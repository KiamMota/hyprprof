#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <cstring>
#include <exception>
#include <stdexcept>
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


class FieldSizeException : public std::exception {
    std::string message;
public:
    FieldSizeException(const char* field_name, int min_size, int max_size) {
        message = "Field '" + std::string(field_name) + 
                  "' size must be between " + std::to_string(min_size) +
                  " and " + std::to_string(max_size);
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class LowerVersionException : public std::exception
{
  std::string msg;
  public:
    LowerVersionException(const char* field)
    {
      msg = "the version for the field '" + std::string(field) + "' It is less than requested.\n";  
    }
    const char* what() const noexcept override
    {
      return msg.c_str();
    }
}; // namespace profile
}


#endif // EXCEPTIONS_HPP
