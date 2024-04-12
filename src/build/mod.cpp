#include<iostream>
#include<filesystem>
#include<string>
#include<vector>
#include<fstream>

#include"build/mod.h"
#include"toml.hpp"

using std::string;
using std::vector;
using std::ifstream;

void delete_carriage_returns(string* text) {
  string toReplace("\r");

  size_t pos = text->find(toReplace);
  text->replace(pos, toReplace.length(), "");
} 

int build_project(const std::filesystem::path& cwd) {
  string line;
  vector<string> lines;

  ifstream config_file(cwd / "CCreate.toml");

  if(!config_file.is_open()) {
    std::cerr << "Could not build project because CCreate.toml cannot be found." << std::endl;
    return 1;
  }

  const toml::value data = toml::parse(config_file, cwd / "CCreate.toml");
  config_file.close();
  
  return 0;
}