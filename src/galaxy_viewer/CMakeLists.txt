cmake_minimum_required (VERSION 3.6)
if (COMMAND cmake_policy)
    cmake_policy (SET CMP0003 NEW)
    cmake_policy (SET CMP0022 NEW)
    cmake_policy (SET CMP0026 OLD)
    cmake_policy (SET CMP0042 NEW)
    cmake_policy (SET CMP0063 OLD)
endif ()

if (NOT URHO3D_HOME)
    message(FATAL_ERROR "Undefined 'URHO3D_HOME' variable. Set it with cmake's '-D' switch")
endif()

project(galaxy_viewer
	LANGUAGES C CXX
)

set (CMAKE_MODULE_PATH ${URHO3D_HOME}/share/CMake/Modules)
include (UrhoCommon)
set (TARGET_NAME galaxy_viewer)

define_source_files ()
setup_main_executable ()

# Copy data to build tree to be able to run/debug application from IDE using generated project files
add_custom_command(TARGET galaxy_viewer PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
				   ${URHO3D_HOME}/share/Resources/CoreData $<TARGET_FILE_DIR:galaxy_viewer>/CoreData
)
add_custom_command(TARGET galaxy_viewer PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
				   ${CMAKE_CURRENT_SOURCE_DIR}/bin/Data $<TARGET_FILE_DIR:galaxy_viewer>/Data
)

set(GALAXY_VIEWER_DEPENDENCIES
    libgalgen
)
add_dependencies(galaxy_viewer "${GALAXY_VIEWER_DEPENDENCIES}")
target_link_libraries(galaxy_viewer "${GALAXY_VIEWER_DEPENDENCIES}")

include(GNUInstallDirs)

install(DIRECTORY
    ${URHO3D_HOME}/share/Resources/CoreData ${CMAKE_CURRENT_SOURCE_DIR}/bin/Data DESTINATION ${CMAKE_INSTALL_BINDIR}
)
