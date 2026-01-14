#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <string>

#include "core/enum/package_manager_enum.hpp"
#include "enum/xdg_session_type_enum.hpp"

namespace core {

class Environment {
  public:
    Environment();

    bool sudo() const;
    std::string user_name() const;
    XdgSessionTypeEnum session() const;
    std::string session_str() const;

    PackageManagerEnum package_manager() const;
    std::string package_manager_str() const;
    std::string install_command() const;
    std::string remove_command() const;
};

} // namespace env

#endif
