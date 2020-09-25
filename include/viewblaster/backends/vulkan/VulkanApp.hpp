/**
 * @file VulkanApp.hpp
 * @author Zachary Frost
 * @copyright See repository LICENSE file
 * @brief `VulkanApp` class declaration.
 */

#pragma once

#include <viewblaster/common/core/App.hpp>

#include <SDL2/SDL.h>

namespace viewblaster {
    class VulkanApp : public AbstractApp
    {
    protected:
        utils::Result<utils::Void> Initialize() override;
        utils::Result<utils::Void> SetupSDL() final;
        utils::Result<utils::Void> SetupGfxAPI() final;

        utils::Result<utils::Void> Update(ElapsedT Delta) override;

        utils::Result<utils::Void> RenderScene() override;
        utils::Result<utils::Void> RenderFrame() override;

        utils::Result<utils::Void> CleanUp() override;
    private:
        std::string mTitle;
    };

    using App = VulkanApp;
} // namespace viewblaster
