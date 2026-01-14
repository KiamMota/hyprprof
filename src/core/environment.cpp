#include "core/environment.hpp"
#include "core/enum/package_manager_enum.hpp"
#include "core/enum/xdg_session_type_enum.hpp"
#include "infra/sys/env.hpp"

#include <pwd.h>
#include <unistd.h>

core::Environment::Environment()
{
  _user_name = infra::sys::detect_user_name();
  _xdg_session = infra::sys::detect_xdg_session_str();
  _package_manager = infra::sys::detect_package_manager_str();
}

std::string core::Environment::install_command() const
{
    if(_package_manager == "pacman")
        return _package_manager + " -S";  // corrigido "istall" → "-S"
    else if(_package_manager == "apt")
        return _package_manager + " install";
    else if(_package_manager == "dnf")
        return _package_manager + " install";
    else if(_package_manager == "zypper")
        return _package_manager + " install";
    else if(_package_manager == "brew")
        return _package_manager + " install";
    else
        return ""; // UNKNOWN package manager
}

std::string core::Environment::package_manager_str() const { return _package_manager; }
std::string core::Environment::session_str() const { return _xdg_session; }

core::XdgSessionTypeEnum core::Environment::session() const
{
  return infra::sys::detect_xdg_session();
}

core::PackageManagerEnum core::Environment::package_manager() const
{
  return infra::sys::detect_package_manager();
}
