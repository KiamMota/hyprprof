#ifndef CMD_HPP
#define CMD_HPP

#include <stdexcept>
#include <string>

namespace os {

/**
 * @file cmd.hpp
 * @brief Provides functions for executing shell commands, scripts, and package management
 * operations.
 *
 * This module contains utilities for:
 *  - Running commands synchronously or asynchronously
 *  - Capturing command output and exit codes
 *  - Checking and installing system packages
 *
 * @note All functions execute OS-level commands and may throw exceptions if commands fail.
 */

/**
 * @struct Result
 * @brief Represents the result of a command execution.
 *
 * @var Result::output
 *   Captures the stdout of the executed command.
 * @var Result::error_code
 *   Contains the exit code of the executed process.
 */
typedef struct {
    std::string output; ///< Standard output of the command
    int error_code;     ///< Process exit code
} Result;

/**
 * @brief Executes a command using a POSIX shell through a pipe.
 *
 * @param command Command string executed exactly as provided.
 * @return Result containing the command's stdout and exit code.
 *
 * @note Blocks the calling thread until the command completes.
 * @note Standard error is not captured.
 * @warning The command is executed directly; no escaping or sanitization is performed.
 */
Result pipe(const std::string& command);

/**
 * @brief Executes a command by forking a new process.
 *
 * @param command Command string to execute.
 *
 * @note Non-blocking: returns immediately without waiting for the command to finish.
 * @note Does not provide stdout or exit code.
 * @warning Creates a new OS process.
 */
void fork(const std::string& command);

/**
 * @brief Executes a script at the given path.
 *
 * @param script_path Path to the script (relative or absolute).
 * @return Result containing the script's stdout and exit code.
 *
 * @throws std::runtime_error If the script cannot be executed.
 * @note Requires execute permission and respects the script's shebang.
 */
Result exec_script(const std::string& script_path);

/**
 * @brief Installs a system package using the detected package manager.
 *
 * @param pack Name of the package to install.
 *
 * @note This function uses the OS package manager (apt, pacman, dnf, etc.).
 * @warning May require root privileges.
 */
void install_pack(const std::string& pack);

/**
 * @brief Checks whether a system package is already installed.
 *
 * @param pack Name of the package to check.
 * @return true if the package is installed, false otherwise.
 */
bool pack_exists(const std::string& pack);

} // namespace os

#endif // CMD_HPP
