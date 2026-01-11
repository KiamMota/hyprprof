#include "infra/cmd.hpp"
#include <sys/stat.h>
#include <unistd.h>
#include <array>

infra::cmd::Result infra::cmd::execute_pipe(const std::string &command)
{
    Result res;
    std::array<char, 256> buffer;

    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe) {
        res.error_code = -1;  // falha ao abrir pipe
        return res;
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        res.output += buffer.data();
    }

    int status = pclose(pipe);
    if (WIFEXITED(status)) {
        res.error_code = WEXITSTATUS(status);
    } else {
        res.error_code = -1;  
    }
    return res;
}

infra::cmd::Result infra::cmd::execute_script(const std::string &script_path)
{
 Result res;

    if(script_path.empty())
    {
        res.error_code = -1;
        res.output = "";
        return res;
    }

    struct stat st;
    if(stat(script_path.c_str(), &st) != 0)
    {
        res.error_code = -1; // arquivo não existe
        res.output = "file not found";
        return res;
    }

    if(!(st.st_mode & S_IXUSR)) 
    {
        res = execute_pipe("chmod +x " + script_path);
        if(res.error_code != 0) 
            return res;
    }

    return execute_pipe(script_path);
}

infra::cmd::Result infra::cmd::install_package(domain::Environment &env, const std::string &pack_name)
{
  std::string line_string;
  line_string = "sudo " + env.install_command() + pack_name;
  return execute_pipe(line_string);
}
