#ifndef APP_SERVICE_HPP
#define APP_SERVICE_HPP

#include "domain/install/json_file_parser.hpp"
#include <string>

namespace app_service
{
  class Install
  {
    private:
      std::string _curr_path;
      std::string _json_file;
      domain::install::JsonFileParser json_validator;
      bool _ValidateJSONManifest();
      bool _ValidatePayload();
    public:
      Install(const std::string& curr_path);

  
  };
}

#endif
