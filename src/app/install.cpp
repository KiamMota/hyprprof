#include "app/install.hpp"
#include "core/install/json_file_parser.hpp"
#include "core/payload_validator.hpp"
#include "infra/fs/dir.hpp"
#include "infra/fs/file.hpp"
#include <string>
#include <unistd.h>

std::string app_service::Install::_TraitPath(const std::string& path) const
{
  std::string correct_path;
  return correct_path;
}

bool app_service::Install::_ValidateJson() {
    auto res = _json_validator.Parse(_json_str);

    if (!infra::fs::file::exists(_manifest_path)) {
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

    if (payload_res != core::PayloadValidatorError::NoError) {
                      core::PayloadErrorToString(payload_res);
        return false;
    }
    return true;
}

app_service::Install::Install(const std::string& curr_path) {
    
    _current_path = infra::fs::dir::get_absolute(curr_path);
    _payload_path = _current_path + "/payload";
    _manifest_path = _current_path + "/hyprprof.json";

    _json_str = infra::fs::file::get_content(_manifest_path);

    if (!_ValidateJson())
        return;
    if (!_ValidatePayload())
        return;
}
