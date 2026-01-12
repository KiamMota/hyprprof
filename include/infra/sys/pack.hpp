#ifndef PACK
#define PACK
#include "core/environment.hpp"
#include "infra/sys/cmd.hpp"
#include <list>
#include <string>
namespace infra {
namespace cmd {
namespace pack {

void install_package_y(core::Environment& env, const std::string& pack_name);
void install_packages_y(core::Environment& env, const std::list<std::string>& packages);
void remove_package(core::Environment& env, const std::string& pack_name);
infra::cmd::Result install_package_in_background(core::Environment& env, const std::string& pack_name);
} // namespace pack
} // namespace cmd

} // namespace infra
#endif
