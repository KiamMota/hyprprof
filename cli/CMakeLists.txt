add_executable(hyprprof ${CLI_SRC})
target_include_directories(hyprprof 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cli
        ${CMAKE_CURRENT_SOURCE_DIR}/cli
)

target_link_libraries(hyprprof PRIVATE hyprprof_lib)
