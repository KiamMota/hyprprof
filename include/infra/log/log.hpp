#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <string>
namespace log
{
  template <typename... Args> void log(const std::string& s, Args&&... args)
  {
    std::cout << "hyprprof: ";
    std::cout << s;
    (std::cout << ... << args);
    std::cout << "\n";
  }
  template <typename... Args> void err(const std::string& s, Args&&... args)
  {
    std::cout << "hyprprof err: ";
    std::cout << s;
    (std::cout << ... << args);
    std::cout << "\n";
  }

  void debug(const std::string& s);
}


#endif
