#ifndef PROFILE_STRUCT_HPP
#define PROFILE_STRUCT_HPP

#include <string>

namespace profile {

/**
 * @brief Static utility class for managing the layout of a Hyprprof profile.
 * 
 * This class provides helper methods to check for required paths, construct
 * paths to profile components, and access files within a profile directory.
 * All methods are static and the class cannot be instantiated.
 */
class ProfileLayout
{
private:
    /**
     * @brief Private constructor to prevent instantiation.
     */
    ProfileLayout();

public:
    /**
     * @brief Checks that all required directories and files exist in the profile path.
     * 
     * This can be used to validate a profile before applying it.
     * 
     * @param path The base path of the profile.
     */
    static void check_required_paths(const std::string& path);

    /** @name Existence Checks */
    ///@{
    static bool has_dotfiles_path(const std::string& path) noexcept;     /**< Checks if the profile has a dotfiles directory. */
    static bool has_hypr_path(const std::string& path) noexcept;         /**< Checks if the profile contains a Hypr configuration path. */
    static bool has_waybar_path(const std::string& path) noexcept;       /**< Checks if the profile contains a Waybar configuration path. */
    static bool has_readme_path(const std::string& path) noexcept;       /**< Checks if the profile contains a README file. */
    static bool has_assets_path(const std::string& path) noexcept;       /**< Checks if the profile has an assets directory. */
    static bool has_assets_bg_path(const std::string& path) noexcept;    /**< Checks if the profile has a background assets directory. */
    static bool has_assets_fonts_path(const std::string& path) noexcept; /**< Checks if the profile has a fonts assets directory. */
    ///@}

    /** @name Manifest Access */
    ///@{
    static const std::string manifest_path(const std::string& path) noexcept;   /**< Returns the full path to the hyprprof.json manifest file. */
    static const std::string manifest_content(const std::string& path);         /**< Returns the contents of the manifest file as a string. */
    ///@}

    /** @name Dotfile Utilities */
    ///@{
    static const std::string concat_dotfile_path(const std::string& src, const std::string& name) noexcept; /**< Concatenates a dotfile name with the profile's dotfiles path. */
    static bool has_this_dotfile(const std::string& path, const std::string& name) noexcept;               /**< Checks if a specific dotfile exists inside the profile. */
    static const std::string config_path(const std::string& path) noexcept;                                /**< Returns the config directory path inside the profile. */
    static const std::string readme_path(const std::string& path) noexcept;                                /**< Returns the README file path inside the profile. */
    static const std::string waybar_path(const std::string& path) noexcept;                                /**< Returns the Waybar configuration path inside the profile. */
    static const std::string hypr_path(const std::string& path) noexcept;                                  /**< Returns the Hypr configuration path inside the profile. */
    static const std::string dotfiles_path(const std::string& path) noexcept;                              /**< Returns the dotfiles directory path inside the profile. */
    ///@}

    /** @name Assets Utilities */
    ///@{
    static const std::string assets_path(const std::string& path) noexcept;        /**< Returns the assets directory path inside the profile. */
    static const std::string assets_bg_path(const std::string& path) noexcept;     /**< Returns the background assets directory path inside the profile. */
    static const std::string assets_fonts_path(const std::string& path) noexcept;  /**< Returns the fonts assets directory path inside the profile. */
    ///@}
};

} // namespace profile

#endif // PROFILE_STRUCT_HPP
