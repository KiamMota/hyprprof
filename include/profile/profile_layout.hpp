#ifndef PROFILE_STRUCT_HPP
#define PROFILE_STRUCT_HPP

#include <string>

namespace profile {
class ProfileLayout {
  private:
    std::string _source_path;
    std::string _manifest_path;
    std::string _readme_path;
    std::string _config_path;
    std::string _extras_path;
    std::string _assets_path;
    std::string _scripts_path;

    void set_paths();
    void check_paths();

  public:
    ProfileLayout();
    void set_path(const std::string& source);

    bool has_assets_path() const noexcept;
    bool has_scripts_path() const noexcept;
    bool has_readme_path() const noexcept;
    bool has_extras_path() const noexcept;
    

    const std::string& source_path() const noexcept;
    const std::string& manifest_path() const noexcept;
    const std::string& config_path() const noexcept;
    const std::string& readme_path() const noexcept;
    const std::string& extras_path() const noexcept;
    const std::string& assets_path() const noexcept;
    const std::string& scripts_path() const noexcept;
};

} // namespace profile
#endif // PROFILE_STRUCT_HPP
