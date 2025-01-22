find_package(gz-transport13 QUIET REQUIRED OPTIONAL_COMPONENTS log)
target_link_libraries(${LF_MAIN_TARGET} PUBLIC gz-transport13::core)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
target_link_libraries(${LF_MAIN_TARGET} PUBLIC Eigen3::Eigen)
 
string(REPLACE "\"" "" LF_SOURCE_DIRECTORY_STRIPPED ${LF_SOURCE_DIRECTORY})

target_sources(${LF_MAIN_TARGET} PUBLIC ${LF_SOURCE_DIRECTORY_STRIPPED}/include/lf_gazebo.c)
target_include_directories(${LF_MAIN_TARGET} PUBLIC ${LF_SOURCE_DIRECTORY_STRIPPED}/include)
target_compile_definitions(reactor-c PUBLIC LF_SIMULATE_PHYSICAL_TIME)
