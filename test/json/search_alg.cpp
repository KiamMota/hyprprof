
#include "json/json_base.hpp"
#include <iostream>

class A : public json::JSONBase
{
  public:
    A(const std::string& json_str) : json::JSONBase(json_str) {}


};

const std::string json_string_test()
{
  return R"({"a":{"b":"i like C"}})";;
}

int main()
{
  std::cout<< "SEACH ALG" << std::endl;
  A a{json_string_test()};
}
