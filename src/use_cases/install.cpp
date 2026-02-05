#include "use_cases/install.hpp"
#include "fs/dir.hpp"
#include "fs/file.hpp"
#include "hyprprof_path.hpp"
#include "profile_layout.hpp"
#include "timestamp.hpp"
#include "utils/log.hpp"
#include "profile/profile_layout_exceptions.hpp"
#include "json/json_exceptions.hpp"
#include "json/json_manifest_reader.hpp"
#include <bits/types/cookie_io_functions_t.h>
#include <cstdlib>
#include <iostream>
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
    if (!core::HyprprofPath::path_exists_in_hyprprof_path(_ProfileModel.name()))
        fs::dir::create(core::HyprprofPath::hyprprof_path());
    if (!core::HyprprofPath::has_config_file())
        fs::file::create(core::HyprprofPath::config_path());
}

void use_cases::Install::ensure_manifest_content(const std::string& string) {
    try {
        _ManifestReader.run(string);
    } catch (json::JsonEmptyException const& ex) {
        hypr_log::err("hyprprof.json is empty!");
        std::exit(0);
    } catch (json::JsonParseException const& ex) {
        hypr_log::err(ex.what());
        std::exit(0);
    }
}

void use_cases::Install::rewrite_config_file() {
    if (core::HyprprofPath::has_config_file()) {
        std::string json = fs::file::get_content(core::HyprprofPath::config_path());
        _GlobalConfig.set_json_context(json);
    }

    _GlobalConfig.set_current_profile(_current_path).set_username(_ProfileModel.name());

    fs::file::overwrite(core::HyprprofPath::config_path(), _GlobalConfig.to_string());
}

void use_cases::Install::create_profile_path(bool overwrite) {
    try {
        core::HyprprofPath::create_path(_ProfileModel.name(), overwrite);
    } catch (std::runtime_error const& r) {
        hypr_log::err(r.what());
        hypr_log::log("to overwrite profile, use --overwrite");
        std::exit(0);
    }
}

void use_cases::Install::finalize_profile_path() {
    fs::dir::copy(_current_path, _current_profile_path); // _current_profile_path = ~/.config/hyprprof/omniarch
}


use_cases::Install::Install(const std::string& curr_path, bool overwrite)
    : _current_path(fs::dir::get_absolute(curr_path)) {

    std::cout << _current_path << std::endl;
    TimeStamp tm{};
    tm.start();
    ensure_required_paths();
    ensure_profile_layout(curr_path);
    ensure_manifest_content(
        fs::file::get_content(profile::ProfileLayout::manifest_path(_current_path)));
    _ProfileModel = _ManifestReader.get_profile();
    _current_profile_path = core::HyprprofPath::get_path(_ProfileModel.name());
    create_profile_path(overwrite);
    finalize_profile_path();
    rewrite_config_file();
    tm.stop();
    hypr_log::ok("installed.");
    std::cout << "completed in: " << tm.to_string() << std::endl;
    std::cout << "profile created in: " << core::HyprprofPath::get_path(_ProfileModel.name()) << std::endl;
    std::cout << "to use: hyprprof use " << _ProfileModel.name() << std::endl;
}
