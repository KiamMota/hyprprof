#ifndef HYPRPROF_PATH_HPP
#define HYPRPROF_PATH_HPP

#include <string>
namespace core
{
  class HyprprofPath
  {
    private:
      std::string _hyprprof_path;
      std::string _config_path;
    public:
      HyprprofPath();
      const std::string& hyprprof_path() const noexcept;
      const std::string& config_path() const noexcept;
      bool path_exists() const noexcept;
      bool has_config_file() const noexcept;
      bool profile_path_exists(const std::string& path_name) const noexcept;
      void create_path(const std::string& name);
      void create_config_file();
      const std::string profile_path(const std::string& path) const; 
  };

}

#endif // HYPRPROF_HPP
