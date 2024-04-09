#include<iostream>
#include<vector>
#include<string>


using std::vector;
using std::string;

const string VERSION = "1.0.0";

template <typename T>
bool isElementInVector(vector<T>* vec, const T& element) {
  int len = vec->size();
  for(int i = 0; i < len; i++) {
    if(vec->at(i) == element) {
      return true;
    }
  }
  return false;
}

vector<string> processCLIArguments(const int& argc, char** argv) {
  vector<string> result = vector<string>();

  if(argc == 1) {
    result.push_back("-h");
  }

  for(int i = 0; i < argc; i++) {
    string arg = string(argv[i]);

    if(arg == "-h" || arg == "--help") {
      result.push_back("-h");
      continue;
    }

    if(arg == "-V" || arg == "--version") {
      result.push_back("-V");
      continue;
    }

  }

  return result;
};

void showHelp() {
  std::cout << "CCreate - C/C++ Package manager and build system - by TSMStudios\n" << std::endl;
  std::cout << "Usage: ccreate [options] [command]\n" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -h, --help      Display this help message" << std::endl;
  std::cout << "  -V, --version   Display installed version" << std::endl;
  std::cout << "\nCommands:" << std::endl;
  std::cout << "  new             Create a new CCreate project" << std::endl;
  return;
}


int main(int argc, char** argv) {
  vector<string> processedArgs = processCLIArguments(argc, argv);

  if(isElementInVector(&processedArgs, string("-h"))) {
    showHelp();
    return 0;
  }

  if(isElementInVector(&processedArgs, string("-V"))) {
    std::cout << "ccreate " << VERSION << std::endl;
    return 0;
  }

  return 0;
};