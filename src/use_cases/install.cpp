#include "use_cases/install.hpp"
#include "fs/dir.hpp"
#include "fs/file.hpp"
#include "hyprprof_path.hpp"
#include "profile/profile_layout_validator.hpp"
#include "utils/log.hpp"
#include "profile/profile_layout_exceptions.hpp"
#include "json/json_exceptions.hpp"
#include "json/json_manifest_reader.hpp"
#include <bits/types/cookie_io_functions_t.h>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <unistd.h>

void use_cases::Install::ensure_profile_layout(const std::string& path) {
    try {
      profile::ProfileLayout::check_required_paths(path);
    } catch (profile::ProfileLayoutDirException const& ex) {
        hypr_log::err(ex.what());
        std::exit(0);
    } catch (profile::ProfileLayoutFileException const& ex) {
        hypr_log::err(ex.what());
        std::exit(0);
    }
}

void use_cases::Install::ensure_required_paths() {
    if (!_Paths.path_exists())
        fs::dir::create(_Paths.hyprprof_path());
    if (!_Paths.has_config_file())
        fs::file::create(_Paths.config_path());
}

void use_cases::Install::ensure_manifest_content(const std::string& string) {
    try {
        _ManifestReader.run(string);
    } catch (json::JsonEmptyException const& ex) {
        hypr_log::err("hyprprof.json is empty!");
        std::exit(0);
    }
    catch(json::JsonParseException const& ex)
  {
    hypr_log::err(ex.what());
    std::exit(0);
  }
}

void use_cases::Install::rewrite_config_file()
{
    if (_Paths.has_config_file()) {
    std::string json = fs::file::get_content(_Paths.config_path());
        _GlobalConfig.set_json_context(json);
    }

    _GlobalConfig.set_current_profile(_current_path)
        .set_username(_ProfileModel.name());

    fs::file::overwrite(
        _Paths.config_path(),
        _GlobalConfig.to_string()
    );
}

void use_cases::Install::create_profile_path() {
    try {
        _Paths.create_path(_ProfileModel.name());
    } catch (std::runtime_error const& r) {
        hypr_log::err(r.what());
        std::exit(0);
    }
}

void use_cases::Install::finalize_profile_path() {
  fs::dir::copy(_current_path, _Paths.hyprprof_path());
}

use_cases::Install::Install(const std::string& curr_path) : _current_path(curr_path)
{
    ensure_required_paths();
    ensure_profile_layout(curr_path);
    ensure_manifest_content(fs::file::get_content(profile::ProfileLayout::manifest_path(_current_path)));
    _ProfileModel = _ManifestReader.get_profile();
    _current_profile_path = _Paths.profile_path(_ProfileModel.name());
    create_profile_path();
    finalize_profile_path();
    rewrite_config_file();
    hypr_log::ok("installed.");
}
