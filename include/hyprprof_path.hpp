#ifndef HYPRPROF_PATH_HPP
#define HYPRPROF_PATH_HPP

#include <string>
namespace core
{
  /*STATIC*/ class HyprprofPath
  {
    private:
      HyprprofPath();
    public:
      static const std::string hyprprof_path() noexcept;
      static const std::string config_path() noexcept;
      static bool path_exists_in_hyprprof_path(const std::string& path) noexcept;
      static const std::string get_path(const std::string& path) noexcept;
      static bool has_config_file() noexcept;
      static void create_path(const std::string& name);
  };

}

#endif // HYPRPROF_HPP
