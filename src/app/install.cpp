#include "app/install.hpp"
#include "infra/fs/dir.hpp"
#include "infra/fs/file.hpp"
#include "infra/log/log.hpp"
#include <string>

app_service::Install::Install(const std::string& curr_path) : _curr_path(curr_path), _json_file(_curr_path + "/hyprprof.json")
{
  _ValidateJSONManifest();
  _ValidatePayload();
}

bool app_service::Install::_ValidateJSONManifest()
{
  if(!fs::file::exists(_json_file))
  {
    log::err("\"hyprprof.json\" does not exist for the directory ", _curr_path);
    return false;
  }

  std::string json_str = fs::file::get_content(_json_file);
  json_validator.Parse(json_str);
  return true;
}

bool app_service::Install::_ValidatePayload()
{
  if(!fs::dir::exists("payload"))
  {
    return false;

  }
  if(fs::dir::exists("payload/hyprland") && fs::dir::is_emp("payload/hyprland"))
  {
    log::err("the payload of hyprland cannot be empty!");
    return false;
  }

  if(fs::dir::exists("payload/hyprland/bar") && fs::dir::is_emp("payload/hyprland/bar"))
  {
    log::err("the payload of hyprland/bar cannot be empty!");
    return false;
  }
  return true;
}
