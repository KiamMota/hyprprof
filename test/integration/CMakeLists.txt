# test/integration/CMakeLists.txt
set(INTEGRATION_SRC integration1.cpp)
add_executable(integration_test ${INTEGRATION_SRC})
target_link_libraries(integration_test PRIVATE hyprprof)
# os includes já vêm do hyprprof PUBLIC

