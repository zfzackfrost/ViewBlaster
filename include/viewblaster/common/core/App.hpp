/**
 * @file App.hpp
 * @author Zachary Frost
 * @copyright See repository LICENSE file
 * @brief `AbstractApp` class.
 */

#pragma once

#include <chrono>
#include <string>
#include <viewblaster/common/utils/Result.hpp>

#include <SDL2/SDL.h>

namespace viewblaster {
    class AbstractApp
    {
    public:
        using ElapsedT = std::chrono::steady_clock::duration;

        void Run();
        void Quit();

    protected:

        virtual utils::Result<utils::Void> Initialize() = 0;
        virtual utils::Result<utils::Void> SetupSDL() = 0;
        virtual utils::Result<utils::Void> SetupGfxAPI() = 0;

        virtual utils::Result<utils::Void> Update(ElapsedT Delta) = 0;

        virtual utils::Result<utils::Void> RenderScene() = 0;
        virtual utils::Result<utils::Void> RenderFrame() = 0;

        virtual utils::Result<utils::Void> CleanUp() = 0;

        virtual utils::Result<utils::Void> SetAppTitle(const std::string& NewTitle);

    protected:
        void MainLoop();

        bool bShouldQuit = false;
        SDL_Window* Window;
        std::string Title;
    };
} // namespace viewblaster
