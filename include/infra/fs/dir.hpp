#ifndef DIR_HPP
#define DIR_HPP

#include <string>
namespace fs
{
namespace dir
{
  bool exists(const std::string& path_name);
  bool is_emp(const std::string& path_name);
}

}

#endif
