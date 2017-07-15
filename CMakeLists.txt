cmake_minimum_required(VERSION 3.5)
project(Hello CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

set(CMAKE_FILES_DIRECTORY ${CMAKE_BINARY_DIR})
set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/RunHello.dir)
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES coverage)

message("-- Object files have been output to: ${OBJECT_DIR}")

add_executable(RunHello RunHello.cpp Hello.cpp)

enable_testing()

add_test(output_test ${CMAKE_CURRENT_BINARY_DIR}/RunHello)
set_tests_properties(output_test PROPERTIES PASS_REGULAR_EXPRESSION "Hello")

add_custom_target(gcov)
add_custom_command(TARGET gcov
    COMMAND mkdir -p coverage
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
add_custom_command(TARGET gcov
    COMMAND make test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
add_custom_command(TARGET gcov
    COMMAND gcov -b ${CMAKE_SOURCE_DIR}/*.cpp -o ${OBJECT_DIR} | grep -A 5 "Hello.cpp" > Coverage.tmp
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
    )
add_custom_command(TARGET gcov
    COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/coverage"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_dependencies(gcov RunHello)
