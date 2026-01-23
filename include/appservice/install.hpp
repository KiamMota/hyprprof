#ifndef APP_SERVICE_HPP
#define APP_SERVICE_HPP

#include <string>
#include "core/json_manifest.hpp"
#include "core/environment.hpp"
#include "core/profile_payload.hpp"

namespace app_service
{
  class Install
  {
    private:

      core::profile_payload _payload;

      core::JsonManifest _json_validator;
      core::Environment _env;
     
      void _Message() const;
      bool _ValidateEnvironmentState() const; 
      bool _ValidateJson();
      bool _ValidatePayload();

      bool _CopyHyprlandFolder();

      std::string _TraitPath(const std::string& path) const;
    public:
      Install(const std::string& curr_path);
      
  
  };
}

#endif
