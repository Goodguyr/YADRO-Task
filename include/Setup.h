#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

constexpr uint32_t ramLimit = 100;

namespace Delay
{
static uint32_t IO = 0;
static uint32_t shift = 0;
static uint32_t rewind = 0;
}  // namespace Delay

class Setup
{
public:
	explicit Setup(int argc, char* argv[], std::string& inFile, std::string& outFile);

private:
	void setupDelays();
	std::string getArgument(const std::vector<std::string>& args, const std::string& prefix) const;
	std::string& inFile;
	std::string& outFile;

	std::unordered_map<std::string, uint32_t> delays{
	    {"ioDelay", Delay::IO}, {"shiftDelay", Delay::shift}, {"rewindDelay", Delay::rewind}};
};