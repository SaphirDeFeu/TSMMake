#include<iostream>
#include<filesystem>
#include<string>
#include<fstream>

#include"new.hpp"

using std::string;
using std::ofstream;

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
  std::filesystem::path root_folder_name = cwd / name;
  if(!is_quiet) std::cout << "  \033[92;1mCreating\033[0m \"" << name << "\" (C++ project) at " << root_folder_name << std::endl;
  
  if(std::filesystem::exists(root_folder_name)) {
    std::cerr << "  \033[91;1mSystem error\033[0m: folder " << root_folder_name << " already exists" << std::endl;
    return 1;
  }

  const bool directory_creation_success = std::filesystem::create_directories(root_folder_name / "src");
  if(!directory_creation_success) {
    std::cerr << "  \033[91;1mSystem error\033[0m: folders for project " << root_folder_name << " cannot be created" << std::endl;
    return 1;
  }

  string config_as_toml = "[project]\nname = \"" + name + "\"\nversion = \"1.0.0\"\nlang = \"cpp\"\ncompiler = \"g++\"\ncompiler_flags = \"-Wall\"\n\n";
  create_and_write_file(root_folder_name / "TSMMake.toml", config_as_toml);

  string main_cpp = "#include<iostream>\n\nint main() {\n    std::cout << \"Hello, World!\" << std::endl;\n    return 0;\n}\n";
  create_and_write_file(root_folder_name / "src/main.cpp", main_cpp);

  return 0;
}
