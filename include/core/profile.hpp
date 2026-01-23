#ifndef PROFILE_HPP
#define PROFILE_HPP

#include "core/json_manifest.hpp"
#include <list>
#include <string>
namespace core
{
  class Profile
  {
    private:
      std::string _name;
      std::string _version;
      std::list<std::string> _authors;
      std::string _description;
      std::list<std::string> _components;
      std::list<std::string> _providers;
    public:
      Profile(const std::string& json_str);
  };

}
#endif // PROFILE_HPP
