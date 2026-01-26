#ifndef VERSION_CONSTRAINTS_HPP
#define VERSION_CONSTRAINTS_HPP

#include <string>
namespace core
{
namespace profile
{
  class VersionConstraints
  {
    private:
      std::string _wayland_version;
      std::string _hyprland_version;
    public:
      VersionConstraints();
      void set_wayland_version(const std::string& ver);
      void set_hyprland_version(const std::string& ver);
      std::string wayland_version() const noexcept;
      std::string hyprland_version() const noexcept;
  };

}
}

#endif // VERSION_CONSTRAINTS_HPP
