#include "infra/cmd.hpp"
#include "domain/environment.hpp"
#include <iostream>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <array>

void infra::cmd::execute_fork(const std::string& command) {
    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "Falha ao criar processo\n";
        return;
    }

    if (pid == 0) {
        // Filho: herda stdout/stderr do pai, imprime direto no terminal
        execl("/bin/sh", "sh", "-c", command.c_str(), nullptr);

        // se execl falhar
        std::cerr << "Falha ao executar comando\n";
        _exit(127);
    } else {
        // Pai: espera o filho terminar
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            std::cerr << "Falha ao esperar pelo processo filho\n";
            return;
        }

        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            if (code != 0)
                std::cerr << "Comando terminou com código de saída: " << code << "\n";
        } else {
            std::cerr << "Processo filho terminou de forma anormal\n";
        }
    }
}

infra::cmd::Result infra::cmd::execute_pipe(const std::string& command) {
    Result res;
    std::array<char, 256> buffer;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        res.error_code = -1; // falha ao abrir pipe
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

infra::cmd::Result infra::cmd::execute_script(const std::string& script_path) {
    Result res;

    if (script_path.empty()) {
        res.error_code = -1;
        res.output = "";
        return res;
    }

    struct stat st;
    if (stat(script_path.c_str(), &st) != 0) {
        res.error_code = -1; // arquivo não existe
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

void infra::cmd::install_package_y(const std::string& pack_name) {
    domain::Environment env{};
    std::string line_string;
    line_string = "sudo " + env.install_command() + " " + pack_name + " -y";
    execute_fork(line_string);
}

infra::cmd::Result infra::cmd::install_package_in_background(const std::string &pack_name)
{
  domain::Environment env{};
  std::string line_string;
  line_string = "sudo " + env.install_command() + " " + pack_name + " -y" ;
  std::cout << "installing dependencies in background..." << std::endl;
  return execute_pipe(line_string);
}
