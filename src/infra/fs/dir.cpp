#include "infra/fs/dir.hpp"
#include "infra/log.hpp"
#include <exception>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <system_error>

bool infra::fs::dir::exists(const std::string& path_name) {
    return std::filesystem::exists(path_name) ? true : false;
}

bool infra::fs::dir::is_emp(const std::string& path_name) {
    return std::filesystem::is_empty(path_name) ? true : false;
}

bool infra::fs::dir::move(const std::string& src, const std::string& new_path) {
    std::error_code ec;
    std::filesystem::rename(src, new_path, ec);
    return ec ? true : false;
}

std::string infra::fs::dir::get_absolute(const std::string& src) {
    return std::filesystem::absolute(src).string();
}

bool infra::fs::dir::make_bak(const std::string& file_src) {
    std::filesystem::path src_path = infra::fs::dir::get_absolute(file_src);

    if (!std::filesystem::exists(src_path)) {
        infra::hypr_log::file_not_exists(src_path);
        return false;
    }
    std::filesystem::path dest_path = src_path;
    dest_path += ".bak";

    std::error_code ec;
    std::filesystem::copy(src_path, dest_path,
                          std::filesystem::copy_options::overwrite_existing |
                              std::filesystem::copy_options::recursive,
                          ec);

    if (ec)
        throw std::filesystem::filesystem_error("backup failed", src_path, dest_path, ec);
  return true;
}

bool infra::fs::dir::is_dir(const std::string& src) {
    return std::filesystem::is_directory(src) ? true : false;
}

bool infra::fs::dir::create(const std::string &path_name)
{
  std::error_code ec;
  if(std::filesystem::create_directories(path_name, ec))
    return true;
  if(ec)
    throw std::runtime_error("failed to create directory");
  return {};
}
