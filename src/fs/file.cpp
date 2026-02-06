#include "fs/file.hpp"
#include "fs/dir.hpp"

#include <fstream>
#include <stdexcept>
#include <string>
#include <filesystem>
#include <system_error>

namespace hprof_fs::file {

bool exists(const std::string& file_name)
{
    return std::filesystem::exists(file_name);
}

std::string get_content(const std::string& file_name)
{
    if (!exists(file_name))
        return {};

    std::ifstream file(file_name, std::ios::in | std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("cannot open file: " + file_name);

    return std::string(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    );
}

bool is_file(const std::string& file_name)
{
    return std::filesystem::is_regular_file(
        std::filesystem::absolute(file_name)
    );
}

bool create(const std::string& file)
{
    std::ofstream outf(file);
    if (!outf.is_open())
        throw std::runtime_error("cannot create file: " + file);

    return true;
}

bool move(const std::string& src, const std::string& dest)
{
    std::error_code ec;
    std::filesystem::rename(
        hprof_fs::dir::get_absolute(src),
        dest,
        ec
    );
    return !ec;
}

void insert(const std::string& file_src, const std::string& content)
{
    std::ofstream file(file_src, std::ios::app);
    if (!file.is_open())
        throw std::runtime_error("cannot open file: " + file_src);

    file << content;
}

void overwrite(const std::string& file_src, const std::string& content)
{
    std::ofstream file(file_src, std::ios::out | std::ios::trunc);
    if (!file.is_open())
        throw std::runtime_error("cannot open file: " + file_src);

    file << content;
}

} // namespace hprof_fs::file

