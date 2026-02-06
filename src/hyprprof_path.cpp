#include "hyprprof_path.hpp"
#include "fs/dir.hpp"
#include "fs/dotconfig.hpp"
#include "fs/file.hpp"
#include <stdexcept>

core::HyprprofPath::HyprprofPath() {}

const std::string core::HyprprofPath::path() noexcept {
    return fs::dotconfig::get_config_path() + "/hyprprof";
}
const std::string core::HyprprofPath::config_path() noexcept {
    return fs::dotconfig::get_config_path() + "/hyprprof/config.json";
}

const std::string core::HyprprofPath::bak_path() noexcept
{
  return path() + "/.bak";
}

bool core::HyprprofPath::path_exists_in_hyprprof_path(const std::string& path) noexcept {
    return fs::dir::exists(fs::dotconfig::get_config_path() + "/hyprprof/" + path);
}

bool core::HyprprofPath::has_config_file() noexcept {
    return fs::file::exists(fs::dotconfig::get_config_path() + "/hyprprof/config.json");
}

void core::HyprprofPath::create_path_in_hyprprof_path(const std::string& name, bool overwrite) {
    if (fs::dir::exists(fs::dotconfig::get_config_path() + "/hyprprof/" + name) &&
        overwrite == false)
        throw std::runtime_error("path named '" + name + "' already exists in " + HyprprofPath::path());

    fs::dir::remove(fs::dotconfig::get_config_path() + "/hyprprof/" + name);
    fs::dir::create(fs::dotconfig::get_config_path() + "/hyprprof/" + name);
}

const std::string core::HyprprofPath::build_path(const std::string& path) noexcept {
    return fs::dotconfig::get_config_path() + "/hyprprof/" + path;
}

void core::HyprprofPath::create_required_paths() {
    std::string config_path = path() + "/config.json";
    std::string _bak_path = path() + "/_bak/";

    if (!fs::file::exists(config_path))
        fs::file::create(config_path);
    if (!fs::dir::exists(_bak_path))
        fs::dir::create(_bak_path);
}
