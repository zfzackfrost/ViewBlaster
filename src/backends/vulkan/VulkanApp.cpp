#include <viewblaster/backends/vulkan/VulkanApp.hpp>

#include <vulkan/vulkan.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <fmt/core.h>

namespace viewblaster {
    using namespace utils;
    Result<Void> VulkanApp::Initialize() { return {Void {}}; }

    Result<Void> VulkanApp::SetupSDL()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
        {
            return {fmt::format(FMT_STRING("Unable to initialize SDL: `{}`"), SDL_GetError()), E_MessageLevel::Error};
        }

        Window = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);

        return {Void {}};
    }
    Result<Void> VulkanApp::SetupGfxAPI() { return {Void {}}; }

    Result<Void> VulkanApp::Update(ElapsedT Delta) { return {Void {}}; }

    Result<Void> VulkanApp::RenderScene() { return {Void {}}; }
    Result<Void> VulkanApp::RenderFrame() { return {Void {}}; }

    Result<Void> VulkanApp::CleanUp() { return {Void {}}; }


} // namespace viewblaster
