#include <viewblaster/common/core/App.hpp>

namespace viewblaster {
    using namespace utils;
    void AbstractApp::Run()
    {
        AssertResult(EarlyInitialize());
        AssertResult(SetupSDL());
        AssertResult(SetupGfxAPI());
        AssertResult(LateInitialize());
        MainLoop();
        AssertResult(CleanUp());
        AssertResult(CleanUpGfxAPI());
    }

    void AbstractApp::Quit() { bShouldQuit = true; }

    void AbstractApp::MainLoop()
    {
        auto LastUpdateTime = std::chrono::steady_clock::now();

        while (!bShouldQuit)
        {
            // Process Events
            {
                SDL_Event evt;
                while (SDL_PollEvent(&evt))
                {
                    if (evt.type == SDL_QUIT)
                    {
                        Quit();
                    }
                }
            }

            {
                auto R = RenderScene();
                AssertResult(R);
            }
            {
                auto R = RenderFrame();
                AssertResult(R);
            }

            {
                auto Now       = std::chrono::steady_clock::now();
                auto DeltaTime = Now - LastUpdateTime;
                {
                    auto R = Update(DeltaTime);
                    AssertResult(R);
                }

                LastUpdateTime = Now;
            }
        }
    }

    utils::Result<utils::Void> AbstractApp::SetAppTitle(const std::string& NewTitle)
    {
        Title = NewTitle;
        if (Window)
            SDL_SetWindowTitle(Window, Title.c_str());
        return {utils::Void {}};
    }
} // namespace viewblaster
