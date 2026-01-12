#ifndef ENV_HPP
#define ENV_HPP

#include <string>
namespace infra {
namespace sys {

std::string detect_distro_str();
std::string detect_package_manager_str();

}
}
#endif
