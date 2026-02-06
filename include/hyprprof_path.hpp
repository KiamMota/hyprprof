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
      static void create_required_paths();
      static const std::string path() noexcept;
      static const std::string config_path() noexcept;
      static const std::string bak_path() noexcept;
      static bool path_exists_in_hyprprof_path(const std::string& path) noexcept;
      static const std::string build_path(const std::string& path) noexcept;
      static bool has_config_file() noexcept;
      static void create_path_in_hyprprof_path(const std::string& name, bool overwrite);
  };

}

#endif // HYPRPROF_HPP
