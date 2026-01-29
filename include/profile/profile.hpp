#ifndef PROFILE_HPP
#define PROFILE_HPP

#include <list>
#include <string>
namespace profile
{

  class Profile
  {
    private:
      std::string _name;
      std::string _version;
      std::list<std::string> _authors;
      std::string _description;
      std::string _wayland_version_constraints;
      std::string _hyprland_version_constraints;
    public:
      Profile() = default;
      Profile& set_name(const std::string& name);
      Profile& set_version(const std::string& version);
      Profile& set_authors(const std::list<std::string>& authors);
      Profile& set_description(const std::string& description);
      Profile& set_wayland_version(const std::string& wayland_version);
      Profile& set_hyprland_version(const std::string& hyprland_version);
      const std::string& name() const noexcept;
      const std::string& version() const noexcept;
      const std::list<std::string>& authors() const noexcept;
      const std::string& description() const noexcept;
      

  };

}
#endif // PROFILE_HPP
