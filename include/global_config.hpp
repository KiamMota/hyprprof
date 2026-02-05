#ifndef JSON_CONFIG_FILE_READER_HPP
#define JSON_CONFIG_FILE_READER_HPP

#include <string>

namespace core {

class GlobalConfig {
private:
  GlobalConfig();
  public:
    static const std::string get_config_content();
    static const std::string get_username();
    static const std::string get_current_profile_name();
};
} // namespace core

#endif // JSON_CONFIG_FILE_READER_HPP
