
# Add headers for Version
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/messagesVersion.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/include/messages/messagesVersion.h")

# Headers and Sources
# Globs are not recommended by CMake, but the following may be used if they are to be used
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
# file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
set (SOURCE_LIST 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/baseMessage.cpp"       
    "${CMAKE_CURRENT_SOURCE_DIR}/src/derivedMessage.cpp"  
    "${CMAKE_CURRENT_SOURCE_DIR}/src/printMessage.cpp" )

set (HEADER_LIST
    "${CMAKE_CURRENT_SOURCE_DIR}/include/messages/baseMessage.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/messages/derivedMessage.h"  
    "${CMAKE_CURRENT_SOURCE_DIR}/include/messages/printMessage.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/messages/messagesVersion.h")


# Make an automatic library - will be static or dynamic based on user setting
add_library(messages "${SOURCE_LIST}" "${HEADER_LIST}")

add_library(messages::messages ALIAS messages) 

# Make the headers public
set_target_properties(messages PROPERTIES 
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      )

if(WIN32)
  target_link_libraries(messages wsock32 ws2_32)
endif()

target_include_directories(messages PUBLIC 
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/messages>)  

# All users of this library will need at least C++11
target_compile_features(messages PUBLIC cxx_std_11)

install(TARGETS messages
        EXPORT messagesTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT messagesTargets
        FILE messagesTargets.cmake
        NAMESPACE messages::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/messages")

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/messages"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/messages"
        FILES_MATCHING PATTERN "*.h*")

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/messagesConfigVersion.cmake"
    VERSION ${messages_VERSION}
    COMPATIBILITY AnyNewerVersion)

install(FILES 
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/messagesConfig.cmake"
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/messagesConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/messages")


# IDEs should put the headers in a nice place
# source_group(
#   TREE "${PROJECT_SOURCE_DIR}/include"
#   PREFIX "Header Files"
#   FILES ${HEADER_LIST})

  