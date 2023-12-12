#include "SortingAlgorithm.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <future>
#include <limits>
namespace fs = std::filesystem;

SortingAlgorithm::SortingAlgorithm(std::shared_ptr<FileTape> in,
                                   std::shared_ptr<FileTape> out,
                                   Configuration &config)
    : ramSize(config.RAM), tapeCounter(0), config(config), in(in), out(out) {
  fs::create_directory(fileFolder);
  sort();
  while (tapeCounter != 1) {
    merge();
  }
  writeToOut();
}

SortingAlgorithm::~SortingAlgorithm() {
  out->rewind();
  fs::remove_all(fileFolder);
}

// Distributes initial input tape into a lot of sorted tmp tapes
void SortingAlgorithm::sort() {
  int ramUsed = 0;
  while (!in->tapeEnd()) {
    ram.push_back(in->read());
    ramUsed++;
    in->shiftForward();
    if (ramUsed == ramSize) {
      std::sort(ram.begin(), ram.end());
      ramToTmp();
      ram.clear();
      ramUsed = 0;
      tapeCounter++;
    }
  }
  if (ramUsed) {
    std::sort(ram.begin(), ram.end());
    ramToTmp();
    ram.clear();
    tapeCounter++;
  }
}

// Places values from ram to tmpTape file
void SortingAlgorithm::ramToTmp() {
  std::string tmpFileName = fileFolder + "/" + std::to_string(tapeCounter);
  auto tmp = std::make_shared<FileTape>(tmpFileName, outTape, config);

  for (int i : ram) {
    tmp->write(i);
    tmp->shiftForward();
  }

  tmp->rewind();
  tmpTapeStorage.push_back(tmp);
}

void SortingAlgorithm::merge() {
  std::vector<std::shared_ptr<FileTape>> newTapeStorage;

  for (int i = 0; i < tapeCounter; i += 2) {
    if (i + 1 < tapeCounter) {
      std::shared_ptr<FileTape> tape_1 = tmpTapeStorage[i];
      std::shared_ptr<FileTape> tape_2 = tmpTapeStorage[i + 1];
      std::shared_ptr<FileTape> mergeOutput = std::make_shared<FileTape>(
          fileFolder + "/" + std::to_string(tapeCounter + i), outTape, config);

      int32_t num_1, num_2;
      while (!tape_1->tapeEnd() || !tape_2->tapeEnd()) {
        if (!tape_1->tapeEnd()) {
          num_1 = tape_1->read();
        }
        if (!tape_2->tapeEnd()) {
          num_2 = tape_2->read();
        }

        if (num_1 < num_2) {
          mergeOutput->write(num_1);
          tape_1->shiftForward();
          num_1 = std::numeric_limits<int>::max();
        } else {
          mergeOutput->write(num_2);
          tape_2->shiftForward();
          num_2 = std::numeric_limits<int>::max();
        }
        mergeOutput->shiftForward();
      }
      mergeOutput->rewind();
      newTapeStorage.push_back(mergeOutput);
    } else {
      newTapeStorage.push_back(tmpTapeStorage[i]);
    }
  }
  tmpTapeStorage = newTapeStorage;
  tapeCounter = tmpTapeStorage.size();
}

void SortingAlgorithm::writeToOut() {
  auto lastTape = tmpTapeStorage[0];

  while (!lastTape->tapeEnd()) {
    out->write(lastTape->read());
    auto shiftLast = std::async(std::launch::async,
                                [&lastTape]() { lastTape->shiftForward(); });
    out->shiftForward();
    shiftLast.wait();
  }
}
