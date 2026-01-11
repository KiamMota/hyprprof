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
        case domain::install::JsonFileParserError::TypeError:
            return "type is incorrect to current object";
        case domain::install::JsonFileParserError::EmptyOrNullValue:
            return "empty or null value to current object";
    }
    std::abort(); 
}
