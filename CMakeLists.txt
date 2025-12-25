cmake_minimum_required(VERSION 3.16)
project(hyprprof)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC
     CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(hyprprof ${SRC})
target_include_directories(hyprprof PRIVATE include ${CMAKE_CURRENT_SOURCE_DIR}/rapidjson/include)

