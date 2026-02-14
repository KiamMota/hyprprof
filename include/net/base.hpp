#ifndef BASE_HPP
#define BASE_HPP

#include <stdexcept>
#include <string>
namespace net {

class NetException : public std::runtime_error {
  public:
    NetException(std::string message) : std::runtime_error("Net Exception: " + message) {}
};

void check_url(const std::string& url);
void check_net();
bool is_url(const std::string& str);
} // namespace net

#endif // BASE_HPP
