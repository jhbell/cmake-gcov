cmake_minimum_required(VERSION 3.5)
project(CMake_GCov CXX)

# Set the compiler options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

# Create OBJECT_DIR variable
set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/RunAdder.dir)
message("-- Object files will be output to: ${OBJECT_DIR}")

# Set the sources
set(SOURCES
    RunAdder.cpp
    Adder.cpp
    )

# Create the executable
add_executable(RunAdder ${SOURCES})

# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov
    COMMAND mkdir -p coverage
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
add_custom_command(TARGET gcov
    COMMAND echo "=================== GCOV ===================="
    COMMAND gcov -b ${CMAKE_SOURCE_DIR}/*.cpp -o ${OBJECT_DIR}
        | grep -A 5 "Adder.cpp" > CoverageSummary.tmp
    COMMAND cat CoverageSummary.tmp
    COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/coverage"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage  # Need separate command for this line
    )
add_dependencies(gcov RunAdder)
# Make sure to clean up the coverage folder
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES coverage)

# Create the gcov-clean target. This cleans the build as well as generated 
# .gcda and .gcno files.
add_custom_target(scrub
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    COMMAND rm -f ${OBJECT_DIR}/*.gcno
    COMMAND rm -f ${OBJECT_DIR}/*.gcda
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

# Testing
enable_testing()

add_test(output_test ${CMAKE_CURRENT_BINARY_DIR}/RunAdder)
set_tests_properties(output_test PROPERTIES PASS_REGULAR_EXPRESSION "0;5;10")
