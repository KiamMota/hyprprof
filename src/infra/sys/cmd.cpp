#include "infra/sys/cmd.hpp"
#include "infra/sys/exception.hpp"

#include <string>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <array>

void infra::sys::execute_fork(const std::string& command) {
    pid_t pid = fork();

    if(command.empty())
      throw infra::sys::ForkException("command is empty!"); 
    if (pid < 0) {
        throw infra::sys::ForkException("failed to create process.");
        return;
    }

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", command.c_str(), nullptr);
        throw infra::sys::ForkException("failed to execute command.");

        _exit(127);
    } else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            throw infra::sys::ForkException("failed to wait child process.");
            return;
        }

        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            if (code != 0)
                throw infra::sys::ForkException("task end with the code: " + code);
        } else {
            throw infra::sys::ForkException("The children's process ends abnormally.");
        }
    }
}

infra::sys::Result infra::sys::execute_pipe(const std::string& command) {
    infra::sys::Result res;
    std::array<char, 256> buffer;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw infra::sys::PipeException("failed to open pipe for command: " + command);
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        res.output += buffer.data();
    }

    int status = pclose(pipe);
    if (status == -1) {
        throw infra::sys::PipeException("failed to close pipe for command: " + command);
    } else if (WIFEXITED(status)) {
        res.error_code = WEXITSTATUS(status);
        if (res.error_code != 0) {
            throw infra::sys::PipeException(
                "command exited with non-zero code: " + std::to_string(res.error_code));
        }
    } else if (WIFSIGNALED(status)) {
        throw infra::sys::PipeException(
            "command terminated by signal: " + std::to_string(WTERMSIG(status)));
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
