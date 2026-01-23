cmake_minimum_required(VERSION 3.16)
project(hyprprof)

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

add_library(hyprprof_lib ${LIB_SRC})
target_include_directories(hyprprof_lib
    PUBLIC include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/
)

# creating the executable cli

add_executable(hyprprof ${CLI_SRC})
target_include_directories(hyprprof 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cli
        ${CMAKE_CURRENT_SOURCE_DIR}/cli
)

target_link_libraries(hyprprof PRIVATE hyprprof_lib)

