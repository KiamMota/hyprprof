#include "core/current_profile.hpp"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "core/json/json_profile_list_writer.hpp"

core::json::JSONProfileListWriter::JSONProfileListWriter(const std::string& json_src) {
  _existing_json = json_src;
}

core::json::JSONProfileListWriter::JSONProfileListWriter() {}

const std::string core::json::JSONProfileListWriter::make_json(
    const std::string& profile, 
    const std::string& path
) {
    rapidjson::Document doc;
    if (!_existing_json.empty()) {
        doc.Parse(_existing_json.c_str());
        if (doc.HasParseError() || !doc.IsObject()) {
            doc.SetObject(); // fallback
        }
    } else {
        doc.SetObject();
    }
    auto& alloc = doc.GetAllocator();

    // verifica se já existe um current
    if (doc.HasMember("current")) {
        const auto& old_current = doc["current"];
        if (old_current.HasMember("name") && old_current.HasMember("path")) {
            std::string old_name = old_current["name"].GetString();
            std::string old_path = old_current["path"].GetString();

            if (old_name != profile) {
                // adiciona histórico do perfil antigo
                doc.RemoveMember(old_name.c_str()); // remove se já existia
                doc.AddMember(
                    rapidjson::Value(old_name.c_str(), alloc),
                    rapidjson::Value(old_path.c_str(), alloc),
                    alloc
                );
            }
        }
    }

    // atualiza current
    rapidjson::Value current_obj(rapidjson::kObjectType);
    current_obj.AddMember("name", rapidjson::Value(profile.c_str(), alloc), alloc);
    current_obj.AddMember("path", rapidjson::Value(path.c_str(), alloc), alloc);
    doc.RemoveMember("current");
    doc.AddMember("current", current_obj, alloc);

    // serializa
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    writer.SetIndent(' ', 2);
    doc.Accept(writer);

    std::string json_str = buffer.GetString();
    json_str += "\n";
    return json_str;
}




std::string core::json::JSONProfileListWriter::current_path() { return _current_path; }
std::string core::json::JSONProfileListWriter::current_profile() { return _profile_name; }

core::CurrentProfile core::json::JSONProfileListWriter::get_current()
{
  CurrentProfile prof{};
  prof.set_profile_name(_profile_name);
  prof.set_current_path(_current_path);
  return prof; 
}
