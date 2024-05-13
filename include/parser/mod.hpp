namespace TOML {
  typedef struct ProjectConfiguration {
    std::string name;
    std::string version;
    std::string lang;
    std::string compiler;
    std::string flags;
  } ProjectConfiguration;

  typedef struct Configuration {
    TOML::ProjectConfiguration project;
  } Configuration;

  std::string get_field_name(const std::string& line);

  std::string get_field_value(const std::string& line);

  std::optional<TOML::Configuration> parse(const std::filesystem::path& filepath);
}