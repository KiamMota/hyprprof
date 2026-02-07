// ┌──────────────┐                                                                                             
// │ HyprprofPath │                                                                                             
// └┬─────────────┘                                                                                             
//  │                                                                                                           
//  │ This is a static object that represents                                                                   
//  │ the system's ~/.config/hyprprof directory.                                                                
//  │                                                                                                           
//  │    Methods:                                                                                               
//  ├───────► create_required_paths()         Create the required directories: hyprprof/, .backup/, and .config/
//  ├───────► root_path()                     returns the root hyprprof path.                                   
//  ├───────► backup_path()                   returns the backup path in hyprprof path.                         
//  ├───────► config_path()                   returns the config file                                           
//  ├───────► path_exists_in_hyprprof_path()  returns true if path exists                                       
//  ├───────► concat_str_path(string)         returns string of path in hyprprof path                           
//  ├───────► create_path_in_hyprprof_path(string, bool) create a path in hyprprofpath, if exists, doesnt overwrite, wait the bool result.                               
//  └───────► profile_paths()                 returns a list of profiles within the hyprprof path.              


#ifndef HYPRPROF_PATH_HPP
#define HYPRPROF_PATH_HPP

#include <list>
#include <string>
namespace core
{
    /**
     * @brief Static utility class for managing Hyprprof paths.
     * 
     * This class provides helper methods to create, verify, and manipulate
     * paths within the Hyprprof configuration directory.
     */
    /*STATIC*/ class HyprprofPath
    {
    private:
        /**
         * @brief Private constructor to prevent instantiation.
         */
        HyprprofPath();

    public:
        /**
         * @brief Creates all required directories inside the Hyprprof path.
         * 
         * This should be called during initialization to ensure that
         * all necessary subdirectories exist.
         */
        static void create_required_paths();

        /**
         * @brief Returns the base path of the Hyprprof directory.
         * 
         * @return std::string The absolute path to the Hyprprof directory.
         */
        static const std::string root_path() noexcept;

        /**
         * @brief Returns the configuration path inside Hyprprof.
         * 
         * Typically used to store configuration files and JSON manifests.
         * 
         * @return std::string The absolute path to the config directory.
         */
        static const std::string config_path() noexcept;

        /**
         * @brief Returns the backup path inside Hyprprof.
         * 
         * Used to store backups of system configurations or dotfiles
         * before applying a profile.
         * 
         * @return std::string The absolute path to the backup directory.
         */
        static const std::string backup_path() noexcept;

        /**
         * @brief Checks if a given path exists inside the Hyprprof directory.
         * 
         * @param path The relative or absolute path to check.
         * @return true If the path exists.
         * @return false Otherwise.
         */
        static bool path_exists_in_hyprprof_path(const std::string& path) noexcept;

        /**
         * @brief Concatenates a string with the Hyprprof base path.
         * 
         * Useful for building absolute paths inside Hyprprof.
         * 
         * @param path The relative path to append.
         * @return std::string The resulting absolute path.
         */
        static const std::string concat_str_path(const std::string& path) noexcept;

        /**
         * @brief Creates a directory with the given name inside Hyprprof.
         * 
         * If the directory already exists, it can optionally be overwritten.
         * 
         * @param name The name of the directory to create.
         * @param overwrite Whether to overwrite if the directory exists.
         */
        static void create_path_in_hyprprof_path(const std::string& name, bool overwrite);

        static std::list<std::string> profile_paths() noexcept;
    };
}


#endif // HYPRPROF_HPP
