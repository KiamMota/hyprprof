cmake_minimum_required(VERSION 3.16)
project(hyprprof)

if (NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(FATAL_ERROR
        "Hyprprof is a Linux-exclusive application. "
        "It is not supported on other operating systems."
    )
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE LIB_SRC
     CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE CLI_SRC 
  CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/cli/*.cpp"
)

add_library(hyprprof_lib ${LIB_SRC})
target_include_directories(hyprprof_lib
    PUBLIC include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/
)

add_subdirectory(test)
add_subdirectory(cli)

install(TARGETS hyprprof
        RUNTIME DESTINATION /usr/local/bin
)
