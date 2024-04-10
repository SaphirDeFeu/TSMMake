#ifndef BUILD_TOML_H
#define BUILD_TOML_H

#include<string>
#include<vector>

typedef struct {
  std::string name;
  std::string version;
  std::string lang;
  std::string compiler;
} CCreateProjectTab;

typedef struct {
  std::string name;
  std::string version;
} CCreateDependency;

typedef struct {
  CCreateProjectTab project;
  std::vector<CCreateDependency> deps;
} CCreateConfig;

CCreateConfig parse_ccreate_config(const std::string& toml);

#endif