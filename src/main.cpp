#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>

#include "Setup.h"
#include "Tape.h"

int main(int argc, char* argv[])
{
	std::string inFile, outFile;
	Setup params(argc, argv, inFile, outFile);

	auto inTape = std::make_unique<Tape>(inFile);
	auto outTape = std::make_unique<Tape>(outFile);

	// first we read input file and make Size / ram chunks
	// than we do merge sort on sorted chunks

	// ram / 2 == max Concur
	return 0;
}