#include "appservice/show_profile.hpp"
#include "infra/fs/dotconfig.hpp"
#include "infra/fs/file.hpp"

app_service::ShowProfile::ShowProfile()
{
  
  std::string json_current_path = infra::fs::dotconfig::app_path(".hyprprof_current.json");
  std::string json_src = infra::fs::file::get_content(json_current_path);

}
