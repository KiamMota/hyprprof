#include "core/profile_payload.hpp"
#include "infra/fs/dir.hpp"
#include <stdexcept>
#include <string>

core::profile_payload::profile_payload(const std::string& path) {
    if (path.empty())
        throw std::runtime_error("path is empty!");
    if (!infra::fs::dir::is_dir(path))
        throw std::runtime_error("path is not a directory!");

    _absolutePath = infra::fs::dir::get_absolute(path);

    _jsonManifestPath = _absolutePath + "/" + "hyprprof.json";
    _payloadPath = _absolutePath + "/" + "payload";
    _scriptsPath = _absolutePath + "/" + "scripts";
}

std::string core::profile_payload::manifest_path() const { return _jsonManifestPath; }
std::string core::profile_payload::payload_path() const { return _payloadPath; }
std::string core::profile_payload::scripts_path() const { return _scriptsPath; }
