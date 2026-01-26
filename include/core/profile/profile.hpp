#ifndef PROFILE_HPP
#define PROFILE_HPP

#include <list>
#include <string>
namespace core
{
namespace profile
{

  class Profile
  {
    private:
      std::string _name;
      std::string _version;
      std::list<std::string> _authors;
      std::string _description;
    public:
      Profile() = default;
      void set_name(const std::string& name);
      void set_version(const std::string& version);
      void set_authors(const std::list<std::string>& authors);
      void set_description(const std::string& description);
      const std::string& name() const noexcept;
      const std::string& version() const noexcept;
      const std::list<std::string>& authors() const noexcept;
      const std::string& description() const noexcept;
      

  };

}
}
#endif // PROFILE_HPP
