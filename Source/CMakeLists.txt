project( Drivetrain )

add_library( ${PROJECT_NAME} SHARED "" )

set( ${PROJECT_NAME}_VERSION_MAJOR 0 )
set( ${PROJECT_NAME}_VERSION_MINOR 1 )
set( ${PROJECT_NAME}_VERSION_PATCH 0 )
set( ${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH} )

set_target_properties( ${PROJECT_NAME} 
    PROPERTIES 
        VERSION ${${PROJECT_NAME}_VERSION} 
        SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR}
        LIBRARY_OUTPUT_DIRECTORY ${APPLICATION_COMPONENT_PLUGINS_DIR}
)

# TODO: Fix that nasty hack some other way --> create FindCore.cmake script?
## Core module references
# The root directory where all Core header files are located
include_directories( ${CMAKE_SOURCE_DIR}/Core/Source )
# Some Core module headers are generated during the build
include_directories( ${CMAKE_BINARY_DIR}/Core/Source )

# Add current source directories to include directories list
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

# Gear
include_directories( Gear )
add_subdirectory( Gear )

# Generate version header
set( PLUGIN_VERSION_HEADER Version.h )
add_custom_command( OUTPUT ${PLUGIN_VERSION_HEADER}
	COMMAND ${PYTHON_EXECUTABLE} ${COMPONENT_GENERATORS_DIR}/GeneratePluginVersion.py
		--output ${PLUGIN_VERSION_HEADER}
		--version ${${PROJECT_NAME}_VERSION}
		--component ${PROJECT_NAME}
)
set_source_files_properties( ${PLUGIN_VERSION_HEADER} PROPERTIES GENERATED 1 )

# Generate export header
generate_export_header( ${PROJECT_NAME} EXPORT_FILE_NAME ${PROJECT_NAME}Export.h )

target_sources( ${PROJECT_NAME}	
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/Drivetrain.h"
		"${CMAKE_CURRENT_LIST_DIR}/Drivetrain.cpp"
		"${PLUGIN_VERSION_HEADER}"
)

target_compile_options( ${PROJECT_NAME} 
    PUBLIC 
        -fvisibility=hidden 
        -fvisibility-inlines-hidden 
        -Wl,--no-undefined 
        -fPIC
)

target_link_libraries( ${PROJECT_NAME} 
	Gear
)