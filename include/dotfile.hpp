#ifndef DOTCONFIG_HPP
#define DOTCONFIG_HPP

#include <string>
namespace core
{
  class DotFile
  {
    private: 
      std::string _name;
      std::string _pack;
      std::string _target_path;
      std::string _source_path;
    public:
      DotFile() = default;
      DotFile& set_name(const std::string& name);
      DotFile& set_pack(const std::string& pack);
      DotFile& set_target_path(const std::string& path);
      DotFile& set_source_path(const std::string& path);
      const std::string& name() const noexcept;
      const std::string& pack() const noexcept;
      const std::string& target() const noexcept;
      const std::string& source() const noexcept;
    
  };
}

#endif // DOTCONFIG_HPP
