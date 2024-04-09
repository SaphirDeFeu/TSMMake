#include<iostream>
#include<vector>
#include<string>


using std::vector;
using std::string;

const string VERSION = "1.0.0";

struct CLIArgument {
  string key;
  string value;
};

string findValueForKey(vector<CLIArgument>* vec, const string& key) {
  int len = vec->size();
  for(int i = 0; i < len; i++) {
    if(vec->at(i).key == key) {
      return vec->at(i).value;
    }
  }
  return "";
}


vector<CLIArgument> processCLIArguments(const int& argc, char** argv) {
  vector<CLIArgument> result = vector<CLIArgument>();

  if(argc == 1) {
    result.push_back({
      key: "-h",
      value: "1",
    });
  }

  for(int i = 0; i < argc; i++) {
    string arg = string(argv[i]);

    if(arg == "-h" || arg == "--help") {
      result.push_back({
        key: "-h",
        value: "1",
      });
      return result;
    }

    if(arg == "-V" || arg == "--version") {
      result.push_back({
        key: "-V",
        value: "1",
      });
      return result;
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
  vector<CLIArgument> processedArgs = processCLIArguments(argc, argv);

  if(findValueForKey(&processedArgs, "-h") == "1") {
    showHelp();
    return 0;
  }

  if(findValueForKey(&processedArgs, "-V") == "1") {
    std::cout << "ccreate " << VERSION << std::endl;
    return 0;
  }

  return 0;
};