#include "appservice/install.hpp"
#include "core/profile/profile_layout.hpp"
#include "infra/fs/dir.hpp"
#include "infra/fs/file.hpp"
#include "infra/log.hpp"
#include <string>
#include <unistd.h>

void app_service::Install::ensure_important_paths() {
    if (!_hyprprof_path_obj.path_exists())
        infra::fs::dir::create(_hyprprof_path_obj.hyprprof_path());
    if (!_hyprprof_path_obj.profile_list_exists())
        infra::fs::file::create(_hyprprof_path_obj.profile_list_path());
}

app_service::Install::Install(const std::string& curr_path)
    : _profile_lay(curr_path) // inicializa ProfileLayout
{

    std::string json_content = infra::fs::file::get_content(_profile_lay.manifest_path());
    infra::hypr_log::log("getting json content...");
    _json_reader.set_json_str(json_content);
    infra::hypr_log::log("parsing...");
    _json_reader.parse();
    _profile_domain = _json_reader.get_profile();
    infra::hypr_log::log("ensuring files...");
    ensure_important_paths();
    std::string profile_target_dir =
        _hyprprof_path_obj.hyprprof_path() + "/" + _profile_domain.name();
    if (!infra::fs::dir::exists(profile_target_dir))
        infra::fs::dir::create(profile_target_dir);

    infra::fs::file::move(curr_path + "/hyprprof.json", profile_target_dir);
    infra::hypr_log::ok("profile installed without errors. accessible at: " + profile_target_dir);
}
