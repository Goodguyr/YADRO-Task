#include "Setup.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

Setup::Setup(int argc, char* argv[], std::string& inFile, std::string& outFile) : inFile(inFile), outFile(outFile)
{
	const std::string badConfigMsg{"Usage :" + std::string(argv[0]) + "-in=[filename] -out=[filename]"};
	if (argc != 3)
	{
		throw std::runtime_error(badConfigMsg);
	}

	std::vector<std::string> args(argv + 1, argv + argc);

	try
	{
		inFile = getArgument(args, "-in=");
		outFile = getArgument(args, "-out=");
	}
	catch (const std::invalid_argument&)
	{
		throw std::runtime_error(badConfigMsg);
	}
	setupDelays();
}

void Setup::setupDelays()
{
	std::ifstream delayFile("delays.txt");
	if (!delayFile.is_open())
	{
		std::cerr << "Unable to open delays.txt, proceeding w default values" << std::endl;
	}

	std::string line;
	while (std::getline(delayFile, line))
	{
		auto delimiterPos = line.find("=");
		if (delimiterPos != std::string::npos)
		{
			std::string key = line.substr(0, delimiterPos);
			std::string value = line.substr(delimiterPos + 1);
			if (delays.count(key))
			{
				delays[key] = std::stoi(value);
			}
		}
	}

	delayFile.close();
}

std::string Setup::getArgument(const std::vector<std::string>& args, const std::string& prefix) const
{
	auto it = std::find_if(args.begin(), args.end(),
	                       [&prefix](const std::string& param) { return param.substr(0, prefix.size()) == prefix; });

	if (it != args.end())
	{
		return it->substr(prefix.size());
	}
	throw std::invalid_argument("Missing argument with prefix: " + prefix);
}