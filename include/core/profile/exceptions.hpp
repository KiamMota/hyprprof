#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <csignal>
#include <cstring>
#include <exception>
#include <stdexcept>
namespace core {
namespace profile {


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

class InvalidPatternException : public std::exception
{
  std::string field;
  std::string message;

public:
  InvalidPatternException(const char* fi)
    : field(fi),
      message("The regex did not match as expected for the '" + field + "' field.")
  {}

  const char* what() const noexcept override
  {
    return message.c_str();
  }
};


} // namespace profile

} // namespace core

#endif // EXCEPTIONS_HPP
