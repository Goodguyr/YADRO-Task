#include "FileTape.h"

#include <iostream>
FileTape::FileTape(const std::string &filename, const TapeType &type,
                   const Configuration &config)
    : file(filename, type), config(config), head(0) {
  if (!file.is_open()) {
    throw std::runtime_error("Unable to open file: " + filename);
  }
  tapeSize = file.seekg(0, std::ios::end).tellg() / sizeof(int32_t);
  // std::cout << "Tape size = " + std::to_string(tapeSize) << std::endl;
}

FileTape::~FileTape() { file.close(); }

int32_t FileTape::read() {
  std::this_thread::sleep_for(std::chrono::milliseconds(config.readTime));
  int32_t value = 0;
  file.seekg(head * sizeof(int32_t));
  file.read(reinterpret_cast<char *>(&value), sizeof(value));
  return value;
}

void FileTape::write(const int32_t &value) {
  std::this_thread::sleep_for(std::chrono::milliseconds(config.writeTime));
  file.seekp(head * sizeof(int32_t));
  file.write(reinterpret_cast<const char *>(&value), sizeof(value));
  file.flush();
  if (head == tapeSize) {
    tapeSize++;
  }
}

void FileTape::shiftForward() {
  std::this_thread::sleep_for(std::chrono::milliseconds(config.shiftTime));
  head++;
}

void FileTape::shiftBackward() {
  std::this_thread::sleep_for(std::chrono::milliseconds(config.shiftTime));
  head--;
}

void FileTape::rewind() {
  std::this_thread::sleep_for(std::chrono::milliseconds(config.rewindTime));
  head = 0;
}

bool FileTape::tapeEnd() const { return head == tapeSize; }
