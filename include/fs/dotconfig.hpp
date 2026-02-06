#ifndef HPROF_FS_DOTCONFIG_HPP
#define HPROF_FS_DOTCONFIG_HPP

#include <string>
namespace hprof_fs {
namespace dotconfig {
std::string get_config_path();
bool exists(const std::string& app);
void create(const std::string& app);
std::string app_path(const std::string& app);
}
} 


#endif // DOTCONFIG_HPP
