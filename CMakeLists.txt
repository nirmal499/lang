cmake_minimum_required(VERSION 3.22.1)
project(lang)

include(FetchContent)

FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2
	GIT_TAG v2.13.9
	GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Catch2)
message("Fetched catch2")

option(ENABLE_TESTING "Enable a Unit Testing Build" ON)

set(LIBRARY_NAME "lang_lib")
set(EXECUTABLE_NAME "executable")

add_subdirectory(src)

if (ENABLE_TESTING)
	add_subdirectory(catch-tests) # This tests source code will be linking to our library for testing
endif()

add_subdirectory(lang)