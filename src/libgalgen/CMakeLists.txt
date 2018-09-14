cmake_minimum_required(VERSION 3.6)

project(libgalgen
    LANGUAGES CXX
)

set(GALGEN_PUBLIC_HEADERS
    include/Vector3.h
    include/GalaxyGenerator.h
)

set(GALGEN_PRIVATE_HEADERS
        src/BaseGenerator.h
    src/Vector3Array.h
    src/Mutator.h
)

set(GALGEN_SOURCES
    src/Vector3Array.cpp
    src/BaseGenerator.cpp
    src/Mutator.cpp
    src/GalaxyGenerator.cpp
)

add_library(libgalgen
	${GALGEN_PUBLIC_HEADERS}
	${GALGEN_PRIVATE_HEADERS}
    ${GALGEN_SOURCES}
)
target_compile_features(libgalgen PUBLIC cxx_std_11)
set_target_properties(libgalgen PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(libgalgen PROPERTIES PUBLIC_HEADER "${GALGEN_PUBLIC_HEADERS}")

target_include_directories(libgalgen
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
	    ${CMAKE_CURRENT_SOURCE_DIR}
)

include(GNUInstallDirs)

export(TARGETS libgalgen FILE libgalgenTargets.cmake)
export(PACKAGE libgalgen)

install(TARGETS libgalgen
    EXPORT libgalgen-targets
	PUBLIC_HEADER DESTINATION include
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
)
install(EXPORT libgalgen-targets
    FILE libgalgenConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
)
