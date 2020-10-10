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

# This is just a simple test routine. It only checks that 1 == 1
# and is mainly to ensure that everything is working.
add_executable(simple_test
	test/simple_test.cpp
)
target_link_libraries(simple_test
	gtest_main
)
add_test(SimpleTest simple_test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
