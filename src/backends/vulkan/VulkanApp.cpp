#include <viewblaster/backends/vulkan/VulkanApp.hpp>

#include <viewblaster/backends/vulkan/vk.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <fmt/core.h>

namespace viewblaster {
    using namespace utils;
    Result<Void> VulkanApp::EarlyInitialize() { return {Void {}}; }
    Result<Void> VulkanApp::LateInitialize() { return {Void {}}; }

    Result<Void> VulkanApp::SetupSDL()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
        {
            return {fmt::format(FMT_STRING("Unable to initialize SDL: `{}`"), SDL_GetError()), E_MessageLevel::Error};
        }

        Window = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);

        return {Void {}};
    }
    Result<Void> VulkanApp::SetupGfxAPI()
    {
        uint32_t SdlExtCount;
        SDL_Vulkan_GetInstanceExtensions(Window, &SdlExtCount, nullptr);
        std::vector<const char*> InstanceExts(SdlExtCount);
        SDL_Vulkan_GetInstanceExtensions(Window, &SdlExtCount, InstanceExts.data());

        vk::ApplicationInfo AppInfo{};
        AppInfo.pEngineName = "ViewBlaster";
        AppInfo.pApplicationName = Title.c_str();
        AppInfo.apiVersion = VK_API_VERSION_1_0;
        AppInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
        AppInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);

        vk::InstanceCreateInfo InstanceInfo{};
        InstanceInfo.pApplicationInfo = &AppInfo;
        InstanceInfo.enabledExtensionCount = InstanceExts.size();
        InstanceInfo.ppEnabledExtensionNames = InstanceExts.data();

        auto InstRes = vk::createInstance(InstanceInfo);

        if (InstRes.result != vk::Result::eSuccess)
            return {"Vulkan: Failed to create instance", E_MessageLevel::Error};
        else
            InstanceVk = InstRes.value;

        return {Void {}};
    }

    Result<Void> VulkanApp::Update(ElapsedT Delta) { return {Void {}}; }

    Result<Void> VulkanApp::RenderScene() { return {Void {}}; }
    Result<Void> VulkanApp::RenderFrame() { return {Void {}}; }

    Result<Void> VulkanApp::CleanUp() { return {Void {}}; }


} // namespace viewblaster
