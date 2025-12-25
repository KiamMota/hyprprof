#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <string>

#include "package_manager.hpp"
#include "xdg_session_type.hpp"

namespace env {

class Environment {
  private:
    bool _is_sudo{};
    std::string _home_path;
    std::string _user_name;
    XDG_SESSION_TYPE _session_type{XDG_SESSION_TYPE::UNKNOWN};
    PACKAGE_MANAGER _package_manager{PACKAGE_MANAGER::UNKNOWN};

    bool _get_sudo();
    XDG_SESSION_TYPE _get_session_type();
    std::string _get_user_name();
    std::string _get_user_home_path();
    PACKAGE_MANAGER _get_package_manager();

  public:
    Environment();

    bool sudo() const;
    std::string user_name() const;
    XDG_SESSION_TYPE session() const;
    std::string session_str() const;

    PACKAGE_MANAGER package_manager() const;
    std::string package_manager_str() const;
};

} // namespace env

#endif
