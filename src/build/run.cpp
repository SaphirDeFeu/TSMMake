#include<iostream>
#include<string>
#include<filesystem>

#include"build/run.hpp"
#include"toml.hpp"

using std::string;

int run_project(const std::filesystem::path& cwd) {
  // Assume necessary folders and directories exist because this method is run right after build_project (see mod.cpp@build_project)

  const toml::value config = toml::parse(cwd / "CCreate.toml");
  const toml::value project = toml::find<toml::value>(config, "project");
  const string name = toml::find<string>(project, "name");

  std::filesystem::path filename = cwd / "build" / name;

  std::cout << "  \033[92;1mRunning\033[0m " << filename << std::endl;
  int code = system(filename.c_str());
  return code;
}