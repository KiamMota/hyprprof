#ifndef ENV_HPP
#define ENV_HPP

#include "enum/package_manager_enum.hpp"
#include "enum/xdg_session_type_enum.hpp"
#include <string>

namespace os {

/**
 * @brief Detect the Linux distribution as a string.
 * 
 * This function attempts to determine the current Linux distribution
 * running on the system (e.g., "Arch", "Ubuntu", "Fedora").
 * 
 * @return A lowercase string representing the distro name.
 */
std::string detect_distro_str();

/**
 * @brief Detect the system's package manager as a string.
 * 
 * Returns a string representation of the package manager
 * according to the detected Linux distribution
 * (e.g., "pacman", "apt", "dnf").
 * 
 * @return A string containing the package manager name.
 */
std::string detect_package_manager_str();

/**
 * @brief Detect the current XDG session type as a string.
 * 
 * Determines whether the session is Wayland or X11.
 * 
 * @return A string representing the session type (e.g., "wayland" or "x11").
 */
std::string detect_xdg_session_str();

/**
 * @brief Detect the current system username.
 * 
 * Retrieves the username of the user running the process.
 * 
 * @return A string containing the username.
 */
std::string detect_user_name();

/**
 * @brief Detect the system's package manager as an enum.
 * 
 * Returns the package manager in enum form for type-safe handling.
 * 
 * @return A PackageManagerEnum value corresponding to the detected manager.
 */
core::PackageManagerEnum detect_package_manager();

/**
 * @brief Detect the current XDG session type as an enum.
 * 
 * Returns the XDG session type in enum form for type-safe handling.
 * 
 * @return An XdgSessionTypeEnum value corresponding to the session type.
 */
core::XdgSessionTypeEnum detect_xdg_session();

} // namespace os

#endif

