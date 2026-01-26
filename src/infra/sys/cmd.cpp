#include "infra/sys/cmd.hpp"
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <array>
#include "infra/log.hpp"

void infra::sys::execute_fork(const std::string& command) {
    pid_t pid = fork();
    if (pid < 0) {
    hypr_log::err("failed to create process.");
        return;
    }

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", command.c_str(), nullptr);
    hypr_log::err("failed to execute command.");

        _exit(127);
    } else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
      hypr_log::err("failed to wait child process.");
            return;
        }

        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            if (code != 0)
                hypr_log::err("task end with the code: ", code);
        } else {
          hypr_log::err("The children's process ends abnormally.");
        }
    }
}

infra::sys::Result infra::sys::execute_pipe(const std::string& command) {
    infra::sys::Result res;
    std::array<char, 256> buffer;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        res.error_code = -1; // failed to open pipe
        res.output = "";
        return res;
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        res.output += buffer.data();
    }

    int status = pclose(pipe);
    if (status == -1) {
        res.error_code = -1;
    } else if (WIFEXITED(status)) {
        res.error_code = WEXITSTATUS(status);
    } else {
        res.error_code = -1;
    }

    // trim newline final se houver
    if (!res.output.empty() && res.output.back() == '\n') {
        res.output.pop_back();
    }

    return res;
}


infra::sys::Result infra::sys::execute_script(const std::string& script_path) {
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


