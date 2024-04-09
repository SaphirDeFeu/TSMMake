#include<iostream>
#include<filesystem>
#include<string>
#include<fstream>

namespace fs = std::filesystem;

using std::string;

int create_project(const string& name, const fs::path& cwd) {
  fs::path project_path = cwd / name;
  
  if(fs::exists(project_path)) {
    std::cerr << "Could not create new CCreate project at " << project_path.c_str() << " because the folder already exists." << std::endl;
    return 1;
  }

  std::cout << "Creating new CCreate project at " << project_path.c_str() << std::endl;
  if(!fs::create_directory(project_path)) {
    std::cerr << "Failed creating root folder of CCreate project, aborting process." << std::endl;
    return 1;
  }

  if(!fs::create_directory(project_path / "src")) {
    std::cerr << "Failed creating src folder of CCreate project, aborting process." << std::endl;
    return 1;
  }

  std::ofstream config_file((project_path / "CCreate.toml").c_str());

  if(!config_file.is_open()) {
    std::cerr << "Failed to create CCreate config file" << std::endl;
    return 1;
  }

  config_file << "[project]\n";
  config_file << "name = \"" << name << "\"\n";
  config_file << "version = \"1.0.0\"\n";
  config_file << "lang = \"cpp\"\n";
  config_file << "compiler = \"g++\"\n\n";
  config_file << "[dependencies]\n";
  config_file << "\n";

  config_file.close();

  std::ofstream main_file((project_path / "src/main.cpp").c_str());

  if(!main_file.is_open()) {
    std::cerr << "Failed to create src/main.cpp" << std::endl;
    return 0;
  }

  main_file << "#include<iostream>\n\n";
  main_file << "int main() {\n";
  main_file << "    std::cout << \"Hello, World!\" << std::endl;\n";
  main_file << "}\n";

  main_file.close();

  return 0;
}