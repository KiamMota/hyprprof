#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/error/en.h"
#include "rapidjson/include/rapidjson/error/error.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

std::string open_file(std::string path)
{
  std::ifstream json_file{};
  std::stringstream buffer ;

  json_file.open(path);
  if(!json_file.is_open())
    std::cout << "não foi possível abrir o arquivo!" << std::endl;
  
  buffer << json_file.rdbuf();
  
  json_file.close();

  return buffer.str();
}

typedef enum
{
  UNK,
  PACMAN,
  APT,
  DNF,
  ZYPPER,
  EMERGE,
  APK
} PACKAGE_MANAGER;



std::string get_package_manager_str(PACKAGE_MANAGER& pack_man)
{ 
  switch (pack_man) {

    case APT:
      return "apt";
    case PACMAN:
      return "pacman";
    case UNK:
      return "";
    case DNF:
      return "dnf";
    case APK:
      return "apk";
    case EMERGE:
      return "emerge";
    case ZYPPER:
      return "zypper";
  }

  return "";
}

std::string mount_package_manager_command(bool sudo, PACKAGE_MANAGER pm) {
    std::string cmd;

    if (sudo) cmd = "sudo ";

    switch (pm) {
        case PACMAN:
            cmd += "pacman -S "; // adiciona flag de instalação padrão
            break;
        case APT:
            cmd += "apt install -y "; // instalação não-interativa
            break;
        case DNF:
            cmd += "dnf install -y ";
            break;
        case UNK:
        default:
            return ""; // desconhecido, não tenta nada
    }

    return cmd;
}

bool have_apps_object(rapidjson::Document& d)  
{
  
  if(d.HasMember("apps") && d["apps"].IsObject())
    std::cout << "existe apps!" << std::endl;
  const rapidjson::Value& apps = d["apps"];
  
  if((!apps.HasMember("terminal")) || !apps["terminal"].IsString())
    return false;
  if((!apps.HasMember("browser")) || !apps["browser"].IsString())
    return false;

  return true;
}

enum class XDG_SESSION_TYPE 
{
  UNKNOWN,
  WAYLAND,
  TTY,
  X11
};


class Environment
{
private:
  bool _is_sudo;
  std::string _home_path;
  std::string _user_name;
  XDG_SESSION_TYPE _session_type; 
  PACKAGE_MANAGER _package_manager;

  bool _get_sudo()
  {
    uid_t euid = geteuid();
    if(euid == 0)
      return true;
    return {};
  }

  XDG_SESSION_TYPE _get_session_type()
  {
    std::string line = std::string(getenv("XDG_SESSION_TYPE")); 
    if(line == "wayland") return XDG_SESSION_TYPE::WAYLAND;
    if(line == "tty") return XDG_SESSION_TYPE::TTY;
    if(line == "X11") return XDG_SESSION_TYPE::X11;
    return {};
  }

  std::string _get_user_name()
  {
    uid_t uid = geteuid ();
    struct passwd *pw = getpwuid (uid);
    if(pw) return std::string(pw->pw_name);
    return {};
  }

  std::string _get_user_home_path()
  {
    if(const char* home = getenv("HOME"))
      return home;
    return {};
  }

  PACKAGE_MANAGER _get_package_manager() {
    std::ifstream f("/etc/os-release");
    if (!f.is_open()) return UNK;

    std::string line;
    std::string id;
    while (std::getline(f, line)) {
        if (line.rfind("ID=", 0) == 0) { // começa com "ID="
            id = line.substr(3);
            if (!id.empty() && id.front() == '"' && id.back() == '"') {
                id = id.substr(1, id.size() - 2); // remove aspas
            }
            break;
        }
    }

    // converte para lowercase para evitar problemas
    std::transform(id.begin(), id.end(), id.begin(), ::tolower);

    if (id == "arch") return PACMAN;
    if (id == "manjaro") return PACMAN;
    if (id == "linuxmint") return APT;
    if (id == "debian") return APT;
    if (id == "ubuntu") return APT;
    if (id == "fedora") return DNF;
    if (id == "alphine") return APK;

    return UNK; 

  }

public:
  
  Environment()
  {
    _package_manager = _get_package_manager(); 
    _user_name = _get_user_name(); 
    _is_sudo = _get_sudo(); 
    _session_type = _get_session_type();
  }

  bool sudo(){ return _is_sudo; }
  std::string user_name() { return _user_name; }
  XDG_SESSION_TYPE session() { return _session_type; }
  
