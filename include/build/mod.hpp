#ifndef BUILD_MOD_HPP
#define BUILD_MOD_HPP

void delete_carriage_returns(std::string* text);

std::vector<std::string> scan_dir(const std::string& root_dir);

std::string replace_ext(const std::string& path, const std::string& replace);

int build_project(const std::filesystem::path& cwd, bool is_quiet);

int build_dependencies(const std::filesystem::path& cwd, bool is_quiet);

#endif