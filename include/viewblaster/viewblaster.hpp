/**
 * @file viewblaster.hpp
 * @author Zachary Frost
 * @copyright See repository LICENSE file
 * @brief Primary include header.
 */

#pragma once

#include <viewblaster/config.hpp>

#include <viewblaster/common/core/App.hpp>
#include <viewblaster/common/render/Buffer.hpp>

#ifdef GFX_API_VK
    #include <viewblaster/backends/vulkan/VulkanApp.hpp>
    #include <viewblaster/backends/vulkan/VulkanBuffer.hpp>
#endif
