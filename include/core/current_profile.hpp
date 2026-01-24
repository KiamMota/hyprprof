#ifndef CURRENT_PROFILE_HPP
#define CURRENT_PROFILE_HPP

#include <string>
namespace core {
class CurrentProfile {
  private:
    std::string _current_profile_name;
    std::string _current_profile_path;

public:
  CurrentProfile(const std::string& profile_name, const std::string& profile_path);
};

} // namespace core

#endif // CURRENT_PROFILE_HPP
