#ifndef USE_HPP
#define USE_HPP

#include "profile/profile_layout.hpp"
#include <string>
namespace use_cases {
class Use 
{
  private:
   profile::ProfileLayout _profile; 
  public:
    Use(const std::string profile_name);



};
} // namespace use_cases

#endif // USE_HPP
