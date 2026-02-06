#ifndef APP_SERVICE_HPP
#define APP_SERVICE_HPP

#include "config_file.hpp"
#include "json/json_manifest_reader.hpp"
#include "profile/profile_model.hpp"
#include <string>
namespace use_cases
{
  class Install
  {
    private:
      json::JSONManifestReader _ManifestReader;
      profile::Profile _ProfileModel;
      std::string _current_path;
      void ensure_required_paths();
      void ensure_profile_layout(const std::string& profile_root);
      void ensure_manifest_content(const std::string& string_file);
      void create_profile_path(bool overwrite);
      void finalize_profile_path();
      const std::string load_from_file(const std::string& file);
      std::string _profile_path_in_hyprprof_path;  
public:
      Install(const std::string& curr_path, bool overwrite);
      
  
  };
}

#endif
