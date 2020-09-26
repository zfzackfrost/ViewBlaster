# Works with 3.11 and tested through 3.18
cmake_minimum_required(VERSION 3.12...3.18)

# Project name and a few useful settings. Other commands can pick up the results
project(
    ViewBlaster
    VERSION 0.1.0
    DESCRIPTION "Modern, multi-platform and multi-API realtime rendering engine for C++17"
    LANGUAGES CXX)

######################################################################
#                           Configuration                            #
######################################################################

set(VIEW_BLASTER_COLORED_OUTPUT ${UNIX} CACHE BOOL "Should terminal messages be printed in color with ANSI escape sequences.")

set(GFX_API "" CACHE STRING "The graphics API to use. Can be one of: `VK`")
if(GFX_API STREQUAL VK)
else()
    message(STATUS "----------------------------------------------------------------------------------------")
    message(STATUS "")
    message(STATUS " Graphics API not set to a valid value:")
    message(STATUS "")
    message(STATUS " Invoke CMake in one of the following ways:")
    message(STATUS "    cmake <project_root> -DGFX_API=VK")
    message(STATUS "")
    message(STATUS "----------------------------------------------------------------------------------------")
    message(FATAL_ERROR "")
endif()

set(_MAIN_PROJECT OFF)
# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(_MAIN_PROJECT ON)

    # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

    # Let's ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)

    # C++ Standard
    set(CMAKE_CXX_STANDARD 17)

    # Support folders in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Testing only available if this is the main app
    # Note this needs to be done in the main CMakeLists
    # since it calls enable_testing, which must be in the
    # main CMakeLists.
    include(CTest)

    # Docs only available if this is the main app
    find_package(Doxygen)
    if(Doxygen_FOUND)
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found, not building docs")
    endif()
endif()

set(VIEW_BLASTER_BUILD_EXAMPLES ${_MAIN_PROJECT} CACHE BOOL "Build example applications")

######################################################################
#                            Dependencies                            #
######################################################################

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)
# FetchContent_MakeAvailable was not added until CMake 3.14; use our shim
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

find_package(Boost 1.70 REQUIRED)

include(cmake/LoadSDL2.cmake)
include(cmake/LoadGLM.cmake)

# Formatting library
FetchContent_Declare(
    fmtlib
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 7.0.3)
FetchContent_MakeAvailable(fmtlib)

######################################################################
#                              Targets                               #
######################################################################

add_subdirectory(include)
add_subdirectory(src)

if(VIEW_BLASTER_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Testing only available if this is the main app
# Emergency override VIEW_BLASTER_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR VIEW_BLASTER_BUILD_TESTING)
    AND BUILD_TESTING)
    add_subdirectory(tests)
endif()
