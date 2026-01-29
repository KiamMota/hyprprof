#include "infra/os/cmd.hpp"
#include "infra/os/exception.hpp"

#include <string>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <array>

void infra::os::execute_fork(const std::string& command) {
    pid_t pid = fork();

    if(command.empty())
      throw infra::os::ForkException("command is empty!"); 
    if (pid < 0) {
        throw infra::os::ForkException("failed to create process.");
        return;
    }

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", command.c_str(), nullptr);
        throw infra::os::ForkException("failed to execute command.");

        _exit(127);
    } else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            throw infra::os::ForkException("failed to wait child process.");
            return;
        }

        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            if (code != 0)
                throw infra::os::ForkException("task end with the code: " + code);
        } else {
            throw infra::os::ForkException("The children's process ends abnormally.");
        }
    }
}

infra::os::Result infra::os::execute_pipe(const std::string& command) {
    infra::os::Result res;
    std::array<char, 256> buffer;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw infra::os::PipeException("failed to open pipe for command: " + command);
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        res.output += buffer.data();
    }

    int status = pclose(pipe);
    if (status == -1) {
        throw infra::os::PipeException("failed to close pipe for command: " + command);
    } else if (WIFEXITED(status)) {
        res.error_code = WEXITSTATUS(status);
        if (res.error_code != 0) {
            throw infra::os::PipeException(
                "command exited with non-zero code: " + std::to_string(res.error_code));
        }
    } else if (WIFSIGNALED(status)) {
        throw infra::os::PipeException(
            "command terminated by signal: " + std::to_string(WTERMSIG(status)));
    }

    // trim newline final se houver
    if (!res.output.empty() && res.output.back() == '\n') {
        res.output.pop_back();
    }

    return res;
}


infra::os::Result infra::os::execute_script(const std::string& script_path) {
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
