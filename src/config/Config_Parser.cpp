#include "Config_Parser.h"

#include <fstream>
#include <iostream>

#include "../tape/FileTape.h"

Configuration parseConfigFromFile(const std::string& filename) {
  Configuration config;
  std::ifstream configFile(filename);

  if (!configFile.is_open()) {
    std::cerr << "Failed to open config file." << std::endl;
    return config;
  }

  std::string line;
  while (std::getline(configFile, line)) {
    size_t enterPos = line.find('=');
    if (enterPos != std::string::npos) {
      std::string param = line.substr(0, enterPos);
      std::string valueStr = line.substr(enterPos + 1);

      try {
        int value = std::stoi(valueStr);

        if (param == "ReadTime")
          config.readTime = value;
        else if (param == "WriteTime")
          config.writeTime = value;
        else if (param == "ShiftTime")
          config.shiftTime = value;
        else if (param == "RewindTime")
          config.rewindTime = value;
        else if (param == "RAM")
          config.RAM = value;
        else if (param == "TapeSize")
          config.tapeSize = value;
      } catch (const std::exception& e) {
        std::cerr << "Error converting value for param " << param << ": "
                  << e.what() << std::endl;
      }
    }
  }
  configFile.close();

  return config;
}

void parseCmdArgs(int argc, char* argv[], std::string& inputFileName,
                  std::string& outputFileName) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " in=<input_file> out=<output_file>"
              << std::endl;
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg.compare(0, 3, "in=") == 0) {
      inputFileName = arg.substr(3);
    } else if (arg.compare(0, 4, "out=") == 0) {
      outputFileName = arg.substr(4);
    }
  }
}