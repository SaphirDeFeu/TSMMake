
#ifndef PLATFORM_DEPENDENT_CODE
#define PLATFORM_DEPENDENT_CODE

#ifdef _WIN32

const std::string PATH_SEPARATOR = "\\";

std::string get_exec_path();

#endif

#ifdef __linux__

const std::string PATH_SEPARATOR = "/";

std::string get_exec_path();

#endif

#endif
