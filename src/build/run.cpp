#include<iostream>
#include<string>
#include<vector>
#include<filesystem>

#include"build/run.hpp"
#include"toml.hpp"

using std::string;
using std::vector;

int run_project(const std::filesystem::path& cwd, vector<string> program_arguments, bool is_quiet) {
  // Assume necessary folders and directories exist because this method is run right after build_project (see mod.cpp@build_project)

  const toml::value config = toml::parse(cwd / "CCreate.toml");
  const toml::value project = toml::find<toml::value>(config, "project");
  const string name = toml::find<string>(project, "name");

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