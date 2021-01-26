cmake_minimum_required(VERSION 3.5)
project(CMake_GCov CXX)

# Set the compiler options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

# Set the sources
set(SOURCES
    RunAdder.cpp
    Adder.cpp
    )

# Create the executable
add_executable(RunAdder ${SOURCES})

set_target_properties(RunAdder PROPERTIES COMPILE_FLAGS "--coverage")
set_target_properties(RunAdder PROPERTIES LINK_FLAGS "--coverage")

# Create the covr target. Run coverage tests with 'make covr'
add_custom_target(covr
    COMMAND mkdir -p coverage
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_custom_command(TARGET covr
    COMMAND echo "=================== LCOV ===================="

    COMMAND echo "Generating initial zero coverage..."
        COMMAND lcov -c -i --directory ${CMAKE_BINARY_DIR}
                        --output-file init_coverage.info --include **/*.cpp*

    COMMAND echo "Generating base coverage..."
        COMMAND lcov -c --directory ${CMAKE_BINARY_DIR}
                        --output-file base_coverage.info --include **/*.cpp*

    COMMAND echo "Generating combined coverage..."
        COMMAND lcov -a init_coverage.info -a base_coverage.info
                        -o coverage.info

    COMMAND echo "Generating HTML report..."
    COMMAND genhtml -o html coverage.info

    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
)

add_dependencies(covr RunAdder)
# Make sure to clean up the coverage folder
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES coverage)

# Create the covr-clean target. This cleans the build as well as generated
# .gcda and .gcno files.
add_custom_target(covr-clean
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    COMMAND rm -f ${OBJECT_DIR}/*.gcno
    COMMAND rm -f ${OBJECT_DIR}/*.gcda
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

# Testing
enable_testing()

add_test(output_test ${CMAKE_CURRENT_BINARY_DIR}/RunAdder)
set_tests_properties(output_test PROPERTIES PASS_REGULAR_EXPRESSION "0;5;10")
