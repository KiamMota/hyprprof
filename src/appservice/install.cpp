#include "appservice/install.hpp"
#include "core/json/json_manifest_reader.hpp"
#include "core/profile_layout.hpp"
#include "infra/fs/dir.hpp"
#include "infra/fs/file.hpp"
#include <string>
#include <unistd.h>

void app_service::Install::ensure_important_paths()
{
  if(!_hyprprof_path_obj.path_exists())
    infra::fs::dir::create(_hyprprof_path_obj.hyprprof_path());
  if(!_hyprprof_path_obj.profile_list_exists())
    infra::fs::file::create(_hyprprof_path_obj.profile_list_path());
}

app_service::Install::Install(const std::string& curr_path)
    : _profile_lay(curr_path)  // inicializa ProfileLayout
{
    ensure_important_paths();  // garante dirs e arquivos

    // Lê o conteúdo do hyprprof.json
    std::string json_content = infra::fs::file::get_content(_profile_lay.manifest_path());

    // Inicializa o JSON reader com o conteúdo
    _json_reader = core::json::JSONProfileListReader(json_content);
}

