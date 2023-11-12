function(CreateSourceGroups)
    # Get list of all unique directory paths
    set(PATH_LIST)
    foreach(SOURCE_FILE ${ARGV})
        get_filename_component(SOURCE_PATH ${SOURCE_FILE} PATH)
        list(APPEND PATH_LIST ${SOURCE_PATH})
    endforeach()
    list(SORT PATH_LIST)
    list(REMOVE_DUPLICATES PATH_LIST)

    # Set up source groups
    get_filename_component(PARENT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)
    foreach(UNIQUE_PATH ${PATH_LIST})
        # Scan through all source files to find those contained within the current subdirectory
        set(CONTAINED_SOURCES)
        foreach(SOURCE_FILE ${ARGV})
            get_filename_component(SOURCE_PATH ${SOURCE_FILE} PATH)
            if (${SOURCE_PATH} STREQUAL ${UNIQUE_PATH})
                list(APPEND CONTAINED_SOURCES ${SOURCE_FILE})
            endif()
        endforeach()
        # Generate group name from subdirectory path
        #message("U:  ${UNIQUE_PATH}")
        string(REPLACE "${PARENT_DIRECTORY}" "" STRIPPED_PATH ${UNIQUE_PATH})
        #message("S: ${STRIPPED_PATH}")

	if(NOT STRIPPED_PATH STREQUAL "")
        	string(REGEX REPLACE "/" "\\\\" GROUP_NAME ${STRIPPED_PATH})
	endif()
        # Create source group

        # message ("C: ${CONTAINED_SOURCES}")
        source_group(${GROUP_NAME} FILES ${CONTAINED_SOURCES})
    endforeach()
endfunction()
