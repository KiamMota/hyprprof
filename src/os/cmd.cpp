#include "os/cmd.hpp"
#include "os/env.hpp"
#include "os/exception.hpp"
#include "utils/log.hpp"

#include <string>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <array>

void ::os::execute_fork(const std::string& command) {
    pid_t pid = fork();

    if(command.empty())
      throw ::os::ForkException("command is empty!"); 
    if (pid < 0) {
        throw ::os::ForkException("failed to create process.");
        return;
    }

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", command.c_str(), nullptr);
        throw ::os::ForkException("failed to execute command.");

        _exit(127);
    } else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            throw ::os::ForkException("failed to wait child process.");
            return;
        }

        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            if (code != 0)
                throw ::os::ForkException("task end with the code: " + code);
        } else {
            throw ::os::ForkException("The children's process ends abnormally.");
        }
    }
}

os::Result os::execute_pipe(const std::string& command) {
    os::Result res;
    std::array<char, 256> buffer;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw ::os::PipeException("failed to open pipe for command: " + command);
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        res.output += buffer.data();
    }

    int status = pclose(pipe);
    if (status == -1) {
        throw ::os::PipeException("failed to close pipe for command: " + command);
    } else if (WIFEXITED(status)) {
        res.error_code = WEXITSTATUS(status);
        if (res.error_code != 0) {
            throw ::os::PipeException(
                "command exited with non-zero code: " + std::to_string(res.error_code));
        }
    } else if (WIFSIGNALED(status)) {
        throw ::os::PipeException(
            "command terminated by signal: " + std::to_string(WTERMSIG(status)));
    }

    // trim newline final se houver
    if (!res.output.empty() && res.output.back() == '\n') {
        res.output.pop_back();
    }

    return res;
}


os::Result os::execute_script(const std::string& script_path) {
    Result res;

    if (script_path.empty()) {
        res.error_code = -1;
        res.output = "";
        return res;
    }

    struct stat st;
    if (stat(script_path.c_str(), &st) != 0) {
        res.error_code = -1; // file doesn't exists
        res.output = "file not found";
        return res;
    }

    if (!(st.st_mode & S_IXUSR)) {
        res = execute_pipe("chmod +x " + script_path);
        if (res.error_code != 0)
            return res;
    }
    return execute_pipe(script_path);
}

void os::install_pack(const std::string &pack)
{
    std::string pkg_mgr = os::detect_package_manager_str();
    std::string cmd;

    if (pkg_mgr == "pacman")       cmd = "sudo pacman -S --noconfirm " + pack;
    else if (pkg_mgr == "apt")     cmd = "sudo apt install -y " + pack;
    else if (pkg_mgr == "dnf")     cmd = "sudo dnf install -y " + pack;
    else if (pkg_mgr == "yum")     cmd = "sudo yum install -y " + pack;
    else if (pkg_mgr == "zypper")  cmd = "sudo zypper install -y " + pack;
    else if (pkg_mgr == "apk")     cmd = "sudo apk add " + pack;
    else if (pkg_mgr == "xbps")    cmd = "sudo xbps-install -Sy " + pack;
    else {
        hypr_log::err("Package manager not supported for installation.");
        return;
    }

    os::execute_pipe(cmd);
}

bool os::pack_exists(const std::string &pack)
{
    std::string pkg_mgr = os::detect_package_manager_str();
    std::string cmd;

    if (pkg_mgr == "pacman")       cmd = "pacman -Q " + pack + " >/dev/null 2>&1";
    else if (pkg_mgr == "apt")     cmd = "dpkg -s " + pack + " >/dev/null 2>&1";
    else if (pkg_mgr == "dnf")     cmd = "dnf list installed " + pack + " >/dev/null 2>&1";
    else if (pkg_mgr == "yum")     cmd = "yum list installed " + pack + " >/dev/null 2>&1";
    else if (pkg_mgr == "zypper")  cmd = "zypper se --installed-only " + pack + " >/dev/null 2>&1";
    else if (pkg_mgr == "apk")     cmd = "apk info " + pack + " >/dev/null 2>&1";
    else if (pkg_mgr == "xbps")    cmd = "xbps-query -l | grep -qx " + pack;
    else {
        hypr_log::err("Package manager not supported for checking package existence.");
        return false;
    }

    return os::execute_pipe(cmd).error_code == 0;
}


