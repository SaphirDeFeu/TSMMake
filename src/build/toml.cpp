#include<string>
#include<vector>

#include"build/toml.h"

using std::string;
using std::vector;

CCreateConfig parse_ccreate_config(const string& toml) {
  return {
    project: {
      name: "dev",
      version: "1.0.0",
      lang: "cpp",
      compiler: "g++",
    },
    deps: vector<CCreateDependency>(),
  };
}