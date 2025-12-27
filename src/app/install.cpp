#include "app/install.hpp"
#include "domain/install/json_file_parser.hpp"
#include "domain/payload_validator.hpp"
#include "infra/fs/file.hpp"
#include "infra/log/log.hpp"
#include <string>
#include <unistd.h>

app_service::Install::Install(const std::string& curr_path) : _curr_path(curr_path) {
    _payload_path = _curr_path + "/payload";
    _json_str = fs::file::get_content(_curr_path + "/hyprprof.json");
    domain::install::JsonFileParserError res = json_validator.Parse(_json_str);
    if (res != domain::install::JsonFileParserError::NoError) {
      hypr_log::err("while trying to validate json: ", domain::install::JsonErrorToString(res), " ", "(aborted).");
      return;
    }
    domain::PayloadValidatorError payload_res = payload_validator.Validate(_curr_path);
    if(payload_res != domain::PayloadValidatorError::NoError)
    {
      hypr_log::err("while trying to validate paylaod: ", domain::PayloadErrorToString(payload_res));
      return;
    }
}
