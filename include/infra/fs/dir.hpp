#ifndef DIR_HPP
#define DIR_HPP

#include <list>
#include <string>

#define CONFIG_PATH "~/.config"

namespace infra {
namespace fs {
namespace dir {
bool create(const std::string& path_name);
bool exists(const std::string& path_name);
bool is_emp(const std::string& path_name);
bool move(const std::string& src, const std::string& new_path);
bool make_bak(const std::string& file_src);
std::string get_absolute(const std::string& src);
bool is_dir(const std::string& src);
const std::list<std::string> list_files(const std::string& path);
std::list<std::string> list_all_files(const std::string& path);
} // namespace dir

} // namespace fs
} // namespace infra
#endif
