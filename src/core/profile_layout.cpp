#include "core/profile_layout.hpp"
#include "infra/fs/dir.hpp"
#include "infra/fs/file.hpp"
#include <stdexcept>

core::ProfileLayout::ProfileLayout(const std::string& source_dir)
{
  _source_path = infra::fs::dir::get_absolute(source_dir);
  _manifest_path = _source_path + "/hyprprof.json";
  _payload_path = _source_path + "/payload";

  if(!infra::fs::file::exists(_manifest_path))
    throw std::runtime_error("'hyprprof.json' doesn't exist!");
  if(!infra::fs::dir::exists(_payload_path))
    throw std::runtime_error("'payload/' dir doesn't exist!");
}

const std::string& core::ProfileLayout::manifest_path() const noexcept
{
  return _manifest_path;
}

const std::string& core::ProfileLayout::payload_path() const noexcept
{
  return _payload_path;
}
