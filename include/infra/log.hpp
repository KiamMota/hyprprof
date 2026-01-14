#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <string>
#include <filesystem>
namespace infra {

namespace hypr_log {
template <typename... Args>
void log(const std::string& s, Args&&... args) {
    std::cout << "\033[47;30m" << "hyprprof:" << "\033[0m" << " "; 
    std::cout << s;
    (std::cout << ... << args);
    std::cout << "\n";
}

template <typename... Args>
void err(const std::string& s, Args&&... args) {
    std::cout << "\033[41;30m" << "hyprprof err:" << "\033[0m" << " "; // fundo vermelho, texto preto
    std::cout << s;
    (std::cout << ... << args);
    std::cout << "\n";
}

template <typename... Args>
void warn(const std::string& s, Args&&... args) {
    std::cout << "\033[103;30m" << "hyprprof warn:" << "\033[0m" << " "; // fundo amarelo claro, texto preto
    std::cout << s;
    (std::cout << ... << args);
    std::cout << "\n";
}
inline void file_not_exists(const std::string& file_path)
{
    std::filesystem::path p(file_path);
    std::string file_name = p.filename().string(); // pega só o nome do arquivo
    hypr_log::err("file named '" + file_name + "' doesn't exists");
}


} // namespace hypr_log

} // namespace infra

#endif
