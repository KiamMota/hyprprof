#ifndef ENV_HPP
#define ENV_HPP

#include "core/enum/package_manager_enum.hpp"
#include "core/enum/package_manager_enum.hpp"
#include "core/enum/xdg_session_type_enum.hpp"
#include <string>
namespace infra {
namespace sys {

std::string detect_distro_str();
std::string detect_package_manager_str();
std::string detect_xdg_session_str();
std::string detect_user_name();
core::PackageManagerEnum detect_package_manager();
core::XdgSessionTypeEnum detect_xdg_session();
}
}
#endif
