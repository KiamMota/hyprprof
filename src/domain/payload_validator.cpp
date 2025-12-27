#include "domain/payload_validator.hpp"
#include "infra/fs/dir.hpp"

domain::PayloadValidator::PayloadValidator()
{

}

bool domain::PayloadValidator::_IsEmpty() const
{
  if(fs::dir::is_emp(_current_path)) return true;
  return {};
}

bool domain::PayloadValidator::_HyprlandSubdirIsEmpty() const
{
  if(fs::dir::is_emp(_hyprland_subdir)) return true;
  return {};
}

bool domain::PayloadValidator::_BarSubdirIsEmpty() const
{
  if(fs::dir::is_emp(_bar_subdir)) return true;
  return {};
}

bool domain::PayloadValidator::_BgIsEmpty() const
{
  if(fs::dir::is_emp(_hyprland_bg_subdir)) return true;
  return {};
}

domain::PayloadValidatorError domain::PayloadValidator::Validate(const std::string& curr_path) 
{
  _current_path = curr_path + "/payload";
  _hyprland_bg_subdir = (curr_path + "payload/hyprland/bg");
  _hyprland_subdir = (curr_path + "/payload/hyprland");
  _bar_subdir = (curr_path + "payload/bar");
  
  if(_IsEmpty()) return PayloadValidatorError::PayloadIsEmpty;
  if(!fs::dir::exists(_hyprland_subdir)) return PayloadValidatorError::HyprlandNoExists;
  if(_HyprlandSubdirIsEmpty()) return PayloadValidatorError::HyprlandEmpty;
  if(_BarSubdirIsEmpty()) return PayloadValidatorError::BarEmpty;
  if(_BgIsEmpty()) return PayloadValidatorError::HyprlandBgEmpty; 
  return PayloadValidatorError::NoError;
}
