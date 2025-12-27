#ifndef HYPRPROF_HPP
#define HYPRPROF_HPP

#include <endian.h>
#include <string>
class Hyprprof {
  private:
    std::string _prof_name;
    std::string _version_name;
    bool _have_payload;
    std::string _apps_terminal;
    std::string _apps_browser;
    std::string _apps_file_manager;
    // this line represents the hyprconf file.
    std::string _optional_hyprconf;
  public:
    Hyprprof();
    std::string prof_name();
    std::string version_name();
    bool payload();
    std::string terminal();
    std::string browser();
    std::string file_manager();
};

#endif
