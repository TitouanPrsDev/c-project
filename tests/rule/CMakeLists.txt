include_directories(${CMAKE_SOURCE_DIR}/rule)

find_program(VALGRIND "valgrind")

include(CMakeDependentOption)
cmake_dependent_option(USE_VALGRIND "Don't run valgrind tests" OFF "VALGRIND" OFF)

file(GLOB TEST_SRC
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/test-*.c")

foreach(TEST_FILE ${TEST_SRC})

    string(REPLACE ".c" "" TEST_NAME ${TEST_FILE})

    add_executable(${TEST_NAME} ${TEST_FILE})
    add_dependencies(${TEST_NAME} rule)
    target_link_libraries(${TEST_NAME} rule)

    if(USE_VALGRIND)
        add_test(${TEST_NAME}[valgrind] ${VALGRIND} --leak-check=full --quiet --error-exitcode=1 ./${TEST_NAME})
        add_test(${TEST_NAME}[normal] ./${TEST_NAME})
    else()
        add_test(${TEST_NAME} ./${TEST_NAME})
    endif()

endforeach(TEST_FILE ${TEST_SRC})