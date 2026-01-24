#include "core/profile/profile.hpp"
#include "core/profile/exceptions.hpp"
#include <regex>

core::profile::Profile::Profile() {}

void core::profile::Profile::set_authors(const std::list<std::string>& authors) {
    if (authors.empty())
        throw profile::ProfileFieldException("The author field is empty!");
    for (auto& author : authors) {
        _authors.push_back(author);
    }
}

void core::profile::Profile::set_description(const std::string& desc) 
{
  _description = desc;
}

void core::profile::Profile::set_name(const std::string& name) 
{
  if(name.empty())
    throw profile::EmptyFieldException("name");
  std::regex pat("R(^[A-Za-z]+$)");
  if(!std::regex_match(name, pat))
  {
    throw profile::ProfileFieldException("The profile name has an invalid pattern.");
  }
  _name = name;
}

void core::profile::Profile::set_version(const std::string& version) 
{
  if(version.empty()) throw profile::EmptyFieldException("version");
  
  std::regex pat(R"(^\d+\.\d+\.\d+(\d*)$)");
  if(!std::regex_match(version, pat))
    throw profile::VersionFieldException("The version field is not in the correct format.");
  _version = version;
}


