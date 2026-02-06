#ifndef JSON_CONFIG_FILE_READER_HPP
#define JSON_CONFIG_FILE_READER_HPP

#include <string>

namespace core {

class ConfigFile {
private:
  ConfigFile();
  public:
    static const std::string get_config_content();
    static const std::string get_username();
    static const std::string get_current_profile_name();
    static void create_file_content(const std::string& username, const std::string& current_profile);
    static void set_file_content(const std::string& content);
    static void change_username(const std::string& name);
    static void change_current_profile(const std::string& curr);
};
} // namespace core

#endif // JSON_CONFIG_FILE_READER_HPP
