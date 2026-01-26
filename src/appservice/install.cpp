#include "appservice/install.hpp"
#include "core/current_profile.hpp"
#include "core/json/json_manifest_reader.hpp"
#include "core/json_current_profile.hpp"
#include "core/json/json_manifest_reader.hpp"
#include "core/profile/exceptions.hpp"
#include "core/profile/profile.hpp"
#include "core/profile/profile_assembler.hpp"
#include "infra/fs/dir.hpp"
#include "infra/fs/file.hpp"
#include "infra/log.hpp"
#include "infra/fs/dotconfig.hpp"
#include <stdexcept>
#include <string>
#include <unistd.h>

app_service::Install::Install(const std::string& curr_path) {

    std::string hyprprof_json_path = infra::fs::dir::get_absolute(curr_path) + "/hyprprof.json";
    if(!infra::fs::dir::is_dir(hyprprof_json_path))
    {
      infra::hypr_log::err(hyprprof_json_path + " doesn't exist.");
    return;
    }
    if (!infra::fs::file::exists(hyprprof_json_path)) {
        infra::hypr_log::err("hyprprof.json not found");
        return;
    }
    std::string json_str = infra::fs::file::get_content(hyprprof_json_path);

    core::json::JSONManifestReader json_val{json_str};
    try {
        json_val.parse();
    } catch (const std::runtime_error& e) {
        infra::hypr_log::err(e.what(), " (aborted).");
        return;
    }

    core::profile::ProfileAssembler prof{};
    try {
        prof = json_val.GetProfile();
    } catch (const core::profile::EmptyFieldException& ex) {
        infra::hypr_log::err(ex.what(), " https://github.com/KiamMota/hyprprof/blob/main/doc/"
                                        "json.md for more details. (aborted).");
        return;
    }

    catch (const core::profile::InvalidPatternException& ex) {
        infra::hypr_log::err(ex.what(), " https://github.com/KiamMota/hyprprof/blob/main/doc/"
                                        "json.md for more details. (aborted).");
        return;
    }

    if (!infra::fs::dotconfig::exists("hyprprof")) {
        infra::fs::dotconfig::create("hyprprof");
    }

    std::string profile_path =
        infra::fs::dotconfig::app_path("hyprprof") + "/" + json_val.profile_name();

    infra::fs::dir::create(profile_path);
    infra::fs::file::move(hyprprof_json_path, profile_path);

 
    core::CurrentProfile current_profile{};
    current_profile.set_current_path(hyprprof_json_path);
    current_profile.set_profile_name(profile_path);

    core::JsonCurrentProfile curr_prof_json{};
    std::string curr_proj = curr_prof_json.make_json(hyprprof_json_path, profile_path);
  
    infra::fs::dotconfig::create(".hyprprof_current.json");
    std::string json_hyprprof_current_path = infra::fs::dotconfig::app_path(".hyprprof_current.json");

    infra::fs::file::overwrite(json_hyprprof_current_path, curr_proj);


    infra::hypr_log::ok("profile installed!");
    infra::hypr_log::log("to use the profile: hyprprof use");
}
