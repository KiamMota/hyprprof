#include "json/json_manifest_writer.hpp"

namespace json
{
  JSONManifestWriter::JSONManifestWriter() 
  { 
    _json_str = {};
    doc.SetObject();
    auto& alloc = doc.GetAllocator();
  }

  



}
