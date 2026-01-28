#ifndef APP_SERVICE_HPP
#define APP_SERVICE_HPP

#include "core/hyprprof_path.hpp"
#include "core/json/json_manifest_reader.hpp"
#include "core/profile/profile_assembler.hpp"
#include "core/profile/profile_layout.hpp"
#include <string>
namespace app_service
{
  class Install
  {
    private:
      core::Hyprprof _hyprprof_path_obj;
      core::json::JSONManifestReader _json_reader;
      core::ProfileLayout _profile_lay;
      core::profile::ProfileAssembler _profile_domain;
      void ensure_important_paths();

    public:
      Install(const std::string& curr_path);
      
  
  };
}

#endif
