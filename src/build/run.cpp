#include<iostream>
#include<string>
#include<vector>
#include<filesystem>
#include<optional>
#include"parser/mod.hpp"

#include"build/run.hpp"

using std::string;
using std::vector;

int run_project(const std::filesystem::path& cwd, vector<string> program_arguments, bool is_quiet) {
  // Assume necessary folders and directories exist because this method is run right after build_project (see mod.cpp@build_project)

  const std::optional<TOML::Configuration> optional = TOML::parse(cwd / "TSMMake.toml");
  const TOML::Configuration config = optional.value(); // assume okay
  const string name = config.project.name; // assume okay

  std::filesystem::path filename = cwd / "build" / name;

  string command = filename.string();
  int argc = program_arguments.size();
  for(int i = 0; i < argc; i++) {
    command += " " + program_arguments.at(i);
  }

  if(!is_quiet) std::cout << "  \033[92;1mRunning\033[0m " << filename << std::endl;
  int code = system(command.c_str());
  return code;
}