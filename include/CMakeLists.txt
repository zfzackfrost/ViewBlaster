######################################################################
#                     Configuration Header File                      #
######################################################################

if(GFX_API STREQUAL VK)
    set(GFX_API_VK ON)
endif()

configure_file("viewblaster/config.hpp.in" "viewblaster/config.hpp" @ONLY)

add_library(ViewBlasterConfig INTERFACE)
target_include_directories(ViewBlasterConfig INTERFACE ${CMAKE_CURRENT_BINARY_DIR})
