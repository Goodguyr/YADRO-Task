#ifndef FILE_TAPE_H
#define FILE_TAPE_H

#include <chrono>
#include <fstream>
#include <thread>

#include "../config/Config_Parser.h"
#include "Tape.h"

enum TapeType {
  inTape = std::ios::in | std::ios::binary,
  outTape = std::ios::out | std::ios::binary,
};

class FileTape : public Tape {
 private:
  std::fstream file;
  Configuration config;
  size_t head;
  size_t tapeSize;

 public:
  FileTape(const std::string &filename, const TapeType &type,
           const Configuration &config);
  ~FileTape();

  int32_t read() override;
  void write(const int32_t &value) override;
  void shiftForward() override;
  void shiftBackward() override;
  void rewind() override;
  bool tapeEnd() const;
};

#endif