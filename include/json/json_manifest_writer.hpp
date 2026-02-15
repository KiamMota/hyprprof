#ifndef JSON_MANIFEST_WRITER_HPP
#define JSON_MANIFEST_WRITER_HPP

#include "rapidjson/document.h"
#include <list>
#include <string>
namespace json {
class JSONManifestWriter {
  private:
    std::string _json_str;
    rapidjson::Document doc;
    rapidjson::Value hyprprof_obj;
    rapidjson::Value version_constraints;

  public:
    JSONManifestWriter();
    JSONManifestWriter& set_name(const std::string& name);
    JSONManifestWriter& set_version(const std::string& version);
    JSONManifestWriter& set_description(const std::string& desc);
    JSONManifestWriter& set_authors(std::list<std::string> authors);
    JSONManifestWriter& set_version_constraints(const std::string& wayland,
                                                const std::string& hyprland);
    const std::string& to_string() const;
};
} // namespace json

#endif // JSON_MANIFEST_WRITER_HPP
