cmake_minimum_required(VERSION 3.8)
add_subdirectory(UI)
add_executable(CharFiller Main.cpp "UI/ProgressBar/ProgressBar.h" "UI/ProgressBar/ProgressBar.cpp")