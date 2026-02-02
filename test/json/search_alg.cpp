
#include "json/json_base.hpp"
#include <iostream>

class A : public json::JsonBase
{
  public:
    A(const std::string& json_str) : json::JsonBase(json_str) {}


};

const std::string json_string_test()
{
  return R"({"a":{"b":"i like C"}})";;
}

int main()
{
  std::cout<< "SEACH ALG" << std::endl;
  A a{json_string_test()};
  std::string r = a.get_value("a.b");
  std::cout << "r: " << r << std::endl;
}
