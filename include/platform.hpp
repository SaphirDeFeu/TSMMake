#include<string>

#ifdef _WIN32

std::string PATH_SEPARATOR = "\\";

std::string get_exec_path();

#endif

#ifdef __linux__

std::string PATH_SEPARATOR = "/";

std::string get_exec_path();

#endif