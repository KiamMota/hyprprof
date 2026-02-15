#ifndef INTERNET_INSTALL_HPP
#define INTERNET_INSTALL_HPP

#include "use_cases/install.hpp"
namespace use_cases {
class InternetInstall {
  public:
    InternetInstall();
    void install(const std::string& path);
};
} // namespace use_cases

#endif // INTERNET_INSTALL_HPP
