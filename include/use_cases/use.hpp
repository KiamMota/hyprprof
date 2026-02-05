#ifndef USE_HPP
#define USE_HPP

#include "hyprprof_path.hpp"
#include "profile_layout.hpp"
#include "json/global_config.hpp"
#include <string>
namespace use_cases {
class Use 
{
  private:
   profile::ProfileLayout _profile;
  json::GlobalConfig _GlobalConfig;
  core::HyprprofPath _Paths;
  bool ensure_current_profile_is_not_empty();
  void ensure_bak_path();
  void ensure_bak_manifest();
  public:
    Use(const std::string profile_name);



};
} // namespace use_cases

#endif // USE_HPP
