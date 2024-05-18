#include<iostream>
#include<filesystem>
#include<string>
#include<fstream>
#include"platform.hpp"
#include"parser/mod.hpp"

#include"new.hpp"

using std::string;
using std::ofstream;

string get_default_config_path(const std::filesystem::path& exec_path) {
  const std::filesystem::path directory = exec_path.parent_path();
  return (directory / "default.toml").string();
}

void create_and_write_file(const std::filesystem::path& path, const string& data) {

  ofstream file(path.c_str());

  if(!file.is_open()) {
    std::cerr << "  \033[93;1mSystem warn\033[0m: file " << path << " failed to be created" << std::endl << "You can write the file yourself" << std::endl;
    return;
  }

  file << data;

  file.close();
  return;
}

int create_project(const string& name, const std::filesystem::path& cwd, bool is_quiet) {
  const std::filesystem::path EXEC_PATH(get_exec_path());

  const std::optional<TOML::Configuration> PARSE_RES = TOML::parse(get_default_config_path(EXEC_PATH));
  string config_as_toml = "[project]\nname = \"" + name + "\"\nversion = \"1.0.0\"\n";
  string lang = "C++";

  if(!PARSE_RES.has_value()) {
    config_as_toml += "lang = \"cpp\"\ncompiler = \"g++\"\ncompiler_flags = \"-Wall\"\n\n";
  } else {
    const TOML::Configuration DEFAULT_CONFIG = PARSE_RES.value();
    config_as_toml += "lang = \"" + DEFAULT_CONFIG.project.lang + "\"\ncompiler = \"" + DEFAULT_CONFIG.project.compiler + "\"\ncompiler_flags = \"" + DEFAULT_CONFIG.project.flags + "\"\n\n";
  
    if(DEFAULT_CONFIG.project.lang == "c") lang = "C";
  }

  std::filesystem::path root_folder_name = cwd / name;
  if(!is_quiet) std::cout << "  \033[92;1mCreating\033[0m \"" << name << "\" (" + lang + " project) at " << root_folder_name << std::endl;
  
  if(std::filesystem::exists(root_folder_name)) {
    std::cerr << "  \033[91;1mSystem error\033[0m: folder " << root_folder_name << " already exists" << std::endl;
    return 1;
  }

  const bool directory_creation_success = std::filesystem::create_directories(root_folder_name / "src");
  if(!directory_creation_success) {
    std::cerr << "  \033[91;1mSystem error\033[0m: folders for project " << root_folder_name << " cannot be created" << std::endl;
    return 1;
  }

  create_and_write_file(root_folder_name / "TSMMake.toml", config_as_toml);

  string src_main = "#include<iostream>\n\nint main() {\n    std::cout << \"Hello, World!\" << std::endl;\n    return 0;\n}\n";
  string file_name = "main.cpp";
  if(lang == "C") {
    src_main = "#include<stdio.h>\n\nint main() {\n    printf(\"Hello, World!\\n\");\n    return 0;\n}\n";
    file_name = "main.c";
  }

  create_and_write_file(root_folder_name / "src" / file_name, src_main);

  return 0;
}
