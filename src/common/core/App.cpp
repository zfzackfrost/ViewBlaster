#include <viewblaster/common/core/App.hpp>

namespace viewblaster {
    void AbstractApp::Run()
    {
        SetupSDL();
        SetupGfxAPI();
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
            // Process Events
            {
                SDL_Event evt;
                while(SDL_PollEvent(&evt))
                {
                    if (evt.type == SDL_QUIT)
                    {
                        Quit();
                    }
                }
            }

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


    utils::Result<utils::Void> AbstractApp::SetAppTitle(const std::string& NewTitle)
    {
        Title = NewTitle;
        if (Window)
            SDL_SetWindowTitle(Window, Title.c_str());
        return {utils::Void{}};
    }
} // namespace viewblaster
