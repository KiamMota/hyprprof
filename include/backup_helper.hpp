#ifndef BACKUP_HELPER_HPP
#define BACKUP_HELPER_HPP

#include <string>
namespace core
{
  class BackupHelper
  {
    private:
      BackupHelper();
      static void meta_json_insert(const std::string& content);
      static void write_in_metajson(const std::string& path_name, const std::string& original_src);
    public:
      static const std::string meta_json_path() noexcept;
      static const std::string meta_json_content();
      static void create_backup_path_and_register_in_meta_json(const std::string& src_path);
  };


}

#endif // BACKUP_HELPER_HPP
