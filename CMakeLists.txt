cmake_minimum_required(VERSION 3.0)

project(Forward_Chaining C)

add_subdirectory(rule)

enable_testing()
add_subdirectory(tests)

#add_executable(main main.c)
#add_dependencies(main rule)
#target_link_libraries(main rule)