#include "dotfile.hpp"

namespace core
{

// Setters
DotFile& DotFile::set_name(const std::string& name)
{
    _name = name;
    return *this;
}

DotFile& DotFile::set_pack(const std::string& pack)
{
    _pack = pack;
    return *this;
}

DotFile& DotFile::set_target_path(const std::string& path)
{
    _target_path = path;
    return *this;
}

DotFile& DotFile::set_source_path(const std::string& path)
{
    _source_path = path;
    return *this;
}

// Getters
const std::string& DotFile::name() const noexcept
{
    return _name;
}

const std::string& DotFile::pack() const noexcept
{
    return _pack;
}

const std::string& DotFile::target() const noexcept
{
    return _target_path;
}

const std::string& DotFile::source_path() const noexcept
{
    return _source_path;
}

}

