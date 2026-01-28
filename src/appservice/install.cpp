#include "appservice/install.hpp"
#include "core/current_profile.hpp"
#include "core/json/json_manifest_reader.hpp"
#include "core/json/json_manifest_reader.hpp"
#include "core/json/json_profile_list_writer.hpp"
#include "core/profile/exceptions.hpp"
#include "core/profile/profile_assembler.hpp"
#include "infra/fs/dir.hpp"
#include "infra/fs/file.hpp"
#include "infra/log.hpp"
#include "infra/fs/dotconfig.hpp"
#include <fstream>
#include <stdexcept>
#include <string>
#include <unistd.h>

void app_service::Install::ensure_important_paths()
{
    const std::string hyprprof_dir = infra::fs::dotconfig::app_path("hyprprof");

}

app_service::Install::Install(const std::string& curr_path) {
    using namespace infra::fs;

    // -----------------------------
    // Variables
    // -----------------------------
    const std::string hyprprof_dir = dotconfig::app_path("hyprprof");
    const std::string hyprprof_json_path = dir::get_absolute(curr_path) + "/hyprprof.json";
    const std::string profile_list_path = hyprprof_dir + "/profile_list.json";
    std::string json_str;
    std::string dest_profile_json;
    std::string profile_dir;
    core::json::JSONManifestReader json_val{infra::fs::file::get_content(profile_list_path)};
    core::profile::ProfileAssembler prof{};
    core::CurrentProfile current_profile{};
    core::json::JSONProfileListWriter writer{infra::fs::file::get_content(profile_list_path)};
    std::string current_profile_json;

    // -----------------------------
    // Check if the profile JSON exists
    // -----------------------------
    if (!file::exists(hyprprof_json_path)) {
        infra::hypr_log::err(hyprprof_json_path + " doesn't exist.");
        return;
    }

    // -----------------------------
    // Read the JSON content
    // -----------------------------
    json_str = file::get_content(hyprprof_json_path);
    json_val = core::json::JSONManifestReader{json_str};
    try {
        json_val.parse();
    } catch (const std::runtime_error& e) {
        infra::hypr_log::err(e.what(), " (aborted).");
        return;
    }

    // -----------------------------
    // Build the profile
    // -----------------------------
    try {
        prof = json_val.GetProfile();
    } catch (const core::profile::EmptyFieldException& ex) {
        infra::hypr_log::err(ex.what(), " https://github.com/KiamMota/hyprprof/blob/main/doc/json.md (aborted).");
        return;
    } catch (const core::profile::InvalidPatternException& ex) {
        infra::hypr_log::err(ex.what(), " https://github.com/KiamMota/hyprprof/blob/main/doc/json.md (aborted).");
        return;
    }

    // -----------------------------
    // Ensure the base directory exists
    // -----------------------------
    if (!dir::exists(hyprprof_dir))
        dir::create(hyprprof_dir);

    // -----------------------------
    // Create profile directory
    // -----------------------------
    profile_dir = hyprprof_dir + "/" + json_val.profile_name();
    dir::create(profile_dir);

    // -----------------------------
    // Move JSON into profile directory
    // -----------------------------
    dest_profile_json = profile_dir + "/hyprprof.json";
    file::move(hyprprof_json_path, dest_profile_json);

    // -----------------------------
    // Update CurrentProfile object
    // -----------------------------
    current_profile.set_current_path(dest_profile_json);
    current_profile.set_profile_name(json_val.profile_name());

    // -----------------------------
    // Generate JSON for profile list
    // -----------------------------
    current_profile_json = writer.make_json(
        current_profile.name(),
        current_profile.path()
    );

    // -----------------------------
    // Ensure profile list file exists and overwrite
    // -----------------------------
    if (!file::exists(profile_list_path))
        std::ofstream(profile_list_path).close();

    file::overwrite(profile_list_path, current_profile_json);

    // -----------------------------
    // Logs
    // -----------------------------
    infra::hypr_log::ok("Profile installed!");
    infra::hypr_log::log("To use the profile: hyprprof use");
}

