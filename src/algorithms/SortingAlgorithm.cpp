#include "SortingAlgorithm.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <future>
#include <limits>
#include <memory>

namespace fs = std::filesystem;

SortingAlgorithm::SortingAlgorithm(FileTape &in, FileTape &out,
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
  out.rewind();
  fs::remove_all(fileFolder);
}

// Distributes initial input tape into a lot of sorted tmp tapes
void SortingAlgorithm::sort() {
  int ramUsed = 0;
  while (!in.tapeEnd()) {
    ram.push_back(in.read());
    ramUsed++;
    in.shiftForward();
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
  FileTape tmp(tmpFileName, outTape, config);

  for (int i : ram) {
    tmp.write(i);
    tmp.shiftForward();
  }
  tmp.rewind();
}

void SortingAlgorithm::merge() {
  for (int i = 0; i < tapeCounter; i += 2) {
    std::string tmpFile = fileFolder + "/";
    if (i + 1 < tapeCounter) {
      FileTape tape_1(tmpFile + std::to_string(i), inTape, config);
      FileTape tape_2(tmpFile + std::to_string(i + 1), inTape, config);
      FileTape mergeOutput(tmpFile + std::to_string(tapeCounter + 1), outTape,
                           config);

      int32_t num_1, num_2;
      while (!tape_1.tapeEnd() || !tape_2.tapeEnd()) {
        if (!tape_1.tapeEnd()) {
          num_1 = tape_1.read();
        }
        if (!tape_2.tapeEnd()) {
          num_2 = tape_2.read();
        }

        if (num_1 < num_2) {
          mergeOutput.write(num_1);
          tape_1.shiftForward();
          num_1 = std::numeric_limits<int>::max();
        } else {
          mergeOutput.write(num_2);
          tape_2.shiftForward();
          num_2 = std::numeric_limits<int>::max();
        }
        mergeOutput.shiftForward();
      }
      fs::remove(tmpFile + std::to_string(i + 1));
      fs::rename(tmpFile + std::to_string(tapeCounter + 1),
                 tmpFile + std::to_string(i / 2));
      // Doesnt matter but has to be here for integrity
      mergeOutput.rewind();
    } else {
      fs::rename(tmpFile + std::to_string(tapeCounter - 1),
                 tmpFile + std::to_string(tapeCounter / 2));
    }
  }
  tapeCounter =
      (tapeCounter % 2) ? ((tapeCounter /= 2) + 1) : (tapeCounter /= 2);
}

void SortingAlgorithm::writeToOut() {
  std::string finalFile = fileFolder + "/0";
  FileTape lastTape(finalFile, inTape, config);
  while (!lastTape.tapeEnd()) {
    out.write(lastTape.read());
    auto shiftLast = std::async(std::launch::async,
                                [&lastTape]() { lastTape.shiftForward(); });
    out.shiftForward();
    shiftLast.wait();
  }
}
