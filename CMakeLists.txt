cmake_minimum_required(VERSION 3.8)
project (CharFiller)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (UNIX)
	add_compile_definitions(UNIX)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Binaries")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Libraries")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Libraries")

add_subdirectory(${PROJECT_SOURCE_DIR}/src/lib/)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/lib/thirdparty/argparse)
set(ARGPARSE_TEST_ENABLE OFF CACHE BOOL "Build unit tests" FORCE)
set(ARGPARSE_BUILD_EXAMPLE OFF CACHE BOOL "Build example" FORCE)

add_executable(CharFiller "src/Main.cpp")
set_target_properties(CharFiller PROPERTIES PREFIX "${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}_")
target_include_directories(CharFiller PRIVATE "${PROJECT_SOURCE_DIR}/src/lib")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(CharFiller PUBLIC Threads::Threads PRIVATE libcharfiller PRIVATE argparse)
