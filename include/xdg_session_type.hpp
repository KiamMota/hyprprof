
#ifndef _XDG_SESSION_TYPE_HPP_
#define _XDG_SESSION_TYPE_HPP_

namespace env
{

  enum class XDG_SESSION_TYPE 
  {
    UNKNOWN,
    WAYLAND,
    TTY,
    X11
  };

}


#endif
