#ifndef CURRENT_PROFILE_HPP
#define CURRENT_PROFILE_HPP

#include <string>
namespace core {
class CurrentProfile {
  private:
    std::string _current_profile_name;
    std::string _current_profile_path;

public:
  CurrentProfile();
  void set_profile_name(const std::string& name);
  void set_current_path(const std::string& path);
  const std::string& name() const noexcept;
  const std::string& path() const noexcept;
};

} // namespace core

#endif // CURRENT_PROFILE_HPP
