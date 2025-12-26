#ifndef FS_FILE_HPP
#define FS_FILE_HPP

#include <string>
namespace fs
{
namespace file
{
  std::string get_content(const std::string& file_name);
  bool exists(const std::string& file_name);
}


}

#endif
