#ifndef SORTING_ALGORITHM
#define SORTING_ALGORITHM

#include <iostream>
#include <vector>

#include "../config/Config_Parser.h"
#include "../tape/FileTape.h"

class SortingAlgorithm {
 private:
  int ramSize;
  int tapeCounter;
  std::vector<int> ram;
  const std::string fileFolder = "tmp";
  Configuration config;
  std::shared_ptr<FileTape> in;
  std::shared_ptr<FileTape> out;
  std::vector<std::shared_ptr<FileTape>> tmpTapeStorage;

  void sort();
  void merge();
  void writeToOut();
  void ramToTmp();

 public:
  SortingAlgorithm(std::shared_ptr<FileTape> in, std::shared_ptr<FileTape> out,
                   Configuration &config);
  ~SortingAlgorithm();
};

#endif
