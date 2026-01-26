#include "core/profile/version_constraits_checker.hpp"
#include "infra/sys/cmd.hpp"
#include <cstring>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
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

bool core::profile::VersionConstraintsChecker::hyprland_is_equal_or_greater(
    const std::string& version) {
    auto res = infra::sys::execute_pipe(HYPRLAND_VERSION_COMMAND);



    if (res.error_code != 0) {
        throw std::runtime_error("failed to open pipe to see version of hyprland: " +
                                 std::to_string(res.error_code));
        return false;
    }
    if (res.output.empty())
        throw std::runtime_error("result is empty!");

    int ini_pos = strlen("Hyprland ");
    int end_pos = ini_pos + 7;

    std::string version_output = res.output.substr(ini_pos, end_pos - ini_pos);

    auto hyprland_ver = split_version(version_output);
    auto min_ver = split_version(version);

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

bool core::profile::VersionConstraintsChecker::wayland_is_equal_or_greater(
    const std::string& version) {
    auto res = infra::sys::execute_pipe(WAYLAND_VERSION_COMMAND);

    if (res.error_code != 0) {
        throw std::runtime_error("failed to open pipe to see version of hyprland: " +
                                 std::to_string(res.error_code));
        return false;
    }
    if (res.output.empty())
        throw std::runtime_error("result is empty!");

    std::string version_output = res.output.substr(0);
    std::cout << version_output << std::endl;

    auto wayland_ver = split_version(version_output);
    auto min_ver = split_version(version);

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
