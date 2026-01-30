#include "profile/profile.hpp"
#include "profile/exceptions.hpp"
#include "profile/version_constraits_validator.hpp"
#include <regex>
#include <stdexcept>
#include <string>

profile::Profile& profile::Profile::set_authors(const std::list<std::string>& authors) {
    if (authors.empty())
        throw profile::EmptyFieldException("The author field is empty!");
    for (auto& author : authors) {
        _authors.push_back(author);
    }
    return *this;
}

profile::Profile& profile::Profile::set_description(const std::string& desc) {
    if (_description.size() > 255)
        throw profile::FieldSizeException("description", 0, 255);
    _description = desc;
    return *this;
}

profile::Profile& profile::Profile::set_name(const std::string& name) {
    if (name.empty())
        throw profile::EmptyFieldException("name");

    std::regex pat(R"(^[A-Za-z_]+$)");
    if (!std::regex_match(name, pat)) {
        throw profile::InvalidPatternException("name");
    }
    _name = name;
    return *this;
}

profile::Profile& profile::Profile::set_version(const std::string& version) {
    if (version.empty())
        throw profile::EmptyFieldException("version");

    std::regex pat(R"(^\d+\.\d+\.\d+(\d*)$)");
    if (!std::regex_match(version, pat)) {
        throw profile::InvalidPatternException("version");
    }
    _version = version;
    return *this;
}

profile::Profile& profile::Profile::set_hyprland_version(const std::string& version) {
    if (version.empty())
        throw profile::EmptyFieldException("Hyprland version");

    std::regex pat(R"(^\^?\d+\.\d+\.\d+$)");
    if (!std::regex_match(version, pat)) {
        throw profile::InvalidPatternException("Hyprland version must be in format ^X.Y.Z or X.Y.Z");
    }

    std::string min_version = VersionConstraintsChecker::system_hyprland_version(); 
    if (!VersionConstraintsChecker::hyprland_is_equal_or_greater(version)) {
        throw std::runtime_error(
            "Hyprland version " + version + " is outdated. Minimum required for this profile: " + min_version
        );
    }

    return *this;
}


profile::Profile& profile::Profile::set_wayland_version(const std::string& version) {
    if (version.empty())
        throw profile::EmptyFieldException("Wayland version");

    std::regex pat(R"(^\^?\d+\.\d+\.\d+$)");
    if (!std::regex_match(version, pat)) {
        throw profile::InvalidPatternException("Wayland version must be in format ^X.Y.Z or X.Y.Z");
    }

    std::string min_version = VersionConstraintsChecker::system_wayland_version();
    if (!VersionConstraintsChecker::wayland_is_equal_or_greater(version)) {
        throw std::runtime_error(
            "Wayland version " + version + " is outdated. Minimum required for this profile: " + min_version
        );
    }

    return *this;
}


const std::string& profile::Profile::version() const noexcept { return _version; }
const std::string& profile::Profile::name() const noexcept { return _name; }
const std::list<std::string>& profile::Profile::authors() const noexcept { return _authors; }
const std::string& profile::Profile::description() const noexcept { return _description; }
