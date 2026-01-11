#include "app/install.hpp"
#include "domain/install/json_file_parser.hpp"
#include "domain/payload_validator.hpp"
#include "infra/fs/file.hpp"
#include "infra/log/log.hpp"
#include <string>
#include <unistd.h>

void app_service::Install::_ValidateJson()
{
  auto res = _json_validator.Parse(_json_str);
 
  if (res != domain::install::JsonFileParserError::NoError) {
    domain::install::JsonFileParserError res = _json_validator.Parse(_json_str);
    hypr_log::err("while trying to validate json: ", domain::install::JsonErrorToString(res), " ", "(aborted).");
    return;
  }
}

void app_service::Install::_ValidatePayload()
{
  domain::PayloadValidatorError payload_res = _payload_validator.Validate(_current_path);
  if(payload_res != domain::PayloadValidatorError::NoError)
  {
    hypr_log::err("while trying to validate paylaod: ", domain::PayloadErrorToString(payload_res));
    return;
  }
}

app_service::Install::Install(const std::string& curr_path) : _current_path(curr_path) {
  _payload_path = (_current_path + "/payload");
  _manifest_path = (_current_path + "/hyprprof.json");
  
  _json_str = fs::file::get_content(_current_path + "/hyprprof.json");

  _ValidateJson();
  _ValidatePayload();

}
