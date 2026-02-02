#ifndef PROFILE_STRUCT_HPP
#define PROFILE_STRUCT_HPP

#include <list>
#include <string>

namespace profile {
class ProfileLayout {
private:
    std::string _source_path;
    std::string _readme_path;
    std::string _manifest_path;
    std::string _config_path;
    std::string _hypr_path;
    std::string _waybar_path;
    std::string _dotfiles_path;
    std::string _assets_path;
    std::string _assets_bg_path;
    std::string _assets_fonts_path;

    void set_paths();
    void check_paths();

public:
    ProfileLayout();
    void set_path(const std::string& source);
    void move_profile_to(const std::string& new_source);

    bool has_dotfiles_path() const noexcept;
    bool has_hypr_path() const noexcept;
    bool has_waybar_path() const noexcept; 
    bool has_readme_path() const noexcept;
    bool has_assets_path() const noexcept;
    bool has_assets_bg_path() const noexcept;
    bool has_assets_fonts_path() const noexcept;

    const std::string& source_path() const noexcept;
    const std::string& manifest_path() const noexcept;
    const std::string& config_path() const noexcept;
    const std::string& readme_path() const noexcept;
    const std::string& waybar_path() const noexcept;
    const std::string& hypr_path() const noexcept;
    const std::string& dotfiles_path() const noexcept;

    const std::string& assets_path() const noexcept;
    const std::string& assets_bg_path() const noexcept;
    const std::string& assets_fonts_path() const noexcept;

};


} // namespace profile
#endif // PROFILE_STRUCT_HPP
