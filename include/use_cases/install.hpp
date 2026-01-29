#ifndef APP_SERVICE_HPP
#define APP_SERVICE_HPP

#include "hyprprof_path.hpp"
#include "json/json_manifest_reader.hpp"
#include "profile/profile_layout.hpp"
#include <string>
namespace use_cases
{
  class Install
  {
    private:
      core::Hyprprof _hyprprof_path_obj;
      json::JSONManifestReader _json_reader;
      profile::ProfileLayout _profile_lay;
      void ensure_important_paths();

    public:
      Install(const std::string& curr_path);
      
  
  };
}

#endif
