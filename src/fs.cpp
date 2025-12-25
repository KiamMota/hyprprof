#include "fs.hpp"
#include <fstream>
#include <sstream>

std::string fs::get_file_content(const std::string file_path)
{
  std::ifstream f(file_path);
  if(!f) return {};
  std::stringstream buff;
  buff << f.rdbuf();
  return buff.str();
}
