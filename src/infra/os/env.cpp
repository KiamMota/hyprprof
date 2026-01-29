#include "infra/os/env.hpp"
#include "enum/package_manager_enum.hpp"
#include "enum/xdg_session_type_enum.hpp"
#include "infra/fs/file.hpp"
#include "infra/log.hpp"
#include <cstdlib>
#include <pwd.h>
#include <string>
#include <algorithm>

std::string infra::os::detect_distro_str()
{
  std::string os_rel = fs::file::get_content("/etc/os-release");

  int pos = os_rel.find("ID=");
  /* to 'ID=' */
  pos+=3;
  int end = os_rel.find('\n', pos);

  if(end == std::string::npos) end = os_rel.size();

  std::string distro = os_rel.substr(pos, end - pos);
  if(distro.empty())
  {
    hypr_log::err("woops! couldn't detect your distro!"); 
    std::abort();
  }
  return distro;

}

std::string infra::os::detect_package_manager_str()
{
    std::string distro = detect_distro_str();
    std::transform(distro.begin(), distro.end(), distro.begin(), ::tolower);

    if(distro == "arch" || distro == "manjaro")
        return "pacman";
    if(distro == "debian" || distro == "ubuntu" || distro == "linuxmint")
        return "apt";
    if(distro == "fedora")
        return "dnf";
    if(distro == "centos" || distro == "rhel")
        return "yum";
    if(distro == "opensuse" || distro == "suse")
        return "zypper";
    if(distro == "alpine")
        return "apk";
    if(distro == "void")
        return "xbps";
    
    hypr_log::err("Oops! Your package manager isn't yet in hyprprof.");
    std::abort();
}

core::PackageManagerEnum infra::os::detect_package_manager()
{
    std::string pm = detect_package_manager_str();

    if(pm == "pacman") return core::PackageManagerEnum::PACMAN;
    if(pm == "apt") return core::PackageManagerEnum::APT;
    if(pm == "dnf") return core::PackageManagerEnum::DNF;
    if(pm == "yum") return core::PackageManagerEnum::YUM;
    if(pm == "zypper") return core::PackageManagerEnum::ZYPPER;
    if(pm == "apk") return core::PackageManagerEnum::APK;
    if(pm == "xbps") return core::PackageManagerEnum::XBPS;

    return core::PackageManagerEnum::UNKNOWN; // fallback seguro
}

std::string infra::os::detect_xdg_session_str()
{
    const char* xdg = std::getenv("XDG_SESSION_TYPE");
    if (!xdg) {
        return "tty";
    }

    std::string session = xdg;
    for (auto &c : session) c = std::tolower(c);

    return session;
}

core::XdgSessionTypeEnum infra::os::detect_xdg_session()
{
  std::string xdg = detect_xdg_session_str();
  if(xdg == "wayland")
    return core::XdgSessionTypeEnum::WAYLAND;
  if(xdg == "hyprland" && xdg == "Hyprland")
    return core::XdgSessionTypeEnum::HYPRLAND;
  if(xdg == "tty")
    return core::XdgSessionTypeEnum::TTY;
  if(xdg == "x11")
    return core::XdgSessionTypeEnum::X11;
  return core::XdgSessionTypeEnum::UNKNOWN;
}

std::string infra::os::detect_user_name()
{
  return getenv("USER");
}
