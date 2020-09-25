add_subdirectory(common)

if (GFX_API STREQUAL VK)
    add_subdirectory(backends/vulkan)
endif()
