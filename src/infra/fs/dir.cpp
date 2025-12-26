#include "infra/fs/dir.hpp" 

#include <filesystem>

bool fs::dir::exists(const std::string &path_name)
{
  return std::filesystem::exists(path_name) ? true : false;
}

bool fs::dir::is_emp(const std::string &path_name)
{
  return std::filesystem::is_empty(path_name) ? true : false;
}
