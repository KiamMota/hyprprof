#ifndef PROFILE_STRUCT_HPP
#define PROFILE_STRUCT_HPP

#include <string>
namespace core
{
  class ProfileLayout
  {
    private:
      std::string _manifest_path;
      std::string _payload_path;
      std::string _source_path;

    public:
      ProfileLayout(const std::string& source_path);
      const std::string& manifest_path() const noexcept;
      const std::string& payload_path() const noexcept;
      const std::string& source_path() const noexcept;
  };

}
#endif // PROFILE_STRUCT_HPP
