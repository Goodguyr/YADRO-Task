#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <string>

struct Configuration {
  int readTime = 0;
  int writeTime = 0;
  int shiftTime = 0;
  int rewindTime = 0;
  int RAM = 100;
  int tapeSize = 0;
};

Configuration parseConfigFromFile(const std::string& filename);
void parseCmdArgs(int argc, char* argv[], std::string& inputFileName,
                  std::string& outputFileName);
#endif
