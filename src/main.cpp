#include<iostream>
#include<vector>
#include<string>
#include<filesystem>

#include"new.cpp"

namespace fs = std::filesystem;

using std::vector;
using std::string;

const string VERSION = "1.0.0";

struct CLIArgument {
  string key;
  string value;
};

string find_value_for_key(vector<CLIArgument>* vec, const string& key) {
  int len = vec->size();
  for(int i = 0; i < len; i++) {
    if(vec->at(i).key == key) {
      return vec->at(i).value;
    }
  }
  return "";
};

bool is_key_in_vector(vector<CLIArgument>* vec, const string& key) {
  int len = vec->size();
  for(int i = 0; i < len; i++) {
    if(vec->at(i).key == key) {
      return true;
    }
  }
  return false;
};

vector<CLIArgument> process_cli_arguments(const int& argc, char** argv) {
  vector<CLIArgument> result = vector<CLIArgument>();

  if(argc == 1) {
    result.push_back({
      key: "-h",
      value: "1",
    });
  }
  
  int i = 0;
  while(i < argc) {
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

    if(arg == "new") {
      i++;
      string val = string(argv[i]);
      result.push_back({
        key: ":new",
        value: val,
      });
    }

    i++;
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
};


int main(int argc, char** argv) {
  vector<CLIArgument> processed_args = process_cli_arguments(argc, argv);
  fs::path cwd = fs::current_path();

  // int procargc = processed_args.size();

  if(find_value_for_key(&processed_args, "-h") == "1") {
    showHelp();
    return 0;
  }

  if(find_value_for_key(&processed_args, "-V") == "1") {
    std::cout << "ccreate " << VERSION << std::endl;
    return 0;
  }

  if(is_key_in_vector(&processed_args, ":new")) {
    return create_project(find_value_for_key(&processed_args, ":new"), cwd);
  }

  return 0;
};