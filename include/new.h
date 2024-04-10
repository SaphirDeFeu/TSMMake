#ifndef NEW_H
#define NEW_H

#include<string>
#include<filesystem>

int create_project(const std::string& name, const std::filesystem::path& cwd);

#endif