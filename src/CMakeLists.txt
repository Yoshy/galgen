cmake_minimum_required(VERSION 3.6)

project(GalaxyGenerator
	LANGUAGES CXX
)

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory. Please do an out-of-source build. Feel free to remove CMakeCache.txt and CMakeFiles now.")
endif()

set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT galaxy_viewer)

add_subdirectory(libgalgen)
add_subdirectory(galaxy_viewer)
