#ifndef USE_HPP
#define USE_HPP

#include <string>
namespace use_cases {
class Use 
{
  private:
    std::string _profile;
    void check_first_time_using_hyprprof();
    void ensure_profile_exists_in_hyprprof_path();  

  public:

    Use(const std::string& profile_name);



};
} // namespace use_cases

#endif // USE_HPP
