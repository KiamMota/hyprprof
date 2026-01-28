#ifndef HYPRPROF_HPP
#define HYPRPROF_HPP

#include <string>
namespace core
{
  class Hyprprof
  {
    private:
      std::string _hyprprof_path;
      std::string _profile_list_path;
    public:
      Hyprprof();
      const std::string& hyprprof_path() const noexcept;
      const std::string& profile_list_path() const noexcept;
      bool hyprprof_path_exists() const noexcept;
      bool profile_list_exists() const noexcept;
  };

}

#endif // HYPRPROF_HPP
