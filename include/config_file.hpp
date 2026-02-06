#ifndef JSON_CONFIG_FILE_READER_HPP
#define JSON_CONFIG_FILE_READER_HPP

#include <string>

namespace core {

/**
 * @brief Static utility class for managing the Hyprprof configuration file.
 * 
 * The ConfigFile class provides methods to read, write, and manipulate the
 * main Hyprprof configuration file, which stores user information and the
 * currently active profile.
 * 
 * This class is fully static and cannot be instantiated.
 */
class ConfigFile
{
private:
    /**
     * @brief Private constructor to prevent instantiation.
     */
    ConfigFile();

public:
    /**
     * @brief Returns the full content of the Hyprprof configuration file as a string.
     * 
     * @return std::string The JSON or raw content of the configuration file.
     */
    static const std::string get_config_content();

    /**
     * @brief Returns the username stored in the configuration file.
     * 
     * @return std::string The current username.
     */
    static const std::string get_username();

    /**
     * @brief Returns the name of the currently active profile.
     * 
     * @return std::string The current profile name, or an empty string if none is set.
     */
    static const std::string get_current_profile_name();

    /**
     * @brief Creates the configuration file with the given username and profile.
     * 
     * This is used during the first-time setup or when initializing a new
     * configuration.
     * 
     * @param username The username to store.
     * @param current_profile The profile to set as current.
     */
    static void create_file_content(const std::string& username, const std::string& current_profile);

    /**
     * @brief Overwrites the entire configuration file content.
     * 
     * Use this to replace the configuration file with a new content string.
     * 
     * @param content The new configuration content.
     */
    static void set_file_content(const std::string& content);

    /**
     * @brief Changes the username stored in the configuration file.
     * 
     * This modifies only the username field without affecting other settings.
     * 
     * @param name The new username.
     */
    static void change_username(const std::string& name);

    /**
     * @brief Changes the currently active profile stored in the configuration file.
     * 
     * This updates only the current_profile field without altering other data.
     * 
     * @param curr The new current profile name.
     */
    static void change_current_profile(const std::string& curr);
};

} // namespace core


#endif // JSON_CONFIG_FILE_READER_HPP
