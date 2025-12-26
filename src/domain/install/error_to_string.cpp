#include "domain/install/json_file_parser.hpp"  

const char* domain::install::JsonErrorToString(JsonFileParserError e)
{
   switch (e) {
        case JsonFileParserError::NoError:
            return "no error";
        case JsonFileParserError::PlaceHolder:
            return "unspecified validation error";
        case JsonFileParserError::NoSchema:
            return "missing schema field";
        case JsonFileParserError::ParsingError:
            return "failed to parse json";
        case JsonFileParserError::EmptyJSON:
            return "json is empty";
        case JsonFileParserError::JsonFileIsEmpty:
            return "json file is empty";
        case JsonFileParserError::NoHyprProfObject:
            return "missing hyprprof object";
        case JsonFileParserError::NoAppsObject:
            return "missing apps object";
        case JsonFileParserError::NoTerminalObject:
            return "missing terminal object";
    }
    std::abort(); 
}
