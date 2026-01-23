#include "core/install/json_manifest_validator.hpp"
#include "infra/fs/file.hpp"
#include <iostream>
#include <unistd.h>

int main() {
    try {
        std::string json_str;
        try {
        } catch(const std::error_code& ec) {
            json_str = infra::fs::file::get_content("hyprprof.json");
            std::cerr << "Filesystem error: " << ec.message() << "\n";
            return 1;
        }

        core::install::JsonManifestValidator jsonVal{};
        jsonVal.Parse(json_str);
    }
    catch(const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
        return 1;
    }
    catch(...) {
        std::cerr << "Unknown exception occurred!\n";
        return 1;
    }
}

