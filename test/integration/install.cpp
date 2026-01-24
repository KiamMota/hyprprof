#include "appservice/install.hpp"
#include "infra/fs/file.hpp"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void make_profile() { 
    std::filesystem::path build_dir = fs::path("build");
    fs::path profile_dir = build_dir / "profile";

    if(fs::exists(build_dir)) return;

    std::error_code ec;
    fs::create_directories(profile_dir, ec);
    infra::fs::file::create("hyprprof.json");
    if (ec)
        throw std::runtime_error("failed to create profile directory");
    
    std::cout << "created profile" << std::endl;
  
}
int main(int argc, char** argv) 
{ 
  make_profile();
  app_service::Install inst{"profi"}; 
}
