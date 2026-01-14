#ifndef APP_SERVICE_HPP
#define APP_SERVICE_HPP

#include <string>
#include "core/install/json_manifest_validator.hpp"
#include "core/payload_validator.hpp"
#include "core/environment.hpp"

namespace app_service
{
  class Install
  {
    private:
      std::string _current_path;
      std::string _payload_path;
      std::string _hyprconf_path;
      std::string _json_str;

      std::string _manifest_path;
      core::install::JsonFileParser _json_validator;
      core::PayloadValidator _payload_validator;
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
