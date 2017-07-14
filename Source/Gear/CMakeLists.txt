project( Gear )

add_library( ${PROJECT_NAME} STATIC "" )

# Define DesignRules database
set( DESIGN_RULES_DATABASE_FILE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DesignRules.db )

# Define generated header filename
set( PARAMETER_TAG_COLLECTION_HEADER ${CMAKE_CURRENT_BINARY_DIR}/GearParameterTagCollection.h )

# Generate constrained parameter identification header
add_custom_command( OUTPUT ${PARAMETER_TAG_COLLECTION_HEADER}
	COMMAND ${PYTHON_EXECUTABLE} ${COMPONENT_GENERATORS_DIR}/GenerateParameterTagCollection.py
		--output ${PARAMETER_TAG_COLLECTION_HEADER}
		--database ${APPLICATION_DESIGN_RULES_DATABASE_FILE}
		--component ${PROJECT_NAME}
	DEPENDS ${APPLICATION_DESIGN_RULES_DATABASE_FILE}
)
set_source_files_properties( ${PARAMETER_TAG_COLLECTION_HEADER} PROPERTIES GENERATED 1 )

include( Design/CMakeLists.txt )

target_sources( ${PROJECT_NAME}	
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/Gear.h"
		"${CMAKE_CURRENT_LIST_DIR}/Gear.cpp"
		"${CMAKE_CURRENT_LIST_DIR}/GearTypes.h"
		"${PARAMETER_TAG_COLLECTION_HEADER}"
)

# Generate export header
generate_export_header( ${PROJECT_NAME} EXPORT_FILE_NAME ${PROJECT_NAME}Export.h )

target_compile_options( ${PROJECT_NAME} 
    PUBLIC
        -fvisibility=hidden
        -fvisibility-inlines-hidden
        -Wl,--no-undefined 
        -fPIC
)

target_link_libraries( ${PROJECT_NAME} 
    Core
    ${OpenCascade_LIBRARIES} 
)