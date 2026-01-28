#ifndef APP_SERVICE_HPP
#define APP_SERVICE_HPP

#include <string>
namespace app_service
{
  class Install
  {
    private:
      void ensure_important_paths();


    public:
      Install(const std::string& curr_path);
      
  
  };
}

#endif
