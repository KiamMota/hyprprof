#ifndef SHOW_THIS_HPP
#define SHOW_THIS_HPP

#include <list>
#include <string>
namespace use_cases
{
  class ShowThings
{
  ShowThings();
public:
  static const std::string current_profile() noexcept;
  static const std::string version() noexcept;
  static const std::list<std::string> list_profiles() noexcept;
};

}

#endif // SHOW_THIS_HPP
