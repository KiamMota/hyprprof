file(GLOB_RECURSE TEST_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(test_file IN LISTS TEST_SRC)
    # Pega o nome do arquivo sem caminho e extensão
    get_filename_component(test_name ${test_file} NAME_WE)
    
    # Cria um executável por arquivo
    add_executable(${test_name} ${test_file})
    
    # Linka a sua biblioteca
    target_link_libraries(${test_name} PRIVATE hyprprof_lib)
endforeach()

