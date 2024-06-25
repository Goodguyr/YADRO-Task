#pragma once

#include <cstdint>

class ITape
{
public:
	virtual ~ITape() = default;
	virtual int32_t read() = 0;
	virtual void write(int32_t value) = 0;
	virtual void shiftForward() = 0;
	virtual void shiftBackward() = 0;
	virtual void rewind() = 0;
	virtual bool finished() const = 0;
	virtual uint32_t getSize() const = 0;
};