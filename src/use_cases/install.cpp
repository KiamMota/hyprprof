#include "use_cases/install.hpp"
#include "infra/fs/dir.hpp"
#include "infra/fs/file.hpp"
#include <string>
#include <unistd.h>

void use_cases::Install::ensure_profile_layout(const std::string& path)
{
  _profile_lay.set_path(path);
}

void use_cases::Install::ensure_important_paths() {
    if (!_hyprprof_path_obj.path_exists())
        infra::fs::dir::create(_hyprprof_path_obj.hyprprof_path());
    if (!_hyprprof_path_obj.profile_list_exists())
        infra::fs::file::create(_hyprprof_path_obj.profile_list_path());
}

use_cases::Install::Install(const std::string& curr_path) // inicializa ProfileLayout
{
  ensure_profile_layout(curr_path); 
  ensure_important_paths();
}
