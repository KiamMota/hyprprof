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

void use_cases::Install::ensure_required_paths() { core::HyprprofPath::create_required_paths(); }

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
    if (core::ConfigFile::get_config_content().empty()) {
        core::ConfigFile::create_file_content("", _ProfileModel.name());
        return;
    }
    core::ConfigFile::change_current_profile(_ProfileModel.name());
}

void use_cases::Install::create_profile_path(bool overwrite) {
    try {
        core::HyprprofPath::create_path_in_hyprprof_path(_ProfileModel.name(), overwrite);
    } catch (std::runtime_error const& r) {
        hypr_log::err(r.what());
        hypr_log::log("to overwrite profile, use --overwrite");
        std::exit(0);
    }
}

void use_cases::Install::finalize_profile_path() {
    hprof_fs::dir::copy(_current_path, _profile_path_in_hyprprof_path);
}

use_cases::Install::Install(const std::string& curr_path, bool overwrite)
    : _current_path(hprof_fs::dir::get_absolute(curr_path)) {

    TimeStamp tm{};
    tm.start();
    ensure_required_paths();
    ensure_profile_layout(curr_path);
    ensure_manifest_content(
        hprof_fs::file::get_content(profile::ProfileLayout::manifest_path(_current_path)));
    _ProfileModel = _ManifestReader.get_profile();
    _profile_path_in_hyprprof_path = core::HyprprofPath::concat_str_path(_ProfileModel.name());
    create_profile_path(overwrite);
    finalize_profile_path();
    rewrite_config_file();
    tm.stop();
    hypr_log::ok("installed.");
    std::cout << "completed in: " << tm.to_string() << std::endl;
    std::cout << "profile created in: " << core::HyprprofPath::concat_str_path(_ProfileModel.name())
              << std::endl;
    std::cout << "to use: hyprprof use " << _ProfileModel.name() << std::endl;
}
