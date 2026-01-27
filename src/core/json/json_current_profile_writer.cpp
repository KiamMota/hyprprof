#include "core/json/json_current_profile_writer.hpp"
#include "core/current_profile.hpp"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

core::json::JSONCurrentProfileWriter::JSONCurrentProfileWriter(const std::string& json_src) {

}

core::json::JSONCurrentProfileWriter::JSONCurrentProfileWriter() {}

const std::string core::json::JSONCurrentProfileWriter::make_json(const std::string& profile, const std::string& path) {
    rapidjson::Document doc;
    doc.SetObject();
    auto& alloc = doc.GetAllocator();

    // Cria o objeto "current"
    rapidjson::Value current_obj(rapidjson::kObjectType);
    current_obj.AddMember("name", rapidjson::Value(profile.c_str(), alloc), alloc);
    current_obj.AddMember("path", rapidjson::Value(path.c_str(), alloc), alloc);

    // Adiciona "current" ao documento
    doc.AddMember("current", current_obj, alloc);

    // Serializa
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    writer.SetIndent(' ', 2);
    doc.Accept(writer);

    std::string json_str = buffer.GetString();
    json_str += "\n";
    return json_str;
}



std::string core::json::JSONCurrentProfileWriter::current_path() { return _current_path; }
std::string core::json::JSONCurrentProfileWriter::current_profile() { return _profile_name; }

core::CurrentProfile core::json::JSONCurrentProfileWriter::get_current()
{
  CurrentProfile prof{};
  prof.set_profile_name(_profile_name);
  prof.set_current_path(_current_path);
  return prof; 
}
