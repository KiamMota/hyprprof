#include "core/profile/profile.hpp"
#include "core/profile/exceptions.hpp"
#include <regex>
#include <string>


void core::profile::Profile::set_authors(const std::list<std::string>& authors) {
    if (authors.empty())
        throw profile::EmptyFieldException("The author field is empty!");
    for (auto& author : authors) {
        _authors.push_back(author);
    }
}

void core::profile::Profile::set_description(const std::string& desc) { _description = desc; }

void core::profile::Profile::set_name(const std::string& name) {
    if (name.empty())
        throw profile::EmptyFieldException("name");

    std::regex pat(R"(^[A-Za-z_]+$)");
    if (!std::regex_match(name, pat)) {
        throw profile::InvalidPatternException("name");
        return;
    }
    _name = name;
}

void core::profile::Profile::set_version(const std::string& version) {
    if (version.empty())
        throw profile::EmptyFieldException("version");

    std::regex pat(R"(^\d+\.\d+\.\d+(\d*)$)");
    if (!std::regex_match(version, pat)) {
        throw profile::InvalidPatternException("version");
        return;
    }
    _version = version;
}

const std::string& core::profile::Profile::version() const noexcept { return _version; }
const std::string& core::profile::Profile::name() const noexcept { return _name; }
const std::list<std::string>& core::profile::Profile::authors() const noexcept { return _authors; }
const std::string& core::profile::Profile::description() const noexcept { return _description; }
