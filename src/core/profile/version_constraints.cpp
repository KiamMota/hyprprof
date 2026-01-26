#include "core/profile/version_constraints.hpp"
#include "core/profile/exceptions.hpp"
#include <regex>
#include <unistd.h>

core::profile::VersionConstraints::VersionConstraints() {
    _hyprland_version = {};
    _wayland_version = {};
}

void core::profile::VersionConstraints::set_wayland_version(const std::string& version) {
    if (version.empty())
        throw profile::EmptyFieldException("wayland");

    std::regex pat(R"(^\^?\d+\.\d+\.\d+$)");
    if (!std::regex_match(version, pat)) {
        throw profile::InvalidPatternException("wayland");
    }
}

void core::profile::VersionConstraints::set_hyprland_version(const std::string& hyprland_version) {
    if (hyprland_version.empty())
        throw profile::EmptyFieldException("hyprland");

    std::regex pat(R"(^\^?\d+\.\d+\.\d+$)");
    if (!std::regex_match(hyprland_version, pat)) {
        throw profile::InvalidPatternException("hyprland");
    }
}

std::string core::profile::VersionConstraints::hyprland_version() const noexcept {
    return _hyprland_version;
}

std::string core::profile::VersionConstraints::wayland_version() const noexcept {
    return _wayland_version;
}
