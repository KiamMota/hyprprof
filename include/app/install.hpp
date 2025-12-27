#ifndef APP_SERVICE_HPP
#define APP_SERVICE_HPP

#include "domain/install/json_file_parser.hpp"
#include "domain/payload_validator.hpp"
#include <string>

namespace app_service
{
  class Install
  {
    private:
      std::string _curr_path;
      std::string _payload_path;
      std::string _json_str;
      domain::install::JsonFileParser json_validator;
      domain::PayloadValidator payload_validator;
    public:
      Install(const std::string& curr_path);

  
  };
}

#endif
