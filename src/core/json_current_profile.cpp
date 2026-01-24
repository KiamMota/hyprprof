#include "core/json_current_profile.hpp"
#include "core/current_profile.hpp"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

core::JsonCurrentProfile::JsonCurrentProfile(const std::string& json_src) {

}

core::JsonCurrentProfile::JsonCurrentProfile() {}

const std::string core::JsonCurrentProfile::make_json(const std::string& profile, const std::string& path) {
    rapidjson::Document doc;
    doc.SetObject();
    auto& alloc = doc.GetAllocator();

    doc.AddMember(
        "current_profile",
        rapidjson::Value(profile.c_str(), alloc), // <-- precisa do .c_str() + allocator
        alloc
    );

    doc.AddMember(
        "current_path",
        rapidjson::Value(path.c_str(), alloc), // <-- idem
        alloc
    );

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
  CurrentProfile prof{};
  prof.set_profile_name(_profile_name);
  prof.set_current_path(_current_path);
  return prof; 
}
