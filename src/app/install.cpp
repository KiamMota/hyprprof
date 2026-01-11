#include "app/install.hpp"
#include "domain/install/json_file_parser.hpp"
#include "domain/payload_validator.hpp"
#include "infra/fs/dir.hpp"
#include "infra/fs/file.hpp"
#include "infra/log/log.hpp"
#include <string>
#include <unistd.h>

std::string app_service::Install::_TraitPath(const std::string& path) const
{
  std::string correct_path;
  return correct_path;
}

bool app_service::Install::_ValidateJson() {
    auto res = _json_validator.Parse(_json_str);

    if (!fs::file::exists(_manifest_path)) {
    infra::hypr_log::err("manifest doesn't exists in " + _current_path + ". aborted.");
        return false;
    }

    if (res != domain::install::JsonFileParserError::NoError) {
        domain::install::JsonFileParserError res = _json_validator.Parse(_json_str);
    infra::hypr_log::err("while trying to validate json: ", domain::install::JsonErrorToString(res),
                      " ", "(aborted).");
        return false;
    }
    return true;
}

bool app_service::Install::_ValidatePayload() {
    auto payload_res = _payload_validator.Validate(_current_path);

    if (payload_res != domain::PayloadValidatorError::NoError) {
    infra::hypr_log::err("while trying to validate payload: ",
                      domain::PayloadErrorToString(payload_res));
        return false;
    }
    return true;
}

app_service::Install::Install(const std::string& curr_path) {
    
    _current_path = fs::dir::get_absolute(curr_path);
    _payload_path = _current_path + "/payload";
    _manifest_path = _current_path + "/hyprprof.json";

    _json_str = fs::file::get_content(_manifest_path);

    if (!_ValidateJson())
        return;
    if (!_ValidatePayload())
        return;
}
