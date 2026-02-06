#ifndef USE_HPP
#define USE_HPP

#include "json/json_manifest_reader.hpp"
#include <string>
namespace use_cases {
class Use 
{
  private:
    std::string _profile_name;
    std::string _profile_path;
    json::JSONManifestReader _manifest;
    void change_config_file();
    void check_config_file();
    void ensure_profile_exists_in_hyprprof_path();
    void ensure_dotfile_packs();
    void copy_hypr_path();
    void copy_waybar_path();
    void copy_dotfile_paths();

  public:

    Use(const std::string& profile_name);



};
} // namespace use_cases

#endif // USE_HPP
