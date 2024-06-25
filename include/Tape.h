#pragma once

#include <fstream>
#include <string>

#include "ITape.h"

class Tape : public ITape
{
public:
	Tape() = delete;
	Tape(const std::string& fileName);
	Tape(const std::string& fileName, uint32_t fileSize);
	// Tape(const Tape&) = delete;
	// Tape& operator=(const Tape&) = delete;
	// Tape(Tape&& other) noexcept;
	// Tape& operator=(Tape&& other) noexcept;
	~Tape() override;

	int32_t read() override;
	void write(int32_t value) override;
	void rewind() override;
	bool finished() const override;
	void shiftForward() override;
	void shiftBackward() override;
	uint32_t getSize() const override;

	bool operator>(Tape& other) { return read() > other.read(); }

private:
	uint32_t pos;
	uint32_t fileSize;
	std::fstream fileHandle;
};