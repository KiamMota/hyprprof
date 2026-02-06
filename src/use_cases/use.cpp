#include "use_cases/use.hpp"
#include "config_file.hpp"
#include "hyprprof_path.hpp"
#include "utils/log.hpp"
#include <cstdlib>

namespace use_cases {

void Use::ensure_profile_exists_in_hyprprof_path() {
    if (!core::HyprprofPath::path_exists_in_hyprprof_path(_profile)) {
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
Use::Use(const std::string& prof) {
    _profile = prof;
    ensure_profile_exists_in_hyprprof_path();
    check_first_time_using_hyprprof();
}

} // namespace use_cases
