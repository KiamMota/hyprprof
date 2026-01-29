#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>
namespace infra
{
namespace os 
{

class PipeException : public std::runtime_error {  
public:
    PipeException(const std::string& msg) : std::runtime_error(msg) {}
};

class ForkException : public std::runtime_error {
public:
    ForkException(const std::string& msg) : std::runtime_error(msg) {}
};
}
}
#endif // EXCEPTION_HPP
