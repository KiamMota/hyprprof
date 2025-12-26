#include "infra/fs/file.hpp"  
#include <filesystem>
#include <fstream>
#include <string>

bool fs::file::exists(const std::string &file_name)
{
  return std::filesystem::exists(file_name) ? true : false;
}

std::string fs::file::get_content(const std::string &file_name)
{
  if(!fs::file::exists(file_name)) return {};
  std::ifstream file(file_name);
  std::string file_contents { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
  return file_contents;
}
