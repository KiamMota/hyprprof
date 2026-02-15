#include "use_cases/internet_install.hpp"
#include "fs/dir.hpp"
#include "fs/file.hpp"
#include "net/base.hpp"
#include "net/download.hpp"
#include "use_cases/install.hpp"
#include "utils/log.hpp"

namespace use_cases {
InternetInstall::InternetInstall() {}
void InternetInstall::install(const std::string& url) {
    if (!net::is_url(url))
        return;
    Install inst;
    std::string abs_path = net::download_with_git(url);
    if (hprof_fs::file::exists(abs_path + "/hyprprof.json")) {
        inst.install(abs_path, false);
        return;
    }
    hypr_log::err("hyprprof.json doesn't exists");
    hprof_fs::dir::remove(abs_path);
}

} // namespace use_cases
