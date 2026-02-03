#include "use_cases/install.hpp"
#include "infra/fs/dir.hpp"
#include "infra/fs/file.hpp"
#include "infra/log.hpp"
#include "profile/profile_layout.hpp"
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
        _profile_lay.set_path(path);
    } catch (profile::ProfileLayoutDirException const& ex) {
        infra::hypr_log::err(ex.what());
      std::exit(0);
    } catch (profile::ProfileLayoutFileException const& ex) {
        infra::hypr_log::err(ex.what());
      std::exit(0);
    }
}

void use_cases::Install::ensure_important_paths() {
    if (!_hyprprof_path.path_exists())
        infra::fs::dir::create(_hyprprof_path.hyprprof_path());
    if (!_hyprprof_path.has_profile_list())
        infra::fs::file::create(_hyprprof_path.profile_list_path());
}

void use_cases::Install::ensure_manifest(const std::string& string) {
    try
  {
    _json_reader.set_json_string(string);
    _json_reader.run();
  }
  catch(json::JsonEmptyException const& ex)
  {
    infra::hypr_log::err("hyprprof.json is empty!");
    std::exit(0);
  } 
}

void use_cases::Install::rewrite_profile_list()
{
  if(!_hyprprof_path.has_profile_list())
  {
    _hyprprof_path.create_profile_list();
    std::string json = _profile_list_json.json_append(_profile.name(), _current_profile_path);
    infra::fs::file::overwrite(_hyprprof_path.profile_list_path(), json);
    return;
  }

  _profile_list_json.set_existing_json(infra::fs::file::get_content(_hyprprof_path.profile_list_path()));
  _profile_list_json.json_append(_profile.name(), _hyprprof_path.profile_path(_profile.name()));
}

void use_cases::Install::create_path() {
    try {
        _hyprprof_path.create_path(_profile.name());
    } catch (std::runtime_error const& r) {
        infra::hypr_log::err(r.what());
      std::exit(0);
    }
}

void use_cases::Install::move_profile_to_path() {
  _profile_lay.move_profile_to(_current_profile_path);
}

use_cases::Install::Install(const std::string& curr_path) // inicializa ProfileLayout
{
    ensure_profile_layout(curr_path);
    ensure_manifest(infra::fs::file::get_content(_profile_lay.manifest_path()));
    _profile = _json_reader.get_profile();
    _current_profile_path = _hyprprof_path.profile_path(_profile.name());
    ensure_important_paths();
    create_path();
    move_profile_to_path();
    rewrite_profile_list();
    infra::fs::dir::remove(curr_path);
    infra::hypr_log::ok("profile installed!");
}
