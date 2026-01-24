#include "infra/fs/dotconfig.hpp"
#include <filesystem>
#include <stdexcept>
#include <system_error>

std::string infra::fs::dotconfig::get_config_path() {

    if (const char* xdg = std::getenv("XDG_CONFIG_HOME"))
        return xdg;

    if (const char* home = std::getenv("HOME"))
        return std::string(home) + "/.config";

    throw std::runtime_error("Cannot resolve config path: HOME and XDG_CONFIG_HOME are not set");
}

bool infra::fs::dotconfig::exists(const std::string &app)
{
  std::filesystem::path config_path = get_config_path() + "/app";
  return std::filesystem::exists(config_path);
}

void infra::fs::dotconfig::create(const std::string &app)
{
  std::error_code ec; 
  if(app.empty())
    throw std::runtime_error("path name is empty!");
  std::filesystem::path config_path = get_config_path() + "/" + app;
  std::filesystem::create_directories(app, ec);
}

std::string infra::fs::dotconfig::app_path(const std::string& app)
{
    return get_config_path() + "/" + app;
}

