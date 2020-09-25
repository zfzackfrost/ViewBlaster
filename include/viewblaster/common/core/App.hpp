/**
 * @file App.hpp
 * @author Zachary Frost
 * @copyright See repository LICENSE file
 * @brief `AbstractApp` class.
 */

#pragma once

#include <chrono>

namespace viewblaster {
    class AbstractApp
    {
    public:

        void Run();

        void Quit();

    protected:

        virtual void Initialize() = 0;

        using UpdateDeltaT = std::chrono::steady_clock::duration;
        virtual void Update(UpdateDeltaT Delta) = 0;

        virtual void RenderScene() = 0;
        virtual void RenderFrame() = 0;

        virtual void CleanUp() = 0;

    private:
        void MainLoop();

        bool bShouldQuit = false;
    };
} // namespace viewblaster
