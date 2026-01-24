add_executable(hyprprof ${CLI_SRC})

target_include_directories(hyprprof PRIVATE ${CMAKE_SOURCE_DIR}/cli)
target_link_libraries(hyprprof PRIVATE hyprprof_lib)
