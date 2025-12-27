# tests/integration/CMakeLists.txt
set(INTEGRATION_SRC 
  integration1.cpp
)

add_executable(integration_test ${INTEGRATION_SRC})
target_link_libraries(integration_test PRIVATE hyprprof)
# inclui headers da biblioteca automaticamente se hyprprof tem PUBLIC includes

