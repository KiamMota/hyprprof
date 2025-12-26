#ifndef JSON_MESSAGE_HPP
#define JSON_MESSAGE_HPP

#include <iostream>
#include <string>
namespace json {
namespace log {
template <typename... Args> void log(const std::string& s, Args&&... rest) {
    std::cerr << "JSON LOG: ";
    std::cerr << s;
    (std::cerr << ... << rest);
    std::cerr << '\n';
}
template <typename... Args> void err(const std::string& s, Args&&... rest) {
    std::cerr << "\x1b[1;30;41mJSON ERR:\x1b[0m " << s;
    (std::cerr << ... << rest);
    std::cerr << '\n';
}

void object_not_found(const std::string& object);
void member_not_found(const std::string& object, const std::string& member_name);
void member_not_found(const std::string& member_name);
} // namespace log

} // namespace json
#endif
