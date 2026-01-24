#include "appservice/install.hpp"
#include "core/json_manifest.hpp"
#include "core/profile/profile.hpp"
#include "infra/fs/file.hpp"
#include "infra/log.hpp"
#include <string>
#include <unistd.h>

app_service::Install::Install(const std::string& curr_path) {
  if(!infra::fs::file::exists(curr_path + "/hyprprof.json"))
  {
    infra::hypr_log::err("hyprprof.json not found");
    return;
  }
  std::string json_str= infra::fs::file::get_content(curr_path + "/hyprprof.json");
  core::JsonManifest json_val{json_str};
  json_val.parse();
  core::profile::Profile prof{};
  prof = json_val.GetProfile();
  infra::hypr_log::log("end pipeline");
}
