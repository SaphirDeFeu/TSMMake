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
  std::filesystem::path project_path = cwd / name;
  if(!is_quiet) std::cout << "  \033[92;1mCreating\033[0m \"" << name << "\" (C++ project) at " << project_path << std::endl;
  
  if(std::filesystem::exists(project_path)) {
    std::cerr << "  \033[91;1mSystem error\033[0m: folder " << project_path << " already exists" << std::endl;
    return 1;
  }

  if(!std::filesystem::create_directories(project_path / "src")) {
    std::cerr << "  \033[91;1mSystem error\033[0m: folders for project " << project_path << " cannot be created" << std::endl;
    return 1;
  }

  string ccreate_toml = "[project]\nname = \"" + name + "\"\nversion = \"1.0.0\"\nlang = \"cpp\"\ncompiler = \"g++\"\n\n[dependencies]\n\n";
  create_and_write_file(project_path / "CCreate.toml", ccreate_toml);

  string main_cpp = "#include<iostream>\n\nint main() {\n    std::cout << \"Hello, World!\" << std::endl;\n    return 0;\n}\n";
  create_and_write_file(project_path / "src/main.cpp", main_cpp);

  return 0;
}
