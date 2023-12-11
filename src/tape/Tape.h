#ifndef TAPE_H
#define TAPE_H

#include <cstdint>

class Tape {
 public:
  virtual int32_t read() = 0;
  virtual void write(const int32_t &value) = 0;
  virtual void shiftForward() = 0;
  virtual void shiftBackward() = 0;
  virtual void rewind() = 0;
  virtual ~Tape() = default;
};

#endif
