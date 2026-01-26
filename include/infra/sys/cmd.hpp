#ifndef CMD_HPP
#define CMD_HPP

#include <stdexcept>
#include <string>
namespace infra {
namespace sys {


typedef struct {
    std::string output;
    int error_code;
} Result;

/**
 * @brief Executes a command using a POSIX shell through a pipe.
 *
 * @param command Command string executed exactly as provided.
 *
 * @return Result where:
 *  - output contains the full stdout of the command
 *  - error_code is the process exit code
 *
 * @note Blocks the calling thread until completion.
 * @note stderr is not captured.
 * @warning No escaping or sanitization is performed.
 */
Result execute_pipe(const std::string& command);

/**
 * @brief Executes a command by forking a new process.
 *
 * @param command Command string to execute.
 *
 * @note Does not block the caller.
 * @note Does not return execution status.
 * @warning Creates a new OS process.
 */
void execute_fork(const std::string& command);

/**
 * @brief Executes a script at the given path.
 *
 * @param script_path Path to the script (relative or absolute).
 *
 * @return Result containing stdout and exit code.
 *
 * @throws std::runtime_error If the script cannot be executed.
 * @note Requires execute permission and respects the script shebang.
 */
Result execute_script(const std::string& script_path);

} // namespace sys
} // namespace infra

#endif // CMD_HPP
