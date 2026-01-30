#ifndef APP_SERVICE_HPP
#define APP_SERVICE_HPP

#include "hyprprof_path.hpp"
#include "json/json_manifest_reader.hpp"
#include "profile/profile.hpp"
#include "profile/profile_layout.hpp"
#include "json/json_profile_list.hpp"
#include <string>
namespace use_cases
{
  class Install
  {
    private:
      core::HyprprofPath _hyprprof_path;
      json::JSONManifestReader _json_reader;
      json::JSONProfileList _profile_list_json;
      profile::Profile _profile;
      profile::ProfileLayout _profile_lay;

      void ensure_important_paths();
      void ensure_profile_layout(const std::string& curr_path);
      void ensure_manifest(const std::string& string_file);
      void create_path();
      void move_profile_to_path();
      void rewrite_profile_list(); 
      std::string _current_profile_path;  
public:
      Install(const std::string& curr_path);
      
  
  };
}

#endif
