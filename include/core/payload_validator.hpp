#ifndef PAYLOAD_VALIDATOR_HPP
#define PAYLOAD_VALIDATOR_HPP

#include <string>
namespace core {

enum class PayloadValidatorError
{
  NoError,
  PayloadIsEmpty,
  HyprlandNoExists,
  HyprlandEmpty,
  BarEmpty,
  HyprlandBgEmpty
};

const char* PayloadErrorToString(const core::PayloadValidatorError& e);

class PayloadValidator {
  private:
    std::string _current_path;
    std::string _hyprland_subdir;
    std::string _hyprland_bg_subdir;
    std::string _bar_subdir;
  
    bool _IsEmpty() const; 
    bool _HyprlandSubdirIsEmpty() const;
    bool _BarSubdirIsEmpty() const;
    bool _BgIsEmpty() const; 
  public:
    explicit PayloadValidator();
    core::PayloadValidatorError Validate(const std::string& _current_path);
};

} // namespace domain

#endif
