cmake_minimum_required(VERSION 3.0.0)
project(algorithms
	VERSION 1.0.0
	LANGUAGES CXX
	HOMEPAGE_URL https://github.com/kylerobots/algorithms
	DESCRIPTION "A collection of routines from Algorithms"
)

# Set up Google Test.
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
)
if(result)
	message(FATAL_ERROR "CMake step for googletest failed: ${result}")	
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
)
if(result)
	message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()
# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(
	${CMAKE_CURRENT_BINARY_DIR}/googletest-src
    ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
	EXCLUDE_FROM_ALL
)

include(CTest)
enable_testing()

# This is a simple executable that just prints which version
# of C++ is being used. It is basically a "Hello World" check.
add_executable(cpp_version
	src/main.cpp
)

# This is a header-only library that contains all of my implementations.
add_library(algorithms INTERFACE)
target_include_directories(algorithms
	INTERFACE include
)

# This is all of the tests for the entire algorithm library.
add_executable(unit_tests
	test/test_binary_tree.cpp
	test/test_bucket_sort.cpp
	test/test_counting_sort.cpp
	test/test_double_sorting.cpp
	test/test_longest_substring.cpp
	test/test_max_subarray.cpp
	test/test_radix_sort.cpp
	test/test_red_black_tree.cpp
	test/test_rod_cut.cpp
	test/test_sanity_check.cpp
)
target_link_libraries(unit_tests
	PUBLIC
		algorithms
		gtest_main
)
add_test(UnitTests unit_tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
