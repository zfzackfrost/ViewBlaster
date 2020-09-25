# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ViewBlaster_SOURCE_DIR}/include/viewblaster/*.hpp")

set(SRC_LIST "")
list(APPEND SRC_LIST "core/App.cpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(ViewBlaster ${SRC_LIST} ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(ViewBlaster PUBLIC ${ViewBlaster_SOURCE_DIR}/include)
target_link_libraries(ViewBlaster PRIVATE Boost::boost)
target_link_libraries(ViewBlaster PUBLIC ViewBlasterConfig fmt::fmt)

if (GFX_API STREQUAL VK)
    target_link_libraries(ViewBlaster PUBLIC ViewBlaster_Vk)
endif()

# All users of this library will need at least C++11
target_compile_features(ViewBlaster PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
