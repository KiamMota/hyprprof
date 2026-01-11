#ifndef PACK
#define PACK
#include "infra/cmd/cmd.hpp"
#include <list>
#include <string>
namespace infra {
namespace cmd {
namespace pack {

void install_package_y(const std::string& pack_name);
void install_packages_y(const std::list<std::string>& packages);
void remove_package(const std::string& pack_name);
infra::cmd::Result install_package_in_background(const std::string& pack_name);
} // namespace pack
} // namespace cmd

} // namespace infra
#endif
