#include<iostream>
#include<string>

#include"help.hpp"

using std::string;

void showHelp() {
  std::cout << "TSMMake, a C/C++ Package manager and build tool                     by \033[92;1mTSMStudios\033[0m\n" << std::endl;
  std::cout << "Usage: tsmmake <command> [options]\n" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -h, --help          Display this help message" << std::endl;
  std::cout << "  -V, --version       Display installed version" << std::endl;
  std::cout << "  -q, --quiet         Disables TSMMake info lines from logging" << std::endl;
  std::cout << "  -i, --include-deps  During build and run commands, include compilation of dependencies in the include folder" << std::endl;
  std::cout << "\nCommands:" << std::endl;
  std::cout << "  new                 Create a new TSMMake project" << std::endl;
  std::cout << "  build               Build the current TSMMake project" << std::endl;
  std::cout << "  run                 Build and run the current TSMMake project" << std::endl;
  std::cout << "  help                Display help for a command" << std::endl;
  return;
};

void showHelpForCommand(const string& command) {
  if(command == string("run")) {
    std::cout << "Usage: tsmmake run [options] -- [program_args]\n" << std::endl;
    std::cout << "Builds and runs the current TSMMake project" << std::endl;
    std::cout << "\n[options]" << std::endl;
    std::cout << "Used to customize the behaviour of `run`" << std::endl;
    std::cout << "  -q            Disables TSMMake info lines from logging" << std::endl;
    std::cout << "  -i            Compile dependency files located in an include folder" << std::endl;
    std::cout << "\n[program_args]" << std::endl;
    std::cout << "Project-dependent arguments passed to the executable upon execution" << std::endl;
    std::cout << "Any argument given after '--' is treated as a program argument" << std::endl;
  } else if(command == string("build")) {
    std::cout << "Usage: tsmmake build [options]\n" << std::endl;
    std::cout << "Builds the current TSMMake project" << std::endl;
    std::cout << "\n[options]" << std::endl;
    std::cout << "Used to customize the behaviour of `build`" << std::endl;
    std::cout << "  -q            Disables TSMMake info lines from logging" << std::endl;
    std::cout << "  -i            Compile dependency files located in an include folder" << std::endl;
  } else if(command == string("new")) {
    std::cout << "Usage: tsmmake new <project>\n" << std::endl;
    std::cout << "Creates a new TSMMake project named <project>" << std::endl;
    std::cout << "\n<project>" << std::endl;
    std::cout << "Name of the project used for the directory name and project name in TSMMake.toml, and can be modified after creation" << std::endl;
  } else if(command == string("help")) {
    std::cout << "Usage: tsmmake help <command>\n" << std::endl;
    std::cout << "Displays help for a given <command>" << std::endl;
    std::cout << "\n<command>" << std::endl;
    std::cout << "Command to display help for" << std::endl;
  }
  return;
}
