#include<string>
#include<fstream>
#include<iostream>
#include<filesystem>
#include<optional>

#include"parser/mod.hpp"

using std::string;
using std::ifstream;

namespace TOML {
  string get_field_name(const string& line) {
    string field;
    for(const char& c : line) {
      if(c == '=' || c == '#') break;

      if(c != ' ') field.push_back(c);
    }
    return field;
  }

  string get_field_value(const string& line) {
    string value;
    bool can_save = false;
    bool in_string = false;
    for(const char& c : line) {
      if(c == '"') {
        in_string = !in_string;
        continue;
      }

      if(c == ' ' && in_string) {
        value.push_back(c);
        continue;
      }

      if(can_save && !(c == ' ' || c == '"')) value.push_back(c);

      if(c == '\n' || c == '\r' || c == '#') break;

      if(c == '=') can_save = true;
    }

    return value;
  }

  std::optional<Configuration> parse(const std::filesystem::path& filepath) {
    ifstream file(filepath);
    if(!file.is_open()) return {};

    Configuration result;

    string current_header = "__global__";
    string current_line;

    result.project.name = "";
    result.project.version = "";
    result.project.lang = "";
    result.project.compiler = "";
    result.project.flags = "";

    while(std::getline(file, current_line)) {
      if(current_line.size() < 2) // account for CRLF because typewriters
        break;

      string field_name;
      string field_value;

      if(current_line.at(0) == '[' && current_line.at(1) != '[') { // object header, not array header
        current_header = current_line;
      } else if(current_line.at(0) != '[') {
        field_name = get_field_name(current_line);
        field_value = get_field_value(current_line);
      }

      if(current_header == "[project]") {
        if(field_name == "name")
          result.project.name = field_value;
        else if(field_name == "version")
          result.project.version = field_value;
        else if(field_name == "lang")
          result.project.lang = field_value;
        else if(field_name == "compiler")
          result.project.compiler = field_value;
        else if(field_name == "compiler_flags")
          result.project.flags = field_value;
      }

    }

    file.close();
    
    return result;

  }

}
