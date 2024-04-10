#include<iostream>
#include<filesystem>
#include<string>
#include<fstream>

#include"build/mod.h"
#include"build/toml.h"

using std::string;
using std::ifstream;

int build_project(const std::filesystem::path& cwd) {
  string line;
  string text = "";

  ifstream config_file((cwd / "CCreate.toml").c_str());

  if(!config_file.is_open()) {
    std::cerr << "Could not build project because CCreate.toml cannot be found." << std::endl;
    return 1;
  }

  while(std::getline(config_file, line)) {
    text = text + line + "\n";
  }

  CCreateConfig config = parse_ccreate_config(text);

  config_file.close();
  return 0;
}