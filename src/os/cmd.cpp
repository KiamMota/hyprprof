#include "os/cmd.hpp"
#include "os/env.hpp"
#include "os/exception.hpp"
#include "utils/log.hpp"

#include <string>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <array>

//
// Fork-based execution: executes a shell command in a child process
//
void ::os::execute_fork(const std::string& command) {
    // Check if the command string is empty: cannot execute an empty command
    if (command.empty())
        throw ::os::ForkException("command is empty!"); 

    // Fork a new process
    pid_t pid = fork();

    // pid < 0 means fork failed, no child created
    if (pid < 0) {
        throw ::os::ForkException("failed to create process.");
        return;
    }

    // Child process branch
    if (pid == 0) {
        // Replace child process image with /bin/sh executing the command
        execl("/bin/sh", "sh", "-c", command.c_str(), nullptr);

        // If execl fails, throw an exception in the child process
        throw ::os::ForkException("failed to execute command.");

        // Ensure child exits if execl fails
        _exit(127);
    } else { // Parent process branch
        int status;

        // Wait for child process to finish
        if (waitpid(pid, &status, 0) == -1) {
            throw ::os::ForkException("failed to wait child process.");
            return;
        }

        // Check if child exited normally
        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);

            // If exit code is non-zero, report as error
            if (code != 0)
                throw ::os::ForkException("task end with the code: " + code);
        } else {
            // Child did not exit normally (terminated by signal or other abnormal reason)
            throw ::os::ForkException("The children's process ends abnormally.");
        }
    }
}

//
// Pipe-based execution: executes command and captures stdout
//
os::Result os::execute_pipe(const std::string& command) {
    os::Result res; // Struct to hold stdout and exit code
    std::array<char, 256> buffer; // Temporary buffer to read output

    // Open a pipe to the command using POSIX popen()
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw ::os::PipeException("failed to open pipe for command: " + command);
    }

    // Read all lines of output into res.output
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        res.output += buffer.data();
    }

    // Close the pipe and get the process exit code
    int status = pclose(pipe);
    if (status == -1) {
        throw ::os::PipeException("failed to close pipe for command: " + command);
    } else if (WIFEXITED(status)) {
        // Normal exit: save exit code
        res.error_code = WEXITSTATUS(status);

        // If non-zero, raise exception
        if (res.error_code != 0) {
            throw ::os::PipeException(
                "command exited with non-zero code: " + std::to_string(res.error_code));
        }
    } else if (WIFSIGNALED(status)) {
        // Terminated by signal
        throw ::os::PipeException(
            "command terminated by signal: " + std::to_string(WTERMSIG(status)));
    }

    // Trim trailing newline if present to make output cleaner
    if (!res.output.empty() && res.output.back() == '\n') {
        res.output.pop_back();
    }

    return res;
}

//
// Executes a script file by path
//
os::Result os::execute_script(const std::string& script_path) {
    Result res;

    // Empty path is invalid
    if (script_path.empty()) {
        res.error_code = -1;
        res.output = "";
        return res;
    }

    struct stat st;
    // Check if the file exists
    if (stat(script_path.c_str(), &st) != 0) {
        res.error_code = -1; // file doesn't exist
        res.output = "file not found";
        return res;
    }

    // Check if file is executable for the user
    if (!(st.st_mode & S_IXUSR)) {
        // Make it executable if necessary
        res = execute_pipe("chmod +x " + script_path);
        if (res.error_code != 0)
            return res;
    }

    // Finally execute it through a pipe
    return execute_pipe(script_path);
}

//
// Installs a system package using the detected package manager
//
void os::install_pack(const std::string &pack) {
    std::string pkg_mgr = os::detect_package_manager_str();
    std::string cmd;

    // Build installation command based on OS package manager
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

    // Execute the installation command, blocking until done
    os::execute_pipe(cmd);
}

//
// Checks if a system package is installed
//
bool os::pack_exists(const std::string &pack) {
    std::string pkg_mgr = os::detect_package_manager_str();
    std::string cmd;

    // Construct package query command for each known package manager
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

    // Execute the query and return true if exit code is zero (package found)
    return os::execute_pipe(cmd).error_code == 0;
}

