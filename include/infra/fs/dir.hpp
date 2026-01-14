#ifndef DIR_HPP
#define DIR_HPP

#include <string>
namespace infra {
namespace fs {
namespace dir {
bool exists(const std::string& path_name);
bool is_emp(const std::string& path_name);
bool move(const std::string& src, const std::string& new_path);
bool make_bak(const std::string& file_src);
std::string get_absolute(const std::string& src);
} // namespace dir

} // namespace fs
} // namespace infra
#endif
