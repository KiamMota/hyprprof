#include "net/download.hpp"
#include "fs/dir.hpp"
#include "net/base.hpp"
#include "os/cmd.hpp"

static bool is_git(const std::string& url) { return url.find("https://github.com") ? true : false; }

namespace net {

const std::string download_with_git(const std::string& url) {
    check_url(url);

    if (!is_git(url)) {
        throw std::invalid_argument("URL não é um repositório Git válido.");
    }

    // Extrai o nome do projeto a partir da URL
    std::string repo_name = url.substr(url.find_last_of('/') + 1);
    if (repo_name.size() > 4 && repo_name.substr(repo_name.size() - 4) == ".git") {
        repo_name = repo_name.substr(0, repo_name.size() - 4);
    }

    os::pipe(("git clone " + url).c_str());

    return hprof_fs::dir::get_absolute(repo_name);
}
} // namespace net
