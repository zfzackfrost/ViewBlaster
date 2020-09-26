FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm
    GIT_TAG        master
)
FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
    FetchContent_Populate(glm)
    add_library(glm::glm IMPORTED INTERFACE)
    set_property(TARGET glm::glm PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${glm_SOURCE_DIR}")
endif()
