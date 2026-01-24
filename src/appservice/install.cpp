#include "appservice/install.hpp"
#include "core/json_current_profile.hpp"
#include "core/json_manifest.hpp"
#include "core/profile/exceptions.hpp"
#include "core/profile/profile.hpp"
#include "infra/fs/dir.hpp"
#include "infra/fs/file.hpp"
#include "infra/log.hpp"
#include "infra/fs/dotconfig.hpp"
#include <stdexcept>
#include <string>
#include <unistd.h>

app_service::Install::Install(const std::string& curr_path) {

    std::string hyprprof_json_path = curr_path + "/hyprprof.json";

    if (!infra::fs::file::exists(hyprprof_json_path)) {
        infra::hypr_log::err("hyprprof.json not found");
        return;
    }
    std::string json_str = infra::fs::file::get_content(hyprprof_json_path);

    core::JsonManifest json_val{json_str};
    try {
        json_val.parse();
    } catch (const std::runtime_error& e) {
        infra::hypr_log::err(e.what(), " (aborted).");
        return;
    }

    core::profile::Profile prof{};
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
        infra::hypr_log::log("created config directory for hyprprof");
    }

    std::string profile_path =
        infra::fs::dotconfig::app_path("hyprprof") + "/" + json_val.profile_name();

    infra::fs::dir::create(profile_path);
    infra::fs::file::move(hyprprof_json_path, profile_path);

  
    core::JsonCurrentProfile curr_prof_json{json_val.profile_name(), profile_path};
    std::string curr_proj = curr_prof_json.get_json();
  
    infra::fs::dotconfig::create(".hyprprof_current.json");
    std::string json_hyprprof_current_path = infra::fs::dotconfig::app_path(".hyprprof_current.json");

    infra::fs::file::overwrite(json_hyprprof_current_path, curr_prof_json.get_json());



    infra::hypr_log::log("end pipeline");
}
