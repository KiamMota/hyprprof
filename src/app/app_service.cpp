#include "app/app_service.hpp"
#include "fs/file.hpp"
#include "log.hpp"
#include <string>

app_service::AppService::AppService(const std::string& curr_path) : _curr_path(curr_path), _json_file(_curr_path + "/hyprprof.json")
{
  _ValidateJSONManifest();
}

bool app_service::AppService::_ValidateJSONManifest()
{
  if(!fs::file::exists(_json_file))
  {
    log::err("\"hyprprof.json\" does not exist for the directory ", _curr_path);
    return false;
  }

  std::string json_str = fs::file::get_content(_json_file);
  std::cout << "json: " << json_str << std::endl;
  json_validator.Parse(json_str);
  return true;
}
