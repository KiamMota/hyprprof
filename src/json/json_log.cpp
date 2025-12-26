#include "json/json_log.hpp"

void json::log::member_not_found(const std::string &object, const std::string &member_name)
{
  json::log::err("\"" + member_name + "\"" + " not found in " + "\"" + object + "\" " + "object.");
}

void json::log::member_not_found(const std::string &member_name)
{
  json::log::err("member named \"" + member_name + "\" not found");
}

void json::log::object_not_found(const std::string &object)
{
  json::log::err("the object named \"" + object + "\" is not found.");
}
