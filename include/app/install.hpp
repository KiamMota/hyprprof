#ifndef APP_SERVICE_HPP
#define APP_SERVICE_HPP

#include "domain/environment.hpp"
#include "domain/install/json_file_parser.hpp"
#include "domain/payload_validator.hpp"
#include <string>

namespace app_service
{
  class Install
  {
    private:
      std::string _current_path;
      std::string _payload_path;
      std::string _json_str;

      std::string _manifest_path;
      domain::install::JsonFileParser _json_validator;
      domain::PayloadValidator _payload_validator;
      domain::Environment _env;
      
      bool _ValidateJson();
      bool _ValidatePayload();
      std::string _TraitPath(const std::string& path) const;
    public:
      Install(const std::string& curr_path);
      
  
  };
}

#endif
