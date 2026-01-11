#include "infra/fs/dir.hpp" 
#include <filesystem>
#include <system_error>

bool fs::dir::exists(const std::string &path_name)
{
  return std::filesystem::exists(path_name) ? true : false;
}

bool fs::dir::is_emp(const std::string &path_name)
{
  return std::filesystem::is_empty(path_name) ? true : false;
}

bool fs::dir::move(const std::string &src, const std::string &new_path)
{
  std::error_code ec;
  std::filesystem::rename(src, new_path, ec);
  return ec ? true : false;
}

std::string fs::dir::get_absolute(const std::string &src)
{
    return std::filesystem::absolute(src).string();
}

