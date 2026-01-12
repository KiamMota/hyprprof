#include "infra/sys/env.hpp"
#include "infra/fs/file.hpp"
#include "infra/log.hpp"
#include <cstdlib>
#include <string>
#include <algorithm>

std::string infra::sys::detect_distro_str()
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


std::string infra::sys::detect_package_manager_str()
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

