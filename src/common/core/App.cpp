#include <viewblaster/common/core/App.hpp>

namespace viewblaster {
    void AbstractApp::Run()
    {
        Initialize();
        MainLoop();
        CleanUp();
    }

    void AbstractApp::Quit()
    {
        bShouldQuit = true;
    }

    void AbstractApp::MainLoop()
    {
        auto LastUpdateTime = std::chrono::steady_clock::now();

        while (!bShouldQuit)
        {
            RenderScene();
            RenderFrame();

            {
                auto Now = std::chrono::steady_clock::now();
                auto DeltaTime = Now - LastUpdateTime;
                Update(DeltaTime);
                LastUpdateTime = Now;
            }
        }
    }
} // namespace viewblaster
