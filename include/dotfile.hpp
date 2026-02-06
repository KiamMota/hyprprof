#ifndef DOTCONFIG_HPP
#define DOTCONFIG_HPP

#include <string>
namespace core
{
    /**
     * @brief Represents a single dotfile and its associated metadata.
     * 
     * This class encapsulates information about a dotfile in a Hyprprof profile,
     * including the package it belongs to, its source location inside the profile,
     * and its target path in the system.
     * 
     * A DotFile object is used to manage installation and application of
     * configuration files (dotfiles) in a controlled and traceable manner.
     */
    class DotFile
    {
    private: 
        std::string _name;         /**< The logical name of the dotfile, e.g., "nvim" or "kitty". */
        std::string _pack;         /**< The package associated with the dotfile, e.g., "neovim". */
        std::string _target_path;  /**< The absolute path where the dotfile should be applied in the system. */
        std::string _source_path;  /**< The path to the source dotfile within the profile. */

    public:
        /**
         * @brief Default constructor.
         */
        DotFile() = default;

        /**
         * @brief Sets the logical name of the dotfile.
         * 
         * @param name The dotfile name.
         * @return DotFile& Returns a reference to self for method chaining.
         */
        DotFile& set_name(const std::string& name);

        /**
         * @brief Sets the package associated with this dotfile.
         * 
         * @param pack The package name.
         * @return DotFile& Returns a reference to self for method chaining.
         */
        DotFile& set_pack(const std::string& pack);

        /**
         * @brief Sets the target path where the dotfile should be applied.
         * 
         * @param path The absolute system path.
         * @return DotFile& Returns a reference to self for method chaining.
         */
        DotFile& set_target_path(const std::string& path);

        /**
         * @brief Sets the source path of the dotfile inside the profile.
         * 
         * @param path The source path in the profile directory.
         * @return DotFile& Returns a reference to self for method chaining.
         */
        DotFile& set_source_path(const std::string& path);

        /**
         * @brief Returns the logical name of the dotfile.
         * 
         * @return const std::string& The dotfile name.
         */
        const std::string& name() const noexcept;

        /**
         * @brief Returns the package associated with the dotfile.
         * 
         * @return const std::string& The package name.
         */
        const std::string& pack() const noexcept;

        /**
         * @brief Returns the target system path where the dotfile should be applied.
         * 
         * @return const std::string& The absolute target path.
         */
        const std::string& target() const noexcept;

        /**
         * @brief Returns the source path of the dotfile within the profile.
         * 
         * @return const std::string& The source path.
         */
        const std::string& source() const noexcept;
    };
}


#endif // DOTCONFIG_HPP
