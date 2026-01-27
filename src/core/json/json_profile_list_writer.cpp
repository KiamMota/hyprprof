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

    // guarda antigo current no histórico
    if (doc.HasMember("current")) {
        const auto& old_current = doc["current"];
        if (old_current.HasMember("name") && old_current.HasMember("path")) {
            std::string old_name = old_current["name"].GetString();
            std::string old_path = old_current["path"].GetString();
            if (old_name != profile) {
                doc.RemoveMember(old_name.c_str());
                doc.AddMember(
                    rapidjson::Value(old_name.c_str(), alloc),
                    rapidjson::Value(old_path.c_str(), alloc),
                    alloc
                );
            }
        }
    }

    // cria current mas não adiciona ainda
    rapidjson::Document current_doc;
    current_doc.SetObject();
    auto& current_alloc = current_doc.GetAllocator();
    rapidjson::Value current_obj(rapidjson::kObjectType);
    current_obj.AddMember("name", rapidjson::Value(profile.c_str(), current_alloc), current_alloc);
    current_obj.AddMember("path", rapidjson::Value(path.c_str(), current_alloc), current_alloc);

    // serializa o doc original (sem current)
    doc.RemoveMember("current");
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    writer.SetIndent(' ', 2);
    doc.Accept(writer);
    std::string original_json = buffer.GetString();

    // serializa current sozinho
    rapidjson::StringBuffer current_buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> current_writer(current_buffer);
    current_writer.SetIndent(' ', 2);
    current_obj.Accept(current_writer);
    std::string current_str = std::string("\"current\": ") + current_buffer.GetString();


    // encontra primeiro { do original_json
    auto pos = original_json.find('{');
    if (pos == std::string::npos) pos = 0;

    // monta novo json injetando current logo depois do primeiro {
    std::string final_json = original_json.substr(0, pos + 1) + "\n  " + current_str;
    // adiciona o resto (tirando o { inicial)
    final_json += "," + original_json.substr(pos + 1);
    final_json += "\n";
    return final_json;
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
