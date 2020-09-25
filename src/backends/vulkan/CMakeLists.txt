set(SRC_LIST "")
list(APPEND SRC_LIST "VulkanBuffer.cpp")

find_package(Vulkan REQUIRED)

add_library(ViewBlaster_Vk INTERFACE)
target_sources(ViewBlaster_Vk INTERFACE ${SRC_LIST})
target_include_directories(ViewBlaster_Vk INTERFACE ${ViewBlaster_SOURCE_DIR}/include)
target_link_libraries(ViewBlaster_Vk INTERFACE Vulkan::Vulkan)
