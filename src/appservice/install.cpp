#include "appservice/install.hpp"
#include "core/json_manifest.hpp"
#include "core/profile/profile.hpp"
#include "infra/fs/file.hpp"
#include "infra/log.hpp"
#include <stdexcept>
#include <string>
#include <unistd.h>

app_service::Install::Install(const std::string& curr_path) {
  
  std::string hyprprof_json_path = curr_path + "/hyprprof.json";

  if(!infra::fs::file::exists(hyprprof_json_path))
  {
    infra::hypr_log::err("hyprprof.json not found");
    return;
  }
  std::string json_str= infra::fs::file::get_content(hyprprof_json_path);
  
  core::JsonManifest json_val{json_str};
  try
  {
  json_val.parse();
  }catch(const std::runtime_error& e)
  { 
    infra::hypr_log::err(e.what(), " (aborted).");
    return;
  }

  core::profile::Profile prof{};
  prof = json_val.GetProfile();
  infra::hypr_log::log("end pipeline");
}
