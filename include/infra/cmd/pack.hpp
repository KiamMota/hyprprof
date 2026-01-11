#ifndef PACK
#define PACK
#include "domain/environment.hpp"
#include "infra/cmd/cmd.hpp"
#include <list>
#include <string>
namespace infra {
namespace cmd {
namespace pack {

void install_package_y(domain::Environment& env, const std::string& pack_name);
void install_packages_y(domain::Environment& env, const std::list<std::string>& packages);
void remove_package(domain::Environment& env, const std::string& pack_name);
infra::cmd::Result install_package_in_background(domain::Environment& env, const std::string& pack_name);
} // namespace pack
} // namespace cmd

} // namespace infra
#endif
