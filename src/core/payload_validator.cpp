#include "core/payload_validator.hpp"
#include "infra/fs/dir.hpp"

core::PayloadValidator::PayloadValidator()
{
}

bool core::PayloadValidator::_IsEmpty() const
{
  if(infra::fs::dir::exists(_current_path) && infra::fs::dir::is_emp(_current_path)) return true;
  return {};
}

bool core::PayloadValidator::_HyprlandSubdirIsEmpty() const
{
  if(infra::fs::dir::exists(_hyprland_subdir) && infra::fs::dir::is_emp(_hyprland_subdir)) return true;
  return {};
}

bool core::PayloadValidator::_BarSubdirIsEmpty() const
{
  if(infra::fs::dir::exists(_bar_subdir) && infra::fs::dir::is_emp(_bar_subdir)) return true;
  return {};
}

bool core::PayloadValidator::_BgIsEmpty() const
{
  if(infra::fs::dir::exists(_hyprland_bg_subdir) && infra::fs::dir::is_emp(_hyprland_bg_subdir)) return true;
  return {};
}

core::PayloadValidatorError core::PayloadValidator::Validate(const std::string& curr_path) 
{
  _current_path = curr_path + "/payload";
  _hyprland_bg_subdir = _current_path + "/hyprland/bg";
  _hyprland_subdir = _current_path + "/hyprland";
  _bar_subdir = _current_path + "/bar";

  if(_IsEmpty()) return PayloadValidatorError::PayloadIsEmpty;
  if(!infra::fs::dir::exists(_hyprland_subdir)) return PayloadValidatorError::HyprlandNoExists;
  if(!infra::fs::dir::exists(_hyprland_subdir)) return PayloadValidatorError::HyprlandEmpty;
  if(_HyprlandSubdirIsEmpty()) return PayloadValidatorError::HyprlandEmpty;
  if(_BarSubdirIsEmpty()) return PayloadValidatorError::BarEmpty;
  if(infra::fs::dir::exists(_hyprland_bg_subdir) && _BgIsEmpty()) return PayloadValidatorError::HyprlandBgEmpty; 
  return PayloadValidatorError::NoError;
}
