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

  auto readTape = std::make_shared<FileTape>(inputFileName, inTape, config);
  auto writeTape = std::make_shared<FileTape>(outputFileName, outTape, config);
  SortingAlgorithm sorter(readTape, writeTape, config);
  return 0;
}