#ifndef PROFILE_ASSEMBLER_HPP
#define PROFILE_ASSEMBLER_HPP

#include "core/profile/profile.hpp"
#include "core/profile/version_constraints.hpp"
#include <string>
namespace core
{
namespace profile 
{
class ProfileAssembler
{
  private:
    Profile _profile;
    VersionConstraints _version_constraints;
  public:
    ProfileAssembler();
    ProfileAssembler& set_profile_name(const std::string& name);
    ProfileAssembler& set_profile_version(const std::string& version);
    ProfileAssembler& set_profile_description(const std::string& description);
    ProfileAssembler& set_profile_authors(const std::list<std::string>& authors);
    ProfileAssembler& set_wayland_version_constraints(const std::string& version);
    ProfileAssembler& set_hyprland_version_constraints(const std::string& version_constraints);

    const std::string& name() const noexcept;
    const std::string& version() const noexcept;
    const std::string& description() const noexcept;
    const std::list<std::string>& authors() const noexcept;
    const std::string& wayland_version() const noexcept;
    const std::string& hyprland_version() const noexcept;

};
}
}

#endif // PROFILE_ASSEMBLER_HPP
