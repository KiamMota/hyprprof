#ifndef APP_SERVICE_HPP
#define APP_SERVICE_HPP

#include "json/json_file_parser.hpp"
#include <string>
namespace app_service
{
  class AppService
  {
    private:
      std::string _curr_path;
      std::string _json_file;
      json::JsonFileParser json_validator;
      bool _ValidateJSONManifest();
      bool _ValidatePayload();
    public:
      AppService(const std::string& curr_path);

  
  };
}

#endif
