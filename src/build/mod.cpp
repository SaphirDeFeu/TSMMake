#include<iostream>
#include<filesystem>
#include<string>
#include<vector>
#include<fstream>

#include"build/mod.hpp"
#include"toml.hpp"

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

void delete_carriage_returns(string* text) {
  string toReplace("\r");

  size_t pos = text->find(toReplace);
  text->replace(pos, toReplace.length(), "");
} 

vector<string> scan_dir(const string& root_dir) {
  vector<string> files;

  for(const auto& entry : std::filesystem::recursive_directory_iterator(root_dir)) {
    if(std::filesystem::is_regular_file(entry.path())) {
      files.push_back(entry.path().string());
    }
  }
  return files;
}

string replace_ext(const string& path, const string& replace) {
  size_t dot_pos = path.find_last_of('.');

  if(dot_pos == string::npos || dot_pos == 0) {
    return path;
  }

  string new_path = path.substr(0, dot_pos) + "." + replace;
  return new_path;
}

void create_folders_for_path(const string& absolute_path) {
  string parent_path = std::filesystem::path(absolute_path).parent_path().string();

  if(!std::filesystem::exists(parent_path)) {
    if(!std::filesystem::create_directories(parent_path)) {
      std::cerr << "  \033[91;1mSystem error\033[0m: directories up to " << parent_path << " cannot be created" << std::endl;
    }
  }
}

int build_project(const std::filesystem::path& cwd, bool is_quiet) {
  string line;
  vector<string> lines;

  ifstream config_file(cwd / "TSMMake.toml");

  if(!config_file.is_open()) {
    std::cerr << "  \033[91;1mConfiguration error\033[0m: no config file found" << std::endl << "Is TSMMake.toml located in the current working directory?";
    return 1;
  }

  const toml::value data = toml::parse(config_file, cwd / "TSMMake.toml");
  config_file.close();

  if(!std::filesystem::exists(cwd / "build")) {
    if(!std::filesystem::create_directories(cwd / "build/src")) {
      std::cerr << "  \033[91;1mSystem error\033[0m: build directory cannot be created" << std::endl;
      return 1;
    }
  }

  if(!data.contains("project")) {
    std::cerr << "  \033[91;1mConfiguration error\033[0m: no project found" << std::endl << "Is TSMMake.toml present and correct?";
    return 1;
  }

  const toml::value project = toml::find<toml::value>(data, "project");

  string binary_name;
  if(!project.contains("name")) {
    binary_name = cwd.filename();
  } else {
    binary_name = toml::find<string>(project, "name");
  }
  
  if(!project.contains("compiler")) {
    std::cerr << "  \033[91;1mConfiguration error\033[0m: no compiler specified" << std::endl << "Is there a compiler field in TSMMake.toml?";
    return 1;
  }

  const string compiler = toml::find<string>(project, "compiler");

  vector<string> source_files = scan_dir((cwd / "src").string());
  vector<string> object_files;
  for(const string& path : source_files) {
    std::filesystem::path path_as_fspath(path);
    if(!is_quiet) std::cout << "  \033[92;1mCompiling\033[0m " << path_as_fspath << std::endl;

    string obj_path = replace_ext(path, "o");
    string toReplace = "src";
    size_t pos = obj_path.find(toReplace);

    obj_path.replace(pos, toReplace.length(), "build/src");
    object_files.push_back(obj_path);

    create_folders_for_path(obj_path);

    string command = compiler + " -Wall -c " + path + " -o " + obj_path;
    int exit_code = system(command.c_str());
    if(exit_code != 0) {
      std::cerr << "  \033[91;1mCompilation error\033[0m: could not compile" << path_as_fspath << std::endl;
      return exit_code;
    }
  }

  string full_path = (cwd / "build" / binary_name).string();
  std::filesystem::path full_path_as_fspath(full_path);
  string command = compiler + " -Wall -o " + full_path;
  for(const string& path : object_files) {
    command += " " + path;
  }

  if(!is_quiet) std::cout << "  \033[92;1mCompiling\033[0m " << full_path_as_fspath << std::endl;
  int exit_code = system(command.c_str());
  if(exit_code != 0) {
    std::cerr << "  \033[91;1mCompilation error\033[0m: could not compile " << full_path_as_fspath << std::endl;
    return exit_code;
  }

  if(!is_quiet) std::cout << "  \033[92;1mFinishing\033[0m" << std::endl;

  return 0;
}