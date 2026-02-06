#include "dotconfig.hpp"

namespace core
{

// Setters
Dotconfig& Dotconfig::set_name(const std::string& name)
{
    _name = name;
    return *this;
}

Dotconfig& Dotconfig::set_pack(const std::string& pack)
{
    _pack = pack;
    return *this;
}

Dotconfig& Dotconfig::set_target_path(const std::string& path)
{
    _target_path = path;
    return *this;
}

Dotconfig& Dotconfig::set_source_path(const std::string& path)
{
    _source_path = path;
    return *this;
}

// Getters
const std::string& Dotconfig::name() const noexcept
{
    return _name;
}

const std::string& Dotconfig::pack() const noexcept
{
    return _pack;
}

const std::string& Dotconfig::target() const noexcept
{
    return _target_path;
}

const std::string& Dotconfig::source_path() const noexcept
{
    return _source_path;
}

}

