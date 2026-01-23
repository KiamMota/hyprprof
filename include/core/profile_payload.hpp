#ifndef PROFILE_HPP
#define PROFILE_HPP

#include <string>

namespace core
{
  class profile_payload
  {
    private:
      std::string _absolutePath;
      std::string _jsonManifestPath;
      std::string _payloadPath;
      std::string _scriptsPath;
    public:
      profile_payload(const std::string& path); 

      std::string manifest_path() const;
      std::string payload_path() const;
      std::string scripts_path() const;
      std::string uinstall_path() const;
      std::string install_path() const;
  };

}

#endif // PROFILE_HPP
