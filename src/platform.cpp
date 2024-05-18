#include<string>

#include"platform.hpp"

#ifdef _WIN32

#include<windows.h>

std::string get_exec_path() {
  char buffer[MAX_PATH];
  GetModuleFileName(NULL, buffer, MAX_PATH);
  return std::string(buffer);
}

#endif

#ifdef __linux__

#include<unistd.h>
#include<limits.h>

std::string get_exec_path() {
  char buffer[PATH_MAX];
  ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
  
  if(len != 1) {
    buffer[len] = 0;
    return std::string(buffer);
  }

  return "";
}

#endif