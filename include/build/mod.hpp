#ifndef BUILD_MOD_HPP
#define BUILD_MOD_HPP

#include<filesystem>
#include<vector>

void delete_carriage_returns(std::string* text);

std::vector<std::string> scan_dir(const std::string& root_dir);

std::string replace_ext(const std::string& path, const std::string& replace);

int build_project(const std::filesystem::path& cwd);

#endif