#ifndef CMD
#define CMD

#include "domain/environment.hpp"
#include <string>
namespace infra {
namespace cmd {

typedef struct {
    std::string output;
    int error_code;
} Result;

Result execute_pipe(const std::string& command);
Result execute_script(const std::string& script_path);
Result install_package(domain::Environment& env, const std::string& pack_name);
} // namespace cmd

} // namespace infra

#endif
