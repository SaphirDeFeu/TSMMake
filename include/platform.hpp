#include<string>

#ifdef _WIN32

std::string get_exec_path();

#endif

#ifdef __linux__

std::string get_exec_path();

#endif