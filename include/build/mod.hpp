#ifndef BUILD_MOD_HPP
#define BUILD_MOD_HPP

#include<filesystem>

void delete_carriage_returns(std::string* text);

int build_project(const std::filesystem::path& cwd);

#endif