#ifndef PROFILE_HPP
#define PROFILE_HPP

#include <list>
#include <string>
namespace core
{
namespace profile
{

  class Profile
  {
    private:
      std::string _name;
      std::string _version;
      std::list<std::string> _authors;
      std::string _description;
      std::string _hyprland_version_constraint;
      std::string _wayland_version_constraint;
    public:
      Profile();
      void set_name(const std::string& name);
      void set_version(const std::string& version);
      void set_authors(const std::list<std::string>& authors);
      void set_description(const std::string& description);
      void set_hyprland_version(const std::string& hyprland_version);
      void set_wayland_version(const std::string& wayland_version);
  };

}
}
#endif // PROFILE_HPP
