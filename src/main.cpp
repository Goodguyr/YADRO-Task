#include <cstdlib>
#include <filesystem>
#include <iostream>

#include "algorithms/SortingAlgorithm.h"
#include "config/Config_Parser.h"
#include "tape/FileTape.h"

int main(int argc, char* argv[]) {
  std::string inputFileName = "input.txt";
  std::string outputFileName = "output.txt";
  parseCmdArgs(argc, argv, inputFileName, outputFileName);
  Configuration config = parseConfigFromFile("config/config.txt");

  FileTape readTape(inputFileName, inTape, config);
  FileTape writeTape(outputFileName, outTape, config);
  SortingAlgorithm sorter(readTape, writeTape, config);
  return 0;
}