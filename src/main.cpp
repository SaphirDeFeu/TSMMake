#include<iostream>
#include<vector>
#include<optional>
#include<string>
#include<filesystem>

#include"new.hpp"
#include"build/mod.hpp"
#include"build/run.hpp"

using std::vector;
using std::string;
using std::optional;

const string VERSION = "1.0.0";

struct CLIArgument {
  string key;
  optional<vector<string>> value;
};

optional<vector<string>> get_value_for_key(vector<CLIArgument>* vec, const string& key) {
  int len = vec->size();
  for(int i = 0; i < len; i++) {
    if(vec->at(i).key == key) {
      return vec->at(i).value;
    }
  }
  return {};
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
      value: {},
    });
  }
  
  int i = 0;
  while(i < argc) {
    string arg = string(argv[i]);

    if(arg == "--") {
      break;
    }

    if(arg == "-h" || arg == "--help") {
      result.push_back({
        key: "-h",
        value: {},
      });
      return result;
    }

    if(arg == "-V" || arg == "--version") {
      result.push_back({
        key: "-V",
        value: {},
      });
      return result;
    }

    if(arg == "-q" || arg == "--quiet") {
      result.push_back({
        key: "-q",
        value: {},
      });
    }

    if(arg == "new") {
      if(++i >= argc) {
        result.push_back({
          key: ":new",
          value: {},
        });
        break;
      }
      string val = string(argv[i]);
      result.push_back({
        key: ":new",
        value: vector<string>({val}),
      });
    }

    if(arg == "build") {
      result.push_back({
        key: ":build",
        value: {},
      });
    }

    if(arg == "run") {
      vector<string> program_arguments;
      bool is_program_arguments = false;
      for(int j = i; j < argc; j++) {
        if(is_program_arguments) program_arguments.push_back("\"" + string(argv[j]) + "\"");
        if(string(argv[j]) == "--") is_program_arguments = true;
      }

      result.push_back({
        key: ":run",
        value: program_arguments,
      });
    }

    i++;
  }

  return result;
};

void showHelp() {
  std::cout << "CCreate - C/C++ Package manager and build tool - by TSMStudios\n" << std::endl;
  std::cout << "Usage: ccreate [options] [command]\n" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -h, --help      Display this help message" << std::endl;
  std::cout << "  -V, --version   Display installed version" << std::endl;
  std::cout << "  -q, --quiet     Disables CCreate info lines from logging" << std::endl;
  std::cout << "\nCommands:" << std::endl;
  std::cout << "  new             Create a new CCreate project" << std::endl;
  std::cout << "  build           Build the current CCreate project" << std::endl;
  std::cout << "  run             Build and run the current CCreate project" << std::endl;
  return;
};


int main(int argc, char** argv) {
  vector<CLIArgument> processed_args = process_cli_arguments(argc, argv);
  std::filesystem::path cwd = std::filesystem::current_path();

  if(is_key_in_vector(&processed_args, "-h")) {
    showHelp();
    return 0;
  }

  if(is_key_in_vector(&processed_args, "-V")) {
    std::cout << "ccreate " << VERSION << std::endl;
    return 0;
  }

  bool quiet = is_key_in_vector(&processed_args, "-q");

  if(is_key_in_vector(&processed_args, ":new")) {
    optional<vector<string>> arg_value = get_value_for_key(&processed_args, ":new");
    if(!arg_value.has_value()) {
      std::cerr << "  \033[91;1mSystem error\033[0m: no name provided for CCreate project" << std::endl;
      return 1;
    }
    string name = arg_value.value()[0];
    return create_project(name, cwd, quiet);
  }

  if(is_key_in_vector(&processed_args, ":build")) {
    return build_project(cwd, quiet);
  }

  if(is_key_in_vector(&processed_args, ":run")) {
    int build_exit_code = build_project(cwd, quiet);
    if(build_exit_code != 0) {
      return build_exit_code;
    }

    vector<string> program_arguments = get_value_for_key(&processed_args, ":run").value();   
    return run_project(cwd, program_arguments, quiet);
  }

  return 0;
};