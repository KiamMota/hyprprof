#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <string>
namespace infra {

namespace hypr_log {
template <typename... Args> void log(const std::string& s, Args&&... args) {
    std::cout << "hyprprof: ";
    std::cout << s;
    (std::cout << ... << args);
    std::cout << "\n";
}
template <typename... Args> void err(const std::string& s, Args&&... args) {
    std::cout << "hyprprof err: ";
    std::cout << s;
    (std::cout << ... << args);
    std::cout << "\n";
}
template <typename... Args> void warn(const std::string& s, Args&&... args) {
    std::cout << "hyprprof warn: ";
    std::cout << s;
    (std::cout << ... << args);
    std::cout << "\n";
}

} // namespace hypr_log

} // namespace infra

#endif
