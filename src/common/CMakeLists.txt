file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ViewBlaster_SOURCE_DIR}/include/viewblaster/*.hpp")

set(SRC_LIST "")
list(APPEND SRC_LIST "core/App.cpp")

######################################################################
#                           Library Target                           #
######################################################################


add_library(ViewBlaster ${SRC_LIST} ${HEADER_LIST})

######################################################################
#                            Dependencies                            #
######################################################################

target_include_directories(ViewBlaster PUBLIC ${ViewBlaster_SOURCE_DIR}/include)
target_link_libraries(ViewBlaster PRIVATE Boost::boost)
target_link_libraries(ViewBlaster PUBLIC ViewBlasterConfig fmt::fmt)
target_link_libraries(ViewBlaster PUBLIC SDL2-static SDL2main)

# ================ Graphics API ================ #

if (GFX_API STREQUAL VK)
    target_link_libraries(ViewBlaster PUBLIC ViewBlaster_Vk)
endif()

######################################################################
#                          Configure Target                          #
######################################################################


# All users of this library will need at least C++11
target_compile_features(ViewBlaster PUBLIC cxx_std_17)

######################################################################
#                            Misc Config                             #
######################################################################


# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
