# Headers and Sources
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${MessagingChallenge_SOURCE_DIR}/include/*.h")
file(GLOB SOURCE_LIST "${MessagingChallenge_SOURCE_DIR}/src/*.cpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(messages ${SOURCE_LIST} ${HEADER_LIST})

# add_executable(messagingchallenge ${SOURCE_LIST})

if(WIN32)
  target_link_libraries(messages wsock32 ws2_32)
endif()

target_include_directories(messages PUBLIC ../include)

# All users of this library will need at least C++11
target_compile_features(messages PUBLIC cxx_std_11)

# # IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
