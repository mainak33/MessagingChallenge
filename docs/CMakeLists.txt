# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)


# if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease") #Use this to restrict doc building to release
# Find all the public headers
get_target_property(MESSAGES_PUBLIC_HEADER_DIR messages INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE MESSAGES_PUBLIC_HEADERS ${MESSAGES_PUBLIC_HEADER_DIR}/*.h)

# set input and output files
set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/messages)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/xml/index.xml)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# Request to configure the Doxygen file
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR}) #Doxygen won't create this for us

add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
               DEPENDS ${CAT_CUTIFIER_PUBLIC_HEADERS}
               COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
               MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
               COMMENT "Generating docs")

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})
#endif()    
