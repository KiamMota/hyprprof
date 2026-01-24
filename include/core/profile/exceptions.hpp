#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <csignal>
#include <cstring>
#include <exception>
#include <stdexcept>
namespace core {
namespace profile {

class ProfileFieldException : public std::exception {
    std::string msg;

  public:
    ProfileFieldException(const char* msg) : msg(msg) {}
    const char* what() const noexcept { return msg.c_str(); }
};

class EmptyFieldException : public std::exception {
    std::string field;

  public:
    EmptyFieldException(const char* field) : field(field) {}
    const char* what() const noexcept 
  { 
    std::string str = "the field named '" + field + "' is empty\n";
    const char* ret = strdup(str.c_str());
    return ret;
  }
};

class VersionFieldException : public std::exception {
    std::string msg;

  public:
    VersionFieldException(const char* msg) : msg(msg) {}
    const char* what() const noexcept { return msg.c_str(); }
};
} // namespace profile

} // namespace core

#endif // EXCEPTIONS_HPP
