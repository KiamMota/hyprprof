file(GLOB_RECURSE TEST_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(tests ${TEST_SRC})

target_link_libraries(tests PRIVATE hyprprof_lib)

