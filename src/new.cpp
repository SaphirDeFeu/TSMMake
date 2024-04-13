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
    std::cerr << "Failed to create CCreate config file (you can still create the file yourself)" << std::endl;
    return;
  }

  file << data;

  file.close();
  return;
}

int create_project(const string& name, const std::filesystem::path& cwd) {
  std::filesystem::path project_path = cwd / name;
  
  if(std::filesystem::exists(project_path)) {
    std::cerr << "Could not create new CCreate project at " << project_path.c_str() << " because the folder already exists." << std::endl;
    return 1;
  }

  std::cout << "Creating new CCreate project at " << project_path.c_str() << std::endl;
  if(!std::filesystem::create_directory(project_path)) {
    std::cerr << "Failed creating root folder of CCreate project, aborting process." << std::endl;
    return 1;
  }

  if(!std::filesystem::create_directory(project_path / "src")) {
    std::cerr << "Failed creating src folder of CCreate project, aborting process." << std::endl;
    return 1;
  }

  string ccreate_toml = "[project]\nname = \"" + name + "\"\nversion = \"1.0.0\"\nlang = \"cpp\"\ncompiler = \"g++\"\n\n[dependencies]\n\n";
  create_and_write_file(project_path / "CCreate.toml", ccreate_toml);

  string main_cpp = "#include<iostream>\n\nint main() {\n    std::cout << \"Hello, World!\" << std::endl;\n    return 0;\n}\n";
  create_and_write_file(project_path / "src/main.cpp", main_cpp);

  return 0;
}
