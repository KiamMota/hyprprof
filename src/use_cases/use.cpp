#include "use_cases/use.hpp"
#include "backup_helper.hpp"
#include "config_file.hpp"
#include "fs/dotconfig.hpp"
#include "fs/file.hpp"
#include "hyprprof_path.hpp"
#include "os/hyprctl.hpp"
#include "profile_layout.hpp"
#include "timestamp.hpp"
#include "utils/log.hpp"
#include <cstdlib>

namespace use_cases {

void Use::ensure_profile_exists_in_hyprprof_path() {
    if (!core::HyprprofPath::path_exists_in_hyprprof_path(_profile_name)) {
        hypr_log::err("profile doesn't exists in ", core::HyprprofPath::path());
        std::exit(0);
    }
}

void Use::check_first_time_using_hyprprof() {
    if (!core::ConfigFile::get_current_profile_name().empty()) {
        return;
    }
    hypr_log::warn("no profile setted.");
    hypr_log::warn("all current system settings will be queued in ",
                   core::HyprprofPath::path() + "/_bak");

  }

void Use::copy_hypr_path()
{
  if(profile::ProfileLayout::has_hypr_path(_profile_path))
    core::BackupHelper::create_copy_backup_path_and_register_in_meta_json(hprof_fs::dotconfig::app_path("hypr"));
}

void Use::copy_waybar_path()
{
  if(profile::ProfileLayout::has_waybar_path(_profile_path))
    core::BackupHelper::create_copy_backup_path_and_register_in_meta_json(hprof_fs::dotconfig::app_path("waybar"));
}

void Use::copy_dotfile_paths()
{
    std::string base_path = _profile_path + "/config/dotfiles";

    for (const auto& dot : _manifest.get_dotconfigs())
    {
        std::string src_path = base_path + "/" + dot.source(); 
        core::BackupHelper::create_copy_backup_path_and_register_in_meta_json(src_path);
    }
}

Use::Use(const std::string& prof)
{
  TimeStamp tm{};
  tm.start();
    _profile_name = prof;
    _profile_path = core::HyprprofPath::concat_str_path(_profile_path);
    ensure_profile_exists_in_hyprprof_path();
    check_first_time_using_hyprprof();
    _manifest.run(hprof_fs::file::get_content(_profile_path));
    copy_hypr_path();
    copy_waybar_path();
    copy_dotfile_paths();
  tm.stop();
    std::cout << "timestamp: " << tm.to_string() << std::endl;

  os::hyprctl::reload();

}
} // namespace use_cases
