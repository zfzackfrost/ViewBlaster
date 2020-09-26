/**
 * @file VulkanApp.hpp
 * @author Zachary Frost
 * @copyright See repository LICENSE file
 * @brief `VulkanApp` class declaration.
 */

#pragma once

#include <viewblaster/common/core/App.hpp>

#include <viewblaster/backends/vulkan/vk.hpp>

#include <SDL2/SDL.h>

namespace viewblaster {
    class VulkanApp : public AbstractApp
    {
    protected:
        utils::Result<utils::Void> EarlyInitialize() override;
        utils::Result<utils::Void> LateInitialize() override;
        utils::Result<utils::Void> SetupSDL() final;
        utils::Result<utils::Void> SetupGfxAPI() final;

        utils::Result<utils::Void> Update(ElapsedT Delta) override;

        utils::Result<utils::Void> RenderScene() override;
        utils::Result<utils::Void> RenderFrame() override;

        utils::Result<utils::Void> CleanUp() override;
        utils::Result<utils::Void> CleanUpGfxAPI() override;

        void MainLoop() override;

        struct
        {
            vk::Instance Instance;
            vk::PhysicalDevice PhysicalDevice;
        } StateVk;

    private:
        utils::Result<utils::Void> CreateInstanceVk();
        utils::Result<utils::Void> PickPhysicalDeviceVk();
        utils::Result<bool> IsDeviceSuitableVk(vk::PhysicalDevice Device);

    };

    using App = VulkanApp;
} // namespace viewblaster
