#include "core/profile.hpp"
#include "core/json_manifest.hpp"

core::Profile::Profile(const std::string& json)
{
  core::JsonManifest json_manifst{json};
  _authors = json_manifst.authors();
  _name = json_manifst.profile_name();
  _version = json_manifst.version();

}
