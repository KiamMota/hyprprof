#include "environment.hpp"
#include "json/json_file_parser.hpp"

int main(int argn, char** argv) {
  env::Environment env;
  json::JsonFileParser json("../hyprprof.json");
  json.Parse();
}
