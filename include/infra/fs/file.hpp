#ifndef FS_FILE_HPP
#define FS_FILE_HPP

#include <string>
namespace infra {
namespace fs {
namespace file {
std::string get_content(const std::string& file_name);
bool exists(const std::string& file_name);
bool is_file(const std::string& file_name);
bool create(const std::string& file);
} // namespace file

} // namespace fs
} // namespace infra
#endif
