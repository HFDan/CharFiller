cmake_minimum_required(VERSION 3.8)

project (CharFiller)

if (MSVC)
	add_compile_definitions(MSVC)

else()
	add_link_options(-pthread)

endif()

add_subdirectory(src)