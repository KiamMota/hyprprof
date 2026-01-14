#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <string>

#include "core/enum/package_manager_enum.hpp"
#include "enum/xdg_session_type_enum.hpp"

namespace core {

class Environment {
  private:
    bool _is_sudo{};
    std::string _home_path;
    std::string _user_name;
    XdgSessionTypeEnum _session_type{XdgSessionTypeEnum::UNKNOWN};
    PackageManagerEnum _package_manager{PackageManagerEnum::UNKNOWN};

    /*
     * getters 
     * */
    bool _get_sudo();
    XdgSessionTypeEnum _get_session_type();
    std::string _get_user_name();
    std::string _get_user_home_path();
    PackageManagerEnum _get_package_manager();

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
