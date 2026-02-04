#ifndef FS_FILE_HPP
#define FS_FILE_HPP

#include <string>
namespace fs {
namespace file {
std::string get_content(const std::string& file_name);
bool exists(const std::string& file_name);
bool is_file(const std::string& file_name);
bool create(const std::string& file);
bool move(const std::string& src, const std::string& new_scr);
void insert(const std::string& file_src, const std::string& content);
void overwrite(const std::string& file_src, const std::string& content);
} // namespace file

} // namespace fs
#endif
