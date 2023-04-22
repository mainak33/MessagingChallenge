# To include any dependencies in the futute use the following
#nclude(CMakeFindDependencyMacro)
#find_dependency(Bar 2.0

get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_DIR}" PATH)
include("${SELF_DIR}/messages/messagesTargets.cmake")