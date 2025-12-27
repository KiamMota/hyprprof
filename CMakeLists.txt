cmake_minimum_required(VERSION 3.16)
project(hyprprof)
# this helps me with clangd

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE LIB_SRC
     CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE CLI_SRC 
  CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/cli/*.cpp"
)

# creating the hyprprof lib

add_library(hyprprof ${LIB_SRC})
target_include_directories(hyprprof PUBLIC include ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

# creating the executable cli

add_executable(hyprprof_cli ${CLI_SRC})
target_include_directories(hyprprof_cli PRIVATE include/cli)
target_link_libraries(hyprprof_cli PRIVATE hyprprof)

add_subdirectory(test/integration)

