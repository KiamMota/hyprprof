#include "appservice/install.hpp"
#include "core/profile_payload.hpp"
#include "infra/fs/dir.hpp"
#include "infra/log.hpp"
#include "infra/sys/hyprctl.hpp"
#include <string>
#include <unistd.h>

std::string app_service::Install::_TraitPath(const std::string& path) const {
    std::string correct_path;
    return correct_path;
}

bool app_service::Install::_ValidateJson() {
    _json_validator.Parse(_payload.manifest_path());

    return true; // <- garante que sempre retorna bool
}

bool app_service::Install::_ValidatePayload() {

    infra::hypr_log::log("validating payload...");

    return true;
}

bool app_service::Install::_ValidateEnvironmentState() const {}
void app_service::Install::_Message() const {
    std::cout << "i run a command and my hyprland changed!" << std::endl;
}

app_service::Install::Install(const std::string& curr_path) : _payload(curr_path) {

    auto res = infra::sys::hyprctl::reload();

    std::cout << "res: " << res.output << std::endl;

    _Message();
}
