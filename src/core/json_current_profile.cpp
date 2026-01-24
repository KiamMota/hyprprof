#include "core/json_current_profile.hpp"
#include "core/current_profile.hpp"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

core::JsonCurrentProfile::JsonCurrentProfile(const std::string& profile_name,
                                             const std::string& prof_path) {
    _profile_name = profile_name;
    _current_path = prof_path;
}

const std::string core::JsonCurrentProfile::get_json() {
    rapidjson::Document doc;
    doc.SetObject();
    auto& alloc = doc.GetAllocator();

    doc.AddMember("current_profile", rapidjson::Value(_profile_name.c_str(), alloc), alloc);

    doc.AddMember("current_path", rapidjson::Value(_current_path.c_str(), alloc), alloc);

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    writer.SetIndent(' ', 2);
    doc.Accept(writer);
    std::string json_str = buffer.GetString();
    json_str += "\n";
    return json_str;
}

std::string core::JsonCurrentProfile::current_path() { return _current_path; }
std::string core::JsonCurrentProfile::current_profile() { return _profile_name; }

core::CurrentProfile core::JsonCurrentProfile::get_current()
{
  CurrentProfile prof{_profile_name, _current_path};
  return prof; 
}