  std::string session_str() {
    
    switch (_session_type) {
      case XDG_SESSION_TYPE::TTY:
        return "tty";
      case XDG_SESSION_TYPE::X11:
        return "x11";
      case XDG_SESSION_TYPE::WAYLAND:
        return "wayland";
      case XDG_SESSION_TYPE::UNKNOWN:
        return {};
      default:
        return {};
    }

  }

  PACKAGE_MANAGER package_manager() { return _package_manager; }
  std::string package_manager_str()
  {
    switch (_package_manager) {
      case APK: return "apk";
      case APT: return "apt";
      case DNF: return "dnf";
      case PACMAN: return "pacman";
      case EMERGE: return "emerge";
      case ZYPPER: return "zypper";
      default: return "unknown";
    }
  }
};

std::string afterChar(const std::string& s, char c) {
    auto pos = s.find(c);
    if (pos == std::string::npos) return "";
    return s.substr(pos + 1);
}


class JsonFileParser
{
  private:
    std::string _json_file_str;
    
    std::string schema;


    rapidjson::Document d;
    rapidjson::Value environment;
    rapidjson::Value apps;
 
    bool _TryJsonParse()
    {
      rapidjson::ParseResult ok = d.Parse(_json_file_str.c_str());
        if(!ok)
          {
          std::cout << "JSON ERR PARSE: " 
          << rapidjson::GetParseError_En(ok.Code()) << "\n" 
          << "in: " << ok.Offset() << "\n" 
          << std::endl;
          return false;
          }
        return true;
    }

    bool _HaveObject(const std::string name)
    {
      if (!d.IsObject()) return false;
      if (!d.HasMember(name.c_str())) return false;
      return d[name.c_str()].IsObject();
    }
    
    rapidjson::Value& _GetObject(const std::string name) 
    { 
      return d[name.c_str()]; 
    }

    bool _ValidateSchema()
    {
      if(!d.HasMember("schema"))
      {
        std::cerr << "schema not found." << std::endl;
        return false;
      }
      if(!d["schema"].IsString())
      {
        std::cerr << "schema is not string." << std::endl;
        return false;
      }
      
    std::string realschema = afterChar(d["schema"].GetString(), '/');
    if(realschema != schema)
    {
      std::cerr << "invalid schema. " << std::endl;
      std::cout << "current schema: " << schema << std::endl;
      std::cout << "json schema: " << realschema << std::endl;
      return false;
    }
      
    return true;
    }

    bool _HaveAppsObject()
    {
      if(!_HaveObject("apps"))
      {
        std::cerr << "object apps is empty" << std::endl;
        return false;
      }
        apps = _GetObject("apps");
        return true;
    }

    bool _HaveEnironmentObject()
    {
      if(!_HaveObject("environment"))
      {
        std::cerr << "object environment is empty." << std::endl;
        return false;  
      }
      environment = _GetObject("environment");
      return true;
    }
    bool _HaveAppsTerminalObject()
    {
      if(!apps.HasMember("terminal") || !apps["terminal"].IsObject())
      {
        std::cerr << "terminal is not setted in \"apps\" object." << std::endl;
        return false;
      }

    }
    bool _HaveRequiredApps()
    {
      if(!apps.HasMember("browser"))
      {
        std::cerr << "browser is not setted in \"apps\" object." << std::endl;
        return false;
      }
      if(!apps.HasMember("file_manager"))
      {
        std::cerr << "file_manager is not setted in \"apps\" object." << std::endl;
        return false;
      }
      
      return true;
    } 

  public:
    JsonFileParser(std::string file_path) : schema("0.1")
    {
      _json_file_str = open_file(file_path);
    }

    void Parse()
    {

      if(!_TryJsonParse()) return; 
      if(!_ValidateSchema()) return;

      if(!_HaveAppsObject()) return;

      if(!_HaveRequiredApps()) return;
    }
    std::string json_str() { return _json_file_str; }
};

class HyprProf
{
  private:
    std::string _terminal;
    std::string _browser;

};

void show_environment_messages(Environment& env)
{
  std::cout << "env instanciated" << std::endl; 
  std::cout << "json file parser instanciated" << std::endl;  
  std::cout << "name: " << env.user_name() << std::endl;
  std::cout << "sudo: " << (env.sudo() == true ? "yes" : "no") << std::endl;
  std::cout << "package manager: " << env.package_manager_str() << std::endl;
  std::cout << "session: " << env.session_str() << std::endl;
}

int main()
{
  Environment env{};
  JsonFileParser json_file("hyprprof.json");
  json_file.Parse();

  show_environment_messages(env);


}
