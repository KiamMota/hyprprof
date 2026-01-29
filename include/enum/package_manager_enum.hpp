#ifndef _PACKAGE_MANAGE_HPP_
#define _PACKAGE_MANAGE_HPP_

namespace core
{
enum class PackageManagerEnum {
    UNKNOWN,
    PACMAN,     // Arch Linux
    APT,        // Debian/Ubuntu
    DNF,        // Fedora
    YUM,        // CentOS/RHEL
    ZYPPER,     // openSUSE
    EMERGE,     // Gentoo
    APK,        // Alpine
    NIX,        // NixOS
    FLATPAK,    // Flatpak
    SNAP,       // Snap
    BREW,       // Linuxbrew/Homebrew
    XBPS        // void
};
}

#endif
