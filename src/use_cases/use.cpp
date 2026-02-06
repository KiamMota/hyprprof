#include "use_cases/use.hpp"
#include "backup_helper.hpp"
#include "config_file.hpp"
#include "fs/dir.hpp"
#include "fs/dotconfig.hpp"
#include "hyprprof_path.hpp"
#include "os/hyprctl.hpp"
#include "profile_layout.hpp"
#include "timestamp.hpp"
#include "utils/log.hpp"
#include <cstdlib>

namespace use_cases {

// Change the currently active profile in the configuration file to this profile.
void Use::change_config_file() 
{
  if(core::ConfigFile::get_content().empty())
  {
    core::ConfigFile::create_file_content("", "");
  }
    // Log which profile is currently being set.
    hypr_log::ok("current profile: ", _profile_name);

    // Update the configuration file to record the new active profile.
    core::ConfigFile::change_current_profile(_profile_name); 
}

// Ensures that the profile exists in the Hyprprof directory before proceeding.
void Use::ensure_profile_exists_in_hyprprof_path() {
    // If the profile folder does not exist inside the Hyprprof root path:
    if (!core::HyprprofPath::path_exists_in_hyprprof_path(_profile_name)) {
        // Log an error indicating the profile is missing.
        hypr_log::err("profile doesn't exists in ", core::HyprprofPath::path());

        // Terminate the program immediately since the profile is required.
        std::exit(0);
    }
}

// Check if there is a configuration file and if the requested profile can be used.
void Use::check_config_file() {
    // If there is no current profile set:
    if(core::ConfigFile::get_content().empty())
    {
      hypr_log::warn("no profile setted");
    core::ConfigFile::create_file_content("", "");
      return;
    }
    if (core::ConfigFile::get_current_profile_name().empty()) {
        // Warn the user that no profile is set.
        hypr_log::warn("no profile setted.");

        // Warn that all current system settings will be backed up.
        hypr_log::warn("all current system settings will be queued in ",
                       core::HyprprofPath::backup_path());
        return;
    }

    // If the current profile is the same as the one being requested:
    if (core::ConfigFile::get_current_profile_name() == _profile_name) {
        // Log an error to prevent reloading the same profile.
        hypr_log::err("the profile used is the same!");

        // Exit the program to avoid redundant operations.
        std::exit(0);
    }
}

// Copy the Hypr configuration files from the profile to the system directory.
void Use::copy_hypr_path()
{
    // Inform the user that the Hypr profile is being applied.
    hypr_log::log("applying hyprprof...");

    // Get the system path where Hypr configurations are stored.
    std::string hypr_sys_path = hprof_fs::dotconfig::app_path("hypr");

    // If the profile contains Hypr configs and they are not empty:
    if (profile::ProfileLayout::has_hypr_path(_profile_path) &&
        !hprof_fs::dir::is_emp(profile::ProfileLayout::hypr_path(_profile_path)))
    {
        // Backup the current system Hypr configs before applying the new profile.
        core::BackupHelper::create_copy_backup_path_and_register_in_meta_json("hypr", hypr_sys_path);
    }

    // Copy the Hypr configuration from the profile to the system path.
    hprof_fs::dir::copy(profile::ProfileLayout::hypr_path(_profile_path), hypr_sys_path);
}

// Ensure that all required packages for dotfiles are installed.
void Use::ensure_dotfile_packs()
{
    // Iterate through all dotfiles listed in the profile's manifest.
    for (const auto& dot : _manifest.get_dotconfigs())
    {
        const std::string& pack_name = dot.pack();

        // Log which package is being checked.
        hypr_log::log("checking for: ", dot.pack());

        // If the package is specified and does not exist on the system:
        if (!pack_name.empty() && !os::pack_exists(pack_name))
        {
            // Log that the package will be installed.
            hypr_log::log("Installing missing package: ", pack_name);

            // Install the package using the system's package manager.
            os::install_pack(pack_name);
        }
    }
}

// Copy the Waybar configuration from the profile to the system directory.
void Use::copy_waybar_path() {
    // Log that Waybar configurations are being applied.
    hypr_log::log("applying waybar...");

    // Get the system path where Waybar configs are stored.
    std::string waybar_sys_path = hprof_fs::dotconfig::app_path("waybar");

    // If the profile contains Waybar configs and they are not empty:
    if (profile::ProfileLayout::has_waybar_path(_profile_path) &&
        !hprof_fs::dir::is_emp(profile::ProfileLayout::waybar_path(_profile_path))) {
        // Backup current Waybar configs before applying the new profile.
        core::BackupHelper::create_copy_backup_path_and_register_in_meta_json("waybar", waybar_sys_path);
    }

    // Copy Waybar configuration from the profile to the system directory.
    hprof_fs::dir::copy(profile::ProfileLayout::waybar_path(_profile_path), waybar_sys_path);
}

// Copy all dotfile paths from the profile to the system directory.
void Use::copy_dotfile_paths()
{
    // Iterate through each dotfile in the manifest.
    for (const auto& dot : _manifest.get_dotconfigs())
    {
        // Skip dotfiles that do not actually exist in the profile directory.
        if (!profile::ProfileLayout::has_this_dotfile(_profile_path, dot.source()))
            continue;

        // Log the dotfile being applied.
        hypr_log::log("applying: ", dot.name());

        // Determine the full source path of the dotfile in the profile.
        std::string src_path = profile::ProfileLayout::concat_dotfile_path(_profile_path, dot.source());

        // Backup and copy the dotfile to the system directory.
        core::BackupHelper::create_copy_backup_path_and_register_in_meta_json(dot.name(), dot.target());
    }
}

// Constructor for the Use class, which applies a profile completely.
Use::Use(const std::string& prof) {
    // Create a timestamp to measure how long profile application takes.
    TimeStamp tm{};
    tm.start();

    // Store the profile name.
    _profile_name = prof;

    // Compute the absolute path to the profile directory.
    _profile_path = core::HyprprofPath::concat_str_path(_profile_name);

    std::cout << profile::ProfileLayout::manifest_content(_profile_path);

    // Ensure the profile exists on disk.
    ensure_profile_exists_in_hyprprof_path();

    // Check for conflicting or missing configuration files.
    check_config_file();

    // Load the profile's manifest JSON.
    _manifest.run(profile::ProfileLayout::manifest_content(_profile_path));

    // Copy and backup Hypr configuration.
    copy_hypr_path();

    // Copy and backup Waybar configuration.
    copy_waybar_path();

    // Install any required packages for dotfiles.
    ensure_dotfile_packs();

    // Copy all dotfiles from the profile to the system directory.
    copy_dotfile_paths();

    // Update the current profile in the configuration file.
    change_config_file();

    // Stop the timestamp and print the elapsed time.
    tm.stop();
    std::cout << "timestamp: " << tm.to_string() << std::endl;

    // Reload Hypr with the new configuration.
    os::hyprctl::reload();
}

} // namespace use_cases

