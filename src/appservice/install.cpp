#include "appservice/install.hpp"
#include "core/payload_validator.hpp"
#include "infra/fs/dir.hpp"
#include "infra/fs/file.hpp"
#include "infra/log.hpp"
#include "infra/sys/hyprctl.hpp"
#include <string>
#include <unistd.h>

std::string app_service::Install::_TraitPath(const std::string& path) const
{
  std::string correct_path;
  return correct_path;
}

bool app_service::Install::_ValidateJson() {
    auto res = _json_validator.Parse(_json_str);
    
    infra::hypr_log::log("parsing json...");

    if (!infra::fs::file::exists(_manifest_path)) {
      infra::hypr_log::err("hyprprof.json not found on " + _manifest_path);
        return false;
    }

    if (res != core::install::JsonFileParserError::NoError) {
        return false;
    }
    if(!_json_validator.scripts().empty())
    {
    }

    return true;  // <- garante que sempre retorna bool
}



bool app_service::Install::_ValidatePayload() {
    auto payload_res = _payload_validator.Validate(_current_path);
    
    infra::hypr_log::log("validating payload...");

    if (payload_res != core::PayloadValidatorError::NoError) {
        infra::hypr_log::err(core::PayloadErrorToString(payload_res));
        return false;
    }
    return true;
}

bool app_service::Install::_CopyHyprlandFolder()
{
  if(infra::fs::dir::exists("./config/hypr/hyprland.conf"))
  {
    infra::hypr_log::warn("hyprland configuration already exists");
  }
  return infra::fs::dir::move(_hyprconf_path, "./config/hypr");
}
bool app_service::Install::_ValidateEnvironmentState() const
{
    


}
void app_service::Install::_Message() const
{
  std::cout << "i run a command and my hyprland changed!" << std::endl;
}

app_service::Install::Install(const std::string& curr_path) {
    
    _current_path = infra::fs::dir::get_absolute(curr_path);
    _payload_path = _current_path + "/payload";
    _manifest_path = _current_path + "/hyprprof.json";
    _hyprconf_path = _current_path + "/payoad/hyprland/hyprland.conf";

    _json_str = infra::fs::file::get_content(_manifest_path);

    if (!_ValidateJson())
        return;
    if (!_ValidatePayload())
        return;
    if(!_CopyHyprlandFolder())
    {
      infra::hypr_log::err("failed to copy config to ./config/hyprland");
      return;
    } 
    
    auto res = infra::sys::hyprctl::reload();
  
    std::cout << "res: " << res.output << std::endl;
  
  std::cout << "profile: " << _json_validator.profile_name() << std::endl;
    std::cout << "version: " << _json_validator.version() << std::endl;
    _Message();
}
