#include "infra/fs/dir.hpp"
#include "infra/log.hpp"
#include <exception>
#include <filesystem>
#include <list>
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

bool infra::fs::dir::copy(const std::string& src, const std::string& new_path) {
    try {
        std::filesystem::path source(src);
        std::filesystem::path dest(new_path);

        if (!std::filesystem::exists(source) || !std::filesystem::is_directory(source))
            return false;

        if (!std::filesystem::exists(dest))
            std::filesystem::create_directories(dest);

        for (auto& entry : std::filesystem::recursive_directory_iterator(source)) {
            const auto& path = entry.path();
            auto relative_path = std::filesystem::relative(path, source);
            auto dest_path = dest / relative_path;

            if (entry.is_directory()) {
                std::filesystem::create_directories(dest_path);
            } else if (entry.is_regular_file()) {
                std::filesystem::copy_file(path, dest_path,
                                           std::filesystem::copy_options::overwrite_existing);
            }
        }

        return true;
    } catch (const std::exception& e) {
        infra::hypr_log::err(std::string("Failed to copy directory: ") + e.what());
        return false;
    }
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

bool infra::fs::dir::create(const std::string& path_name) {
    std::error_code ec;
    if (std::filesystem::create_directories(path_name, ec))
        return true;
      if (ec)
        throw std::runtime_error("failed to create directory");
    return {};
}

const std::list<std::string> infra::fs::dir::list_files(const std::string& path) {
    static std::list<std::string> empty;
    if (!infra::fs::dir::exists(path))
        return empty;
    std::list<std::string> files;
    for (auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file())
            files.push_back(entry.path().filename().string());
    }
    return files;
}

bool infra::fs::dir::remove(const std::string &path)
{
  return std::filesystem::remove(path);
}
