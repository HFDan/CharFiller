cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)

project (CharFiller)

if (UNIX)
	add_compile_definitions(UNIX)
	add_link_options(-pthread -O2)
endif()


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Binaries")


add_executable(CharFiller "src/Main.cpp" "src/UI/ProgressBar/ProgressBar.h" "src/UI/ProgressBar/ProgressBar.cpp" "src/Util/Files/Files.h" "src/Util/Files/Files.cpp")
target_include_directories(CharFiller PUBLIC "${PROJECT_SOURCE_DIR}")