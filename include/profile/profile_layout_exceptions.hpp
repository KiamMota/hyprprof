#ifndef PROFILE_LAYOUT_EXCEPTIONS_HPP
#define PROFILE_LAYOUT_EXCEPTIONS_HPP

#include <exception>
#include <string>
namespace profile {
class ProfileLayoutDirException : std::exception {
    std::string msg;

  public:
    ProfileLayoutDirException(const char* dir) : std::exception() 
    {
      msg = "the path '" + std::string(dir) + "' is required but not exists!";
    }
    const char* what() const noexcept override
    {
      return msg.c_str();
    }
};

class ProfileLayoutFileException : std::exception
{
std::string msg;

public:
  ProfileLayoutFileException(const char* file) : std::exception()
  {
    msg = "the file '" + std::string(file) + "' is required but not exists!";
  }

  const char* what() const noexcept override
  {
    return msg.c_str();
  }
};
}
#endif // PROFILE_LAYOUT_EXCEPTIONS_HPP
