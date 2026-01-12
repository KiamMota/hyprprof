#include "core/payload_validator.hpp"
#include <cstdlib>

const char* core::PayloadErrorToString(const core::PayloadValidatorError& e) {
    switch (e) {
    case PayloadValidatorError::NoError:
        return "no error";
    case PayloadValidatorError::HyprlandNoExists:
        return "payload/hyprland no exists";
    case PayloadValidatorError::PayloadIsEmpty:
        return "payload is empty";
    case PayloadValidatorError::HyprlandBgEmpty:
        return "hyprland/bg is empty";
    case PayloadValidatorError::BarEmpty:
        return "payload/bar is empty";
    case PayloadValidatorError::HyprlandEmpty:
        return "payload/hyprland is empty";
    }
    std::abort();
}
