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

void Use::change_config_file() 
{
  hypr_log::ok("current profile: ", _profile_name);
  core::ConfigFile::change_current_profile(_profile_name); 
}

void Use::ensure_profile_exists_in_hyprprof_path() {
    if (!core::HyprprofPath::path_exists_in_hyprprof_path(_profile_name)) {
        hypr_log::err("profile doesn't exists in ", core::HyprprofPath::path());
        std::exit(0);
    }

}

void Use::check_config_file() {
    // se já existe um profile ativo
    if (core::ConfigFile::get_current_profile_name().empty()) {
        hypr_log::warn("no profile setted.");
        hypr_log::warn("all current system settings will be queued in ",
                       core::HyprprofPath::backup_path());
        return;
    }

    // se o profile atual é o mesmo que o que está tentando usar
    if (core::ConfigFile::get_current_profile_name() == _profile_name) {
        hypr_log::err("the profile used is the same!");
        std::exit(0);
    }
}


void Use::copy_hypr_path()
{
      hypr_log::log("applying hyprprof...");

    std::string hypr_sys_path = hprof_fs::dotconfig::app_path("hypr");

    if (profile::ProfileLayout::has_hypr_path(_profile_path) &&
        !hprof_fs::dir::is_emp(profile::ProfileLayout::hypr_path(_profile_path)))
    {
        core::BackupHelper::create_copy_backup_path_and_register_in_meta_json(hypr_sys_path);
    }

    hprof_fs::dir::copy(profile::ProfileLayout::hypr_path(_profile_path), hypr_sys_path);
}

void Use::ensure_dotfile_packs()
{
    for (const auto& dot : _manifest.get_dotconfigs())
    {
        const std::string& pack_name = dot.pack();
        hypr_log::log("checking for: ", dot.pack());
        if (!pack_name.empty() && !os::pack_exists(pack_name))
        {
            hypr_log::log("Installing missing package: ", pack_name);
            os::install_pack(pack_name);
        }
    }
}


void Use::copy_waybar_path() {
    hypr_log::log("applying waybar...");
    std::string waybar_sys_path = hprof_fs::dotconfig::app_path("waybar");
    if (profile::ProfileLayout::has_waybar_path(_profile_path) &&
        !hprof_fs::dir::is_emp(profile::ProfileLayout::waybar_path(_profile_path))) {
        core::BackupHelper::create_copy_backup_path_and_register_in_meta_json(waybar_sys_path);
    }

    hprof_fs::dir::copy(profile::ProfileLayout::waybar_path(_profile_path), waybar_sys_path);
}

void Use::copy_dotfile_paths()
{
    for (const auto& dot : _manifest.get_dotconfigs())
    {
        if (!profile::ProfileLayout::has_this_dotfile(_profile_path, dot.source()))
            continue;
        hypr_log::log("applying: ", dot.name());
        std::string src_path = profile::ProfileLayout::concat_dotfile_path(_profile_path, dot.source());

        core::BackupHelper::create_copy_backup_path_and_register_in_meta_json(src_path);
    }
}


Use::Use(const std::string& prof) {
    TimeStamp tm{};
    tm.start();
    _profile_name = prof;
    _profile_path = core::HyprprofPath::concat_str_path(_profile_name);
    ensure_profile_exists_in_hyprprof_path();
    check_config_file();
    _manifest.run(profile::ProfileLayout::manifest_content(_profile_path));
    copy_hypr_path();
    copy_waybar_path();
    ensure_dotfile_packs();
    copy_dotfile_paths();
    change_config_file();
    tm.stop();
    std::cout << "timestamp: " << tm.to_string() << std::endl;

    os::hyprctl::reload();
}
} // namespace use_cases
