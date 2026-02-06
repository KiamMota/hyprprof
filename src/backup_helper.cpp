#include "backup_helper.hpp"
#include "fs/dir.hpp"
#include "fs/file.hpp"
#include "hyprprof_path.hpp"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <stdexcept>
#include <string>

namespace core {
const std::string BackupHelper::meta_json_path() noexcept {
    return HyprprofPath::backup_path() + "/.meta.json";
}

const std::string BackupHelper::meta_json_content() {
    if(!hprof_fs::file::exists(meta_json_path()))
      throw std::runtime_error(".meta.json no exists!");

  return hprof_fs::file::get_content(meta_json_path());

}

void BackupHelper::meta_json_insert(const std::string& content)
{
  hprof_fs::file::overwrite(meta_json_path(), content);
}

void BackupHelper::write_in_metajson(const std::string& path,
                                    const std::string& original_src)
{
    rapidjson::Document doc;
    doc.Parse(meta_json_content().c_str());

    if (!doc.IsObject())
        doc.SetObject();

    auto& allocator = doc.GetAllocator();

    rapidjson::Value key(path.c_str(), allocator);

    rapidjson::Value value(rapidjson::kObjectType);
    value.AddMember(
        rapidjson::Value("original_source", allocator),
        rapidjson::Value(original_src.c_str(), allocator),
        allocator
    );

    doc.AddMember(key, value, allocator);

    // serializa o JSON inteiro
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    // insere no meta json
    meta_json_insert(buffer.GetString());
}
void BackupHelper::create_backup_path_and_register_in_meta_json(const std::string& src_path)
{
    std::string abs = hprof_fs::dir::get_absolute(src_path);
    std::string last_path = hprof_fs::dir::get_last_dir(abs);

    std::string dest = core::HyprprofPath::backup_path() + "/" + last_path;

    if (hprof_fs::dir::exists(dest))
        return;

    hprof_fs::dir::copy(abs, dest);
    write_in_metajson(last_path, abs);
}



} // namespace core
