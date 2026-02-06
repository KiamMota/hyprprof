#include "hyprprof_path.hpp"
#include "fs/dir.hpp"
#include "fs/dotconfig.hpp"
#include "fs/file.hpp"
#include <filesystem>
#include <list>
#include <stdexcept>
#include <string>

core::HyprprofPath::HyprprofPath() {}

const std::string core::HyprprofPath::path() noexcept {
    return hprof_fs::dotconfig::get_config_path() + "/hyprprof";
}
const std::string core::HyprprofPath::config_path() noexcept {
    return hprof_fs::dotconfig::get_config_path() + "/hyprprof/.config.json";
}

const std::string core::HyprprofPath::backup_path() noexcept { return path() + "/.backup"; }

bool core::HyprprofPath::path_exists_in_hyprprof_path(const std::string& path) noexcept {
    return hprof_fs::dir::exists(hprof_fs::dotconfig::get_config_path() + "/hyprprof/" + path);
}

void core::HyprprofPath::create_path_in_hyprprof_path(const std::string& name, bool overwrite) {
    if (hprof_fs::dir::exists(hprof_fs::dotconfig::get_config_path() + "/hyprprof/" + name) &&
        overwrite == false)
        throw std::runtime_error("path named '" + name + "' already exists in " +
                                 HyprprofPath::path());

    hprof_fs::dir::remove(hprof_fs::dotconfig::get_config_path() + "/hyprprof/" + name);
    hprof_fs::dir::create(hprof_fs::dotconfig::get_config_path() + "/hyprprof/" + name);
}

const std::string core::HyprprofPath::concat_str_path(const std::string& path) noexcept {
    return hprof_fs::dotconfig::get_config_path() + "/hyprprof/" + path;
}

std::list<std::string> core::HyprprofPath::profile_paths() noexcept {
    std::list<std::string> profile_paths;
    for (const auto& p : std::filesystem::directory_iterator{HyprprofPath::path()}) {
        if (p.is_directory()) {
            std::string name = p.path().filename().string();
            if (!name.empty() && name[0] != '.') { // ignora diretórios que começam com '.'
                profile_paths.push_back(name);
            }
        }
    }

    return profile_paths;
}

void core::HyprprofPath::create_required_paths() {

    std::string config_path = path() + "/.config.json";
    std::string _bak_path = path() + "/.backup/";
    std::string backup_meta_json = path() + "/.backup/.meta.json";

    if(!hprof_fs::dir::exists(HyprprofPath::path()))
      hprof_fs::dir::create(HyprprofPath::path());

    if (!hprof_fs::file::exists(config_path))
        hprof_fs::file::create(config_path);
    if (!hprof_fs::dir::exists(_bak_path))
        hprof_fs::dir::create(_bak_path);
    if (!hprof_fs::file::exists(backup_meta_json))
        hprof_fs::file::create(backup_meta_json);
}
