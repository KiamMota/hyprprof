#ifndef APP_SERVICE_HPP
#define APP_SERVICE_HPP

#include "json/global_config.hpp"
#include "json/json_manifest_reader.hpp"
#include "profile/profile.hpp"
#include <string>
namespace use_cases
{
  class Install
  {
    private:
      json::JSONManifestReader _ManifestReader;
      json::GlobalConfig _GlobalConfig;
      profile::Profile _ProfileModel;
      std::string _current_path;
      void ensure_required_paths();
      void ensure_profile_layout(const std::string& profile_root);
      void ensure_manifest_content(const std::string& string_file);
      void create_profile_path();
      void finalize_profile_path();
      void rewrite_config_file(); 
      const std::string load_from_file(const std::string& file);
      std::string _current_profile_path;  
public:
      Install(const std::string& curr_path);
      
  
  };
}

#endif
