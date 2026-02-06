#ifndef PROFILE_STRUCT_HPP
#define PROFILE_STRUCT_HPP

#include <string>

namespace profile {
/*STATIC*/ class ProfileLayout {
  private:
    ProfileLayout();
  public:

    static void check_required_paths(const std::string& path);

    static bool has_dotfiles_path(const std::string& path) noexcept;
    static bool has_hypr_path(const std::string& path) noexcept;
    static bool has_waybar_path(const std::string& path) noexcept;
    static bool has_readme_path(const std::string& path) noexcept;
    static bool has_assets_path(const std::string& path) noexcept;
    static bool has_assets_bg_path(const std::string& path) noexcept;
    static bool has_assets_fonts_path(const std::string& path) noexcept;

    static const std::string manifest_path(const std::string& path) noexcept;
    static const std::string manifest_content(const std::string& path);
    static const std::string config_path(const std::string& path) noexcept;
    static const std::string readme_path(const std::string& path) noexcept;
    static const std::string waybar_path(const std::string& path) noexcept;
    static const std::string hypr_path(const std::string& path) noexcept;
    static const std::string dotfiles_path(const std::string& path) noexcept;

    static const std::string assets_path(const std::string& path) noexcept;
    static const std::string assets_bg_path(const std::string& path) noexcept;
    static const std::string assets_fonts_path(const std::string& path) noexcept;
};

} // namespace profile
#endif // PROFILE_STRUCT_HPP
