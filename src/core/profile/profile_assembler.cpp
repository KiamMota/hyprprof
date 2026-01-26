#include "core/profile/profile_assembler.hpp"
#include "core/profile/exceptions.hpp"
#include "core/profile/version_constraits_checker.hpp"

core::profile::ProfileAssembler&
core::profile::ProfileAssembler::set_profile_description(const ::std::string& desc) {
    _profile.set_description(desc);
    return *this;
}

core::profile::ProfileAssembler&
core::profile::ProfileAssembler::set_profile_name(const ::std::string& name) {
    _profile.set_name(name);
    return *this;
}

core::profile::ProfileAssembler&
core::profile::ProfileAssembler::set_profile_authors(const ::std::list<::std::string>& authors) {
    _profile.set_authors(authors);
    return *this;
}

core::profile::ProfileAssembler&
core::profile::ProfileAssembler::set_profile_version(const ::std::string& version) {
    _profile.set_version(version);
    return *this;
}

core::profile::ProfileAssembler&
core::profile::ProfileAssembler::set_hyprland_version_constraints(const ::std::string& hyprland) {
    _version_constraints.set_hyprland_version(hyprland);
    if (!core::profile::VersionConstraintsChecker::hyprland_is_equal_or_greater(hyprland))
        throw LowerVersionException("hyprland");
    return *this;
}

core::profile::ProfileAssembler&
core::profile::ProfileAssembler::set_wayland_version_constraints(const ::std::string& wayland) {
    _version_constraints.set_wayland_version(wayland);
    if (!core::profile::VersionConstraintsChecker::wayland_is_equal_or_greater(wayland))
        throw LowerVersionException("wayland");
    return *this;
}

const std::list<std::string>& core::profile::ProfileAssembler::authors() const noexcept {
    return _profile.authors();
}

const std::string& core::profile::ProfileAssembler::name() const noexcept {
    return _profile.name();
}

const std::string& core::profile::ProfileAssembler::version() const noexcept {
    return _profile.version();
}

const std::string& core::profile::ProfileAssembler::wayland_version() const noexcept {
    return _version_constraints.wayland_version();
}

const std::string& core::profile::ProfileAssembler::hyprland_version() const noexcept {
    return _version_constraints.hyprland_version();
}
