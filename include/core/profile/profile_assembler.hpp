#ifndef PROFILE_ASSEMBLER_HPP
#define PROFILE_ASSEMBLER_HPP

#include "core/profile/profile.hpp"
#include "core/profile/version_constraints.hpp"
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
    ProfileAssembler& set_wayland_version_constraints(const std::string& version);
    ProfileAssembler& set_hyprland_version_constraints(const std::string& version_constraints);
};
}
}

#endif // PROFILE_ASSEMBLER_HPP
