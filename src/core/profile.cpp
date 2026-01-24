#include "core/profile/profile.hpp"
#include "core/profile/exceptions.hpp"
#include <regex>

core::profile::Profile::Profile() {}

void core::profile::Profile::set_authors(const std::list<std::string>& authors) {
    if (authors.empty())
        throw profile::EmptyFieldException("The author field is empty!");
    for (auto& author : authors) {
        _authors.push_back(author);
    }
}

void core::profile::Profile::set_description(const std::string& desc) { _description = desc; }

void core::profile::Profile::set_name(const std::string& name) {
    if (name.empty())
        throw profile::EmptyFieldException("name");

    std::regex pat(R"(^[A-Za-z_]+$)");
    if (!std::regex_match(name, pat)) {
        throw profile::InvalidPatternException("name");
        return;
    }
    _name = name;
}

void core::profile::Profile::set_version(const std::string& version) {
    if (version.empty())
        throw profile::EmptyFieldException("version");

    std::regex pat(R"(^\d+\.\d+\.\d+(\d*)$)");
    if (!std::regex_match(version, pat)) {
        throw profile::InvalidPatternException("version");
        return;
    }
    _version = version;
}

void core::profile::Profile::set_hyprland_version(const std::string& hyprland_version)
{
  if(hyprland_version.empty())
    throw profile::EmptyFieldException("hyprland");

  std::regex pat(R"(^\^?\d+\.\d+\.\d+$)");
  if(!std::regex_match(hyprland_version, pat))
  {
    throw profile::InvalidPatternException("hyprland");
  }
}

void core::profile::Profile::set_wayland_version(const std::string& set_wayland_version)
{

  if(set_wayland_version.empty())
    throw profile::EmptyFieldException("wayland");

  std::regex pat(R"(^\^?\d+\.\d+\.\d+$)");
  if(!std::regex_match(set_wayland_version, pat))
  {
    throw profile::InvalidPatternException("wayland");
  }

}
