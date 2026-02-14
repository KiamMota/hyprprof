#include "profile/version_constraits_validator.hpp"
#include "os/cmd.hpp"
#include "os/exception.hpp"
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

#define HYPRLAND_VERSION_COMMAND "hyprland --version"
#define WAYLAND_VERSION_COMMAND "pkg-config --modversion wayland-client"

static std::vector<int> split_version(const std::string& ver) {
    std::vector<int> parts;
    std::stringstream ss(ver);
    std::string item;

    while (std::getline(ss, item, '.')) {
        try {
            parts.push_back(std::stoi(item));
        } catch (...) {
            parts.push_back(0); // trata casos estranhos
        }
    }
    return parts;
}

static void check_pipe_result(const os::Result& res) {
    if (res.error_code != 0)
        throw os::PipeException("command failed with code " + std::to_string(res.error_code));
    if (res.output.empty())
        throw os::PipeException("command returned empty output");
}

bool profile::VersionConstraintsChecker::hyprland_is_equal_or_greater(const std::string& version) {
    std::string _version = version;
    if (!version.empty() && version[0] == '^')
        _version.erase(0, 1);

    auto hyprland_ver = split_version(system_hyprland_version());
    auto min_ver = split_version(_version);

    size_t n = std::max(hyprland_ver.size(), min_ver.size());
    hyprland_ver.resize(n, 0);
    min_ver.resize(n, 0);

    for (size_t i = 0; i < n; ++i) {
        if (hyprland_ver[i] > min_ver[i])
            return true;
        if (hyprland_ver[i] < min_ver[i])
            return false;
    }

    return true;
}

bool profile::VersionConstraintsChecker::wayland_is_equal_or_greater(const std::string& version) {
    std::string _version = version;
    if (!version.empty() && version[0] == '^')
        _version.erase(0, 1);

    auto wayland_ver = split_version(system_wayland_version());
    auto min_ver = split_version(_version);

    size_t n = std::max(wayland_ver.size(), min_ver.size());
    wayland_ver.resize(n, 0);
    min_ver.resize(n, 0);

    for (size_t i = 0; i < n; ++i) {
        if (wayland_ver[i] > min_ver[i])
            return true;
        if (wayland_ver[i] < min_ver[i])
            return false;
    }

    return true;
}

bool profile::VersionConstraintsChecker::hyprland_is_equal(const std::string& version) {
    std::string _version = version;
    if (!version.empty() && version[0] == '^')
        _version.erase(0, 1);

    return _version == system_hyprland_version();
}

bool profile::VersionConstraintsChecker::wayland_is_equal(const std::string& version) {
    std::string _version = version;
    if (!version.empty() && version[0] == '^')
        _version.erase(0, 1);

    return _version == system_wayland_version();
}

std::string profile::VersionConstraintsChecker::system_hyprland_version() {
    auto res = os::pipe(HYPRLAND_VERSION_COMMAND);
    check_pipe_result(res);

    std::string version_output = res.output;
    int ini_pos = strlen("Hyprland ");
    int end_pos = ini_pos + 7; // captura apenas X.Y.Z
    if (version_output.size() < end_pos)
        throw std::runtime_error("Failed to parse Hyprland version from output");

    return version_output.substr(ini_pos, end_pos - ini_pos);
}

std::string profile::VersionConstraintsChecker::system_wayland_version() {
    auto res = os::pipe(WAYLAND_VERSION_COMMAND);
    check_pipe_result(res);

    std::string version_output = res.output;
    return version_output.substr(0, version_output.find_first_of("\n")); // pega a primeira linha
}
