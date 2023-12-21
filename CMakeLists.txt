cmake_minimum_required(VERSION 3.24)
project(projekt_Netsim)
include_directories(include)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)

include_directories(include)

set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        src/helpers.cpp
        src/nodes.cpp
        )

add_executable(projekt_Netsim ${SOURCE_FILES} main.cpp src/helpers.cpp src/helpers.cpp src/helpers.cpp src/helpers.cpp src/nodes.cpp src/nodes.cpp src/nodes.cpp)

set(SOURCES_FILES_TESTS
        test/main_gtest.cpp
        test/test_Factory.cpp
        test/test_factory_io.cpp
        test/test_nodes.cpp
        test/test_package.cpp
        test/test_reports.cpp
        test/test_simulate.cpp
        test/test_storage_types.cpp)

add_executable(projekt_Netsim_test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)

target_include_directories(projekt_Netsim_test PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        mocks
        )

add_subdirectory(googletest-master)

target_link_libraries(projekt_Netsim_test gmock)

target_compile_definitions(projekt_Netsim_test PUBLIC EXERCISE_ID=EXERCISE_ID_NODES)
