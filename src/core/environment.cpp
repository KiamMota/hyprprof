#include "core/environment.hpp"
#include "core/enum/package_manager_enum.hpp"
#include "core/enum/xdg_session_type_enum.hpp"

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

core::XdgSessionTypeEnum core::Environment::_get_session_type() {
    const char* v = getenv("XDG_SESSION_TYPE");
    if (!v)
        return XdgSessionTypeEnum::UNKNOWN;

    std::string line(v);
    if (line == "wayland")
        return XdgSessionTypeEnum::WAYLAND;
    if (line == "tty")
          return XdgSessionTypeEnum::TTY;
    if (line == "x11")
        return XdgSessionTypeEnum::X11;

    return XdgSessionTypeEnum::UNKNOWN;
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

core::PackageManagerEnum core::Environment::_get_package_manager() {
    std::ifstream f("/etc/os-release");
    if (!f.is_open())
        return PackageManagerEnum::UNKNOWN;

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
        return PackageManagerEnum::PACMAN;
    if (id == "debian" || id == "ubuntu" || id == "linuxmint")
        return PackageManagerEnum::APT;
    if (id == "fedora")
        return PackageManagerEnum::DNF;
    if (id == "centos" || id == "rhel")
        return PackageManagerEnum::YUM;
    if (id == "opensuse" || id == "suse")
        return PackageManagerEnum::ZYPPER;
    if (id == "gentoo")
        return PackageManagerEnum::EMERGE;
    if (id == "alpine")
        return PackageManagerEnum::APK;
    if (id == "nixos")
        return PackageManagerEnum::NIX;

    // flatpak, snap e brew não dependem da distro, então retornamos UNKNOWN aqui
    return PackageManagerEnum::UNKNOWN;
}


bool core::Environment::sudo() const { return _is_sudo; }
std::string core::Environment::user_name() const { return _user_name; }
core::XdgSessionTypeEnum core::Environment::session() const { return _session_type; }

std::string core::Environment::session_str() const {
    switch (_session_type) {
    case core::XdgSessionTypeEnum::TTY:
        return "tty";
    case core::XdgSessionTypeEnum::X11:
        return "x11";
    case core::XdgSessionTypeEnum::WAYLAND:
        return "wayland";
    default:
        return {};
    }
}

core::PackageManagerEnum core::Environment::package_manager() const { return _package_manager; }

std::string core::Environment::package_manager_str() const {
    switch (_package_manager) {
    case core::PackageManagerEnum::APK:
        return "apk";
    case core::PackageManagerEnum::APT:
        return "apt";
    case core::PackageManagerEnum::DNF:
        return "dnf";
    case core::PackageManagerEnum::PACMAN:
        return "pacman";
    case core::PackageManagerEnum::EMERGE:
        return "emerge";
    case core::PackageManagerEnum::ZYPPER:
        return "zypper";
    default:
        return "unknown";
    }
}

std::string core::Environment::install_command() const {
    switch (_package_manager) {
        case core::PackageManagerEnum::APT:
        case core::PackageManagerEnum::APK:
            return "install";
        case core::PackageManagerEnum::DNF:
        case core::PackageManagerEnum::YUM:
            return "dnf install";
        case core::PackageManagerEnum::PACMAN:
            return "pacman -S";
        case core::PackageManagerEnum::EMERGE:
            return "emerge";
        case core::PackageManagerEnum::ZYPPER:
            return "zypper install";
        case core::PackageManagerEnum::NIX:
            return "nix profile install";
        case core::PackageManagerEnum::FLATPAK:
            return "flatpak install";
        case core::PackageManagerEnum::SNAP:
            return "snap install";
        case core::PackageManagerEnum::BREW:
            return "brew install";
        default:
            return "";
    }
}

std::string core::Environment::remove_command() const {
    switch (_package_manager) {
        case core::PackageManagerEnum::APT:
        case core::PackageManagerEnum::APK:
            return "remove";
        case core::PackageManagerEnum::DNF:
            return "dnf remove";
        case core::PackageManagerEnum::YUM:
            return "yum remove";
        case core::PackageManagerEnum::PACMAN:
            return "pacman -R";
        case core::PackageManagerEnum::EMERGE:
            return "emerge --unmerge";
        case core::PackageManagerEnum::ZYPPER:
            return "zypper remove";
        case core::PackageManagerEnum::NIX:
            return "nix profile remove";
        case core::PackageManagerEnum::FLATPAK:
            return "flatpak uninstall";
        case core::PackageManagerEnum::SNAP:
            return "snap remove";
        case core::PackageManagerEnum::BREW:
            return "brew uninstall";
        default:
            return "";
    }
}


