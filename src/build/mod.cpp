#include<iostream>
#include<filesystem>
#include<string>
#include<vector>
#include<fstream>
#include<optional>
#include"parser/mod.hpp"
#include"platform.hpp"

#include"build/mod.hpp"

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::optional;

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

  const optional<TOML::Configuration> config_as_optional = TOML::parse(cwd / "TSMMake.toml");

  if(!config_as_optional.has_value()) {
    std::cerr << "  \033[91;1mConfiguration error\033[0m: no config file found" << std::endl << "Is TSMMake.toml located in the current working directory?" << std::endl;
    return 1;
  }

  const TOML::Configuration config = config_as_optional.value();

  if(config.project.compiler == "") {
    std::cerr << "  \033[91;1mConfiguration error\033[0m: no compiler specified" << std::endl << "Is there a project.compiler field in TSMMake.toml?" << std::endl;
    return 1;
  };

  const string& binary_name = config.project.name;
  if(binary_name == "") {
    std::cerr << "  \033[91;1mConfiguration error\033[0m: no binary name specified" << std::endl << "Is there a project.name field in TSMMake.toml?" << std::endl;
    return 1;
  }

  const bool is_build_directory_present = std::filesystem::exists(cwd / "build");
  if(!is_build_directory_present) {
    const bool create_build_directories_success = std::filesystem::create_directories(cwd / "build" / "src");
    if(!create_build_directories_success) {
      std::cerr << "  \033[91;1mSystem error\033[0m: build directory cannot be created" << std::endl;
      return 1;
    }
  }

  // Source files to object files
  const vector<string> source_files = scan_dir((cwd / "src").string());
  vector<string> source_object_filepaths;
  for(const string& path : source_files) {
    const std::filesystem::path path_as_fspath(path);
    if(!is_quiet) std::cout << "  \033[92;1mCompiling\033[0m " << path_as_fspath << std::endl;

    string object_file_path = replace_ext(path, "o");
    const string string_to_replace = "src";
    const size_t position_index = object_file_path.find(string_to_replace);

    object_file_path.replace(position_index, string_to_replace.length(), "build" + PATH_SEPARATOR + "src");
    source_object_filepaths.push_back(object_file_path);

    create_folders_for_path(object_file_path);

    string command = config.project.compiler + " " + config.project.flags + " -Iinclude -c " + path + " -o " + object_file_path;
    int compilation_success = system(command.c_str());
    if(compilation_success != 0) {
      std::cerr << "  \033[91;1mCompilation error\033[0m: could not compile" << path_as_fspath << std::endl;
      return compilation_success;
    }
  }

  const string standalone_binary_filepath = (cwd / "build" / binary_name).string();
  const std::filesystem::path standalone_binary_fspath(standalone_binary_filepath);
  string command = config.project.compiler + " " + config.project.flags + " -o " + standalone_binary_filepath;
  for(const string& path : source_object_filepaths) {
    command += " " + path;
  }

  const vector<string> dependency_files = scan_dir((cwd / "build" / "include").string());

  for(const string& path : dependency_files) {
    command += " " + path;
  }

  if(!is_quiet) std::cout << "  \033[92;1mCompiling\033[0m " << standalone_binary_fspath << std::endl;
  int exit_code = system(command.c_str());
  if(exit_code != 0) {
    std::cerr << "  \033[91;1mCompilation error\033[0m: could not compile " << standalone_binary_fspath << std::endl;
    return exit_code;
  }

  if(!is_quiet) std::cout << "  \033[92;1mFinishing\033[0m" << std::endl;

  return 0;
}

int build_dependencies(const std::filesystem::path& cwd, bool is_quiet) {
  optional<TOML::Configuration> optional = TOML::parse(cwd / "TSMMake.toml");
  if(!optional.has_value()) {
    std::cerr << "  \033[91;1mConfiguration error\033[0m: no config file found" << std::endl << "Is TSMMake.toml located in the current working directory?";
    return 1;
  }

  TOML::Configuration config = optional.value();

  string compiler = config.project.compiler;
  if(compiler == "") {
    std::cerr << "  \033[91;1mConfiguration error\033[0m: no compiler specified" << std::endl << "Is there a project.compiler field in TSMMake.toml?";
    return 1;
  };

  vector<string> source_files = scan_dir((cwd / "include").string());
  vector<string> object_files;
  for(const string& path : source_files) {

    size_t index = path.find_last_of('.');

    if(index != string::npos && index != path.length() - 1) {
      string ext = path.substr(index + 1);

      if(!(ext == "c" || ext == "cpp")) continue;
    }


    std::filesystem::path path_as_fspath(path);
    if(!is_quiet) std::cout << "  \033[92;1mCompiling\033[0m " << path_as_fspath << std::endl;

    string obj_path = replace_ext(path, "o");
    string toReplace = "include";
    size_t pos = obj_path.find(toReplace);

    obj_path.replace(pos, toReplace.length(), "build" + PATH_SEPARATOR + "include");
    object_files.push_back(obj_path);

    create_folders_for_path(obj_path);

    string command = compiler + " " + config.project.flags + " -Iinclude -c " + path + " -o " + obj_path;
    int exit_code = system(command.c_str());
    if(exit_code != 0) {
      std::cerr << "  \033[91;1mCompilation error\033[0m: could not compile" << path_as_fspath << std::endl;
      return exit_code;
    }
  }

  return 0;
}