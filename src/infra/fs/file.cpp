#include "infra/fs/file.hpp"  
#include "infra/fs/dir.hpp"
#include <exception>
#include <fstream>
#include <stdexcept>
#include <string>
#include <filesystem>
#include <system_error>

bool infra::fs::file::exists(const std::string &file_name) {
  return std::filesystem::exists(std::filesystem::path(file_name));
}

std::string infra::fs::file::get_content(const std::string &file_name)
{
  if(!fs::file::exists(file_name)) return {};
  std::ifstream file(file_name);
  std::string file_contents { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
  return file_contents;
}

bool infra::fs::file::is_file(const std::string &file_name)
{
  std::string all_path = std::filesystem::absolute(file_name);
  return std::filesystem::is_regular_file(all_path);
  
}

bool infra::fs::file::create(const std::string &file)
{
  std::ofstream outf(file);
  if(!outf.is_open())
  {
    throw std::runtime_error("file is not open!");
    return false;
  }
  outf.close();
  return true;
}

bool infra::fs::file::move(const std::string &src, const std::string &new_scr)
{
  std::error_code ec;
  std::filesystem::path abs_src = infra::fs::dir::get_absolute(src);
  std::filesystem::rename(abs_src, new_scr, ec);
  return !ec ? true : false;
}
