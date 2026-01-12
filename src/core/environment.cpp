#include "core/environment.hpp"

#include <algorithm>
#include <fstream>
#include <pwd.h>
#include <unistd.h>

core::Environment::Environment() {
    _package_manager = _get_package_manager();
    _user_name = _get_user_name();
    _home_path = _get_user_home_path();
    _is_sudo = _get_sudo();
    _session_type = _get_session_type();
}

bool core::Environment::_get_sudo() { return geteuid() == 0; }

XDG_SESSION_TYPE core::Environment::_get_session_type() {
    const char* v = getenv("XDG_SESSION_TYPE");
    if (!v)
        return XDG_SESSION_TYPE::UNKNOWN;

    std::string line(v);
    if (line == "wayland")
        return XDG_SESSION_TYPE::WAYLAND;
    if (line == "tty")
          return XDG_SESSION_TYPE::TTY;
    if (line == "x11")
        return XDG_SESSION_TYPE::X11;

    return XDG_SESSION_TYPE::UNKNOWN;
}

std::string core::Environment::_get_user_name() {
    struct passwd* pw = getpwuid(geteuid());
    if (pw)
        return pw->pw_name;
    return {};
}

std::string core::Environment::_get_user_home_path() {
    if (const char* home = getenv("HOME"))
        return home;
    return {};
}

PACKAGE_MANAGER core::Environment::_get_package_manager() {
    std::ifstream f("/etc/os-release");
    if (!f.is_open())
        return PACKAGE_MANAGER::UNKNOWN;

    std::string line, id;
    while (std::getline(f, line)) {
        if (line.rfind("ID=", 0) == 0) {
            id = line.substr(3);
            if (!id.empty() && id.front() == '"' && id.back() == '"')
                id = id.substr(1, id.size() - 2);
            break;
        }
    }

    std::transform(id.begin(), id.end(), id.begin(), ::tolower);

    if (id == "arch" || id == "manjaro")
        return PACKAGE_MANAGER::PACMAN;
    if (id == "debian" || id == "ubuntu" || id == "linuxmint")
        return PACKAGE_MANAGER::APT;
    if (id == "fedora")
        return PACKAGE_MANAGER::DNF;
    if (id == "centos" || id == "rhel")
        return PACKAGE_MANAGER::YUM;
    if (id == "opensuse" || id == "suse")
        return PACKAGE_MANAGER::ZYPPER;
    if (id == "gentoo")
        return PACKAGE_MANAGER::EMERGE;
    if (id == "alpine")
        return PACKAGE_MANAGER::APK;
    if (id == "nixos")
        return PACKAGE_MANAGER::NIX;

    // flatpak, snap e brew não dependem da distro, então retornamos UNKNOWN aqui
    return PACKAGE_MANAGER::UNKNOWN;
}


bool core::Environment::sudo() const { return _is_sudo; }
std::string core::Environment::user_name() const { return _user_name; }
XDG_SESSION_TYPE core::Environment::session() const { return _session_type; }

std::string core::Environment::session_str() const {
    switch (_session_type) {
    case XDG_SESSION_TYPE::TTY:
        return "tty";
    case XDG_SESSION_TYPE::X11:
        return "x11";
    case XDG_SESSION_TYPE::WAYLAND:
        return "wayland";
    default:
        return {};
    }
}

PACKAGE_MANAGER core::Environment::package_manager() const { return _package_manager; }

std::string core::Environment::package_manager_str() const {
    switch (_package_manager) {
    case PACKAGE_MANAGER::APK:
        return "apk";
    case PACKAGE_MANAGER::APT:
        return "apt";
    case PACKAGE_MANAGER::DNF:
        return "dnf";
    case PACKAGE_MANAGER::PACMAN:
        return "pacman";
    case PACKAGE_MANAGER::EMERGE:
        return "emerge";
    case PACKAGE_MANAGER::ZYPPER:
        return "zypper";
    default:
        return "unknown";
    }
}

std::string core::Environment::install_command() const {
    switch (_package_manager) {
        case PACKAGE_MANAGER::APT:
        case PACKAGE_MANAGER::APK:
            return "install";
        case PACKAGE_MANAGER::DNF:
        case PACKAGE_MANAGER::YUM:
            return "dnf install";
        case PACKAGE_MANAGER::PACMAN:
            return "pacman -S";
        case PACKAGE_MANAGER::EMERGE:
            return "emerge";
        case PACKAGE_MANAGER::ZYPPER:
            return "zypper install";
        case PACKAGE_MANAGER::NIX:
            return "nix profile install";
        case PACKAGE_MANAGER::FLATPAK:
            return "flatpak install";
        case PACKAGE_MANAGER::SNAP:
            return "snap install";
        case PACKAGE_MANAGER::BREW:
            return "brew install";
        default:
            return "";
    }
}

std::string core::Environment::remove_command() const {
    switch (_package_manager) {
        case PACKAGE_MANAGER::APT:
        case PACKAGE_MANAGER::APK:
            return "remove";
        case PACKAGE_MANAGER::DNF:
            return "dnf remove";
        case PACKAGE_MANAGER::YUM:
            return "yum remove";
        case PACKAGE_MANAGER::PACMAN:
            return "pacman -R";
        case PACKAGE_MANAGER::EMERGE:
            return "emerge --unmerge";
        case PACKAGE_MANAGER::ZYPPER:
            return "zypper remove";
        case PACKAGE_MANAGER::NIX:
            return "nix profile remove";
        case PACKAGE_MANAGER::FLATPAK:
            return "flatpak uninstall";
        case PACKAGE_MANAGER::SNAP:
            return "snap remove";
        case PACKAGE_MANAGER::BREW:
            return "brew uninstall";
        default:
            return "";
    }
}


