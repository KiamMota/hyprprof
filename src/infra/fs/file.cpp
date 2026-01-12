#include "infra/fs/file.hpp"  
#include <fstream>
#include <string>
#include <filesystem>

bool infra::fs::file::exists(const std::string &file_name) {
    try {
        return std::filesystem::exists(std::filesystem::path(file_name));
    } catch (const std::filesystem::filesystem_error&) {
        return false; // se houver problema de permissão ou caminho inválido
    }
}

std::string infra::fs::file::get_content(const std::string &file_name)
{
  if(!fs::file::exists(file_name)) return {};
  std::ifstream file(file_name);
  std::string file_contents { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
  return file_contents;
}

