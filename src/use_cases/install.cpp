#include "use_cases/install.hpp"
#include "fs/dir.hpp"
#include "fs/file.hpp"
#include "hyprprof_path.hpp"
#include "net/base.hpp"
#include "net/download.hpp"
#include "profile_layout_helper.hpp"
#include "timestamp.hpp"
#include "utils/log.hpp"
#include "profile/profile_layout_exceptions.hpp"
#include "json/json_exceptions.hpp"
#include "json/json_manifest_reader.hpp"

namespace use_cases {

// Verify that the profile folder structure is correct.
void Install::ensure_profile(const std::string& path) {

    try {
        // Check all required directories and files exist in the profile path.
        profile::ProfileLayoutHelper::check_required_paths(path);
    } catch (profile::ProfileLayoutDirException const& ex) {
        // Log an error if any required directory is missing.
        hypr_log::err(ex.what());
        std::exit(0); // Terminate since the profile cannot be used.
    } catch (profile::ProfileLayoutFileException const& ex) {
        // Log an error if any required file is missing.
        hypr_log::err(ex.what());
        std::exit(0);
    }
}

// Ensure that the main Hyprprof directories exist (like config, backup).
void Install::ensure_required_paths() { core::HyprprofPath::create_required_paths(); }

// Validate that the profile manifest (hyprprof.json) is readable and correct.
void Install::ensure_manifest_content(const std::string& string) {
    try {
        // Parse the manifest JSON and load it into the manifest reader.
        _ManifestReader.run(string);
    } catch (json::JsonEmptyException const& ex) {
        // If the JSON is empty, log and abort.
        hypr_log::err("hyprprof.json is empty!");
        std::exit(0);
    } catch (json::JsonParseException const& ex) {
        // If the JSON is malformed, log the parsing error and abort.
        hypr_log::err(ex.what());
        std::exit(0);
    }
}

// Create the folder for the profile inside the Hyprprof directory.
void Install::create_profile_path(bool overwrite) {
    try {
        // Attempt to create a folder for the profile.
        core::HyprprofPath::create_path_in_hyprprof_path(_ProfileModel.name(), overwrite);
    } catch (std::runtime_error const& r) {
        // Log any errors and suggest using --overwrite if the folder already exists.
        hypr_log::err(r.what());
        hypr_log::log("to overwrite profile, use --overwrite");
        std::exit(0);
    }
}

// Copy the profile files from the source location to the Hyprprof path.
void Install::finalize_profile_path() {
    hprof_fs::dir::copy(_current_path, _profile_path_in_hyprprof_path);
}

// Constructor orchestrates the entire installation process.
Install::Install(const std::string& curr_path, bool overwrite)
    : _current_path(hprof_fs::dir::get_absolute(curr_path)) // Resolve absolute path of source.
{
    TimeStamp tm{}; // Start a timer for profiling installation duration.
    tm.start();

    std::cout << "path: " << curr_path << std::endl;

    ensure_required_paths();
    ensure_profile(curr_path);

    // Load and parse the profile manifest JSON.
    ensure_manifest_content(
        hprof_fs::file::get_content(profile::ProfileLayoutHelper::manifest_path(_current_path)));

    // Extract profile metadata (name, authors, dotfiles, etc.) from manifest.
    _ProfileModel = _ManifestReader.get_profile();

    // Compute the path where the profile will reside inside Hyprprof.
    _profile_path_in_hyprprof_path = core::HyprprofPath::concat_str_path(_ProfileModel.name());

    create_profile_path(overwrite); // Create the profile folder (with overwrite option if needed).
    finalize_profile_path();        // Copy the profile files into the Hyprprof path.

    tm.stop(); // Stop the timer.

    // Log the installation result and duration.
    hypr_log::ok("installed.");
    std::cout << "completed in: " << tm.to_string() << std::endl;
    std::cout << "profile created in: " << core::HyprprofPath::concat_str_path(_ProfileModel.name())
              << std::endl;
    std::cout << "to use: hyprprof use " << _ProfileModel.name() << std::endl;
}

} // namespace use_cases
