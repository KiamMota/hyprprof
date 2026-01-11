#ifndef MACROS_HPP
#define MACROS_HPP

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
  #define FUNC_DISCARD [[nodiscard]]
#elif defined(_MSC_VER)
  #define DISCARD [[nodiscard]]
#endif

#define DISCARD auto _ =

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#if defined(__clang__) || defined(__GNUC__)
    #define TODO(msg) _Pragma(TOSTRING(message ("TODO: " __FILE__ ":" TOSTRING(__LINE__) " - " msg)))
#elif defined(_MSC_VER)
    #define TODO(msg) __pragma(message("TODO: " __FILE__ "(" TOSTRING(__LINE__) "): " msg))
#else
    #define TODO(msg)
#endif


#endif // MACROS_HPP

