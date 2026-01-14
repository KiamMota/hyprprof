#include "core/install/json_manifest_validator.hpp"  

const char* core::install::JsonErrorToString(JsonFileParserError e)
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
        case JsonFileParserError::TypeError:
            return "type is incorrect to current object";
        case JsonFileParserError::EmptyOrNullValue:
            return "empty or null value to current object";
    }
    std::abort(); 
}
