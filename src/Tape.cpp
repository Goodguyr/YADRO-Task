#include "Tape.h"

#include <chrono>
#include <thread>

#include "Setup.h"

Tape::Tape(const std::string& fileName) : fileHandle(fileName, std::ios::in | std::ios::out | std::ios::binary), pos(0)
{
	if (!fileHandle.is_open())
	{
		throw std::runtime_error("Failed to open file: " + fileName);
	}
	fileHandle.seekg(0, std::ios::end);
	fileSize = fileHandle.tellg() / sizeof(int32_t);
	fileHandle.seekg(0, std::ios::beg);
}

Tape::Tape(const std::string& fileName, uint32_t fileSize)
    : fileHandle(fileName, std::ios::in | std::ios::out | std::ios::binary), pos(0), fileSize(fileSize)
{
	if (!fileHandle.is_open())
	{
		throw std::runtime_error("Failed to open file: " + fileName);
	}
}

// Tape::Tape(Tape&& other) : fileHandle(std::move(other.fileHandle)), pos(other.pos), fileSize(other.fileSize)
// {
// 	other.pos = 0;
// 	other.fileSize = 0;
// }

// Tape& Tape::operator=(Tape&& other)
// {
// 	if (this != &other)
// 	{
// 		if (fileHandle.is_open())
// 		{
// 			fileHandle.close();
// 		}
// 		fileHandle = std::move(other.fileHandle);
// 		pos = other.pos;
// 		fileSize = other.fileSize;
// 		other.pos = 0;
// 		other.fileSize = 0;
// 	}
// 	return *this;
// }

Tape::~Tape()
{
	if (fileHandle.is_open())
	{
		fileHandle.close();
	}
}

int32_t Tape::read()
{
	int32_t value;
	const auto delay = std::chrono::milliseconds(static_cast<int32_t>(Delay::IO));
	std::this_thread::sleep_for(delay);
	fileHandle.seekg(pos * sizeof(int32_t));
	fileHandle.read(reinterpret_cast<char*>(&value), sizeof(int32_t));
	return value;
}

void Tape::write(int32_t value)
{
	const auto delay = std::chrono::milliseconds(static_cast<int32_t>(Delay::IO));
	std::this_thread::sleep_for(delay);
	fileHandle.seekp(pos * sizeof(int32_t));
	fileHandle.write(reinterpret_cast<char*>(&value), sizeof(int32_t));
	fileHandle.flush();
	fileSize = fileSize == pos ? fileSize += 1 : fileSize;
}

void Tape::shiftForward()
{
	if (pos < fileSize)
	{
		const auto delay = std::chrono::milliseconds(static_cast<int32_t>(Delay::shift));
		std::this_thread::sleep_for(delay);
		++pos;
	}
}

void Tape::shiftBackward()
{
	if (pos > 0)
	{
		const auto delay = std::chrono::milliseconds(static_cast<int32_t>(Delay::shift));
		std::this_thread::sleep_for(delay);
		--pos;
	}
}

uint32_t Tape::getSize() const { return fileSize; }

void Tape::rewind()
{
	const auto delay = std::chrono::milliseconds(static_cast<int32_t>(Delay::rewind));
	std::this_thread::sleep_for(delay);
	pos = 0;
	fileHandle.seekg(pos);
	fileHandle.seekp(pos);
}

bool Tape::finished() const { return pos == fileSize; }
