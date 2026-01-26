#ifndef VERSION_CONSTRAITS_CHECKER_HPP
#define VERSION_CONSTRAITS_CHECKER_HPP

#include <string>
namespace core {
namespace profile {
class VersionConstraintsChecker {
  private:
  public:
    VersionConstraintsChecker() = default;
    static bool wayland_is_equal_or_greater(const std::string& version);
    static bool hyprland_is_equal_or_greater(const std::string& version);
    static bool hyprland_is_equal(const std::string& version);
    static bool wayland_is_equal(const std::string& version);
};
} // namespace profile
} // namespace core
#endif // VERSION_CONSTRAITS_CHECKER_HPP
