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
            return {fmt::format(FMT_STRING("Unable to initialize SDL: `{}`"), SDL_GetError()),
                    E_MessageLevel::Error};
        }

        Window = SDL_CreateWindow(Title.c_str(),
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  800,
                                  600,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);
        if (!Window)
        {
            return {"SDL2: Failed to create window", E_MessageLevel::Error};
        }

        return {Void {}, "SDL2: Initiaized", E_MessageLevel::Success};
    }
    Result<Void> VulkanApp::SetupGfxAPI()
    {
        VIEW_BLASTER_RETURN_IF_ERR(CreateInstanceVk());
        VIEW_BLASTER_RETURN_IF_ERR(PickPhysicalDeviceVk());
        
        return {Void{}};
    }

    Result<Void> VulkanApp::Update(ElapsedT Delta) { return {Void {}}; }

    Result<Void> VulkanApp::RenderScene() { return {Void {}}; }
    Result<Void> VulkanApp::RenderFrame() { return {Void {}}; }

    Result<Void> VulkanApp::CleanUp() { return {Void {}}; }

    Result<Void> VulkanApp::CleanUpGfxAPI()
    {
        StateVk.Instance.destroy();
        return {Void {}};
    }

    void VulkanApp::MainLoop() 
    {
        AbstractApp::MainLoop();
    }

    ///////////////////////////////////////////////////////////////////////
    //                          Vulkan Methods                           //
    ///////////////////////////////////////////////////////////////////////
    
    Result<Void> VulkanApp::CreateInstanceVk()
    {
        uint32_t SdlExtCount;
        SDL_Vulkan_GetInstanceExtensions(Window, &SdlExtCount, nullptr);
        std::vector<const char*> InstanceExts(SdlExtCount);
        SDL_Vulkan_GetInstanceExtensions(Window, &SdlExtCount, InstanceExts.data());

        vk::ApplicationInfo AppInfo {};
        AppInfo.pEngineName        = "ViewBlaster";
        AppInfo.pApplicationName   = Title.c_str();
        AppInfo.apiVersion         = VK_API_VERSION_1_0;
        AppInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
        AppInfo.engineVersion      = VK_MAKE_VERSION(0, 1, 0);

        vk::InstanceCreateInfo InstanceInfo {};
        InstanceInfo.pApplicationInfo        = &AppInfo;
        InstanceInfo.enabledExtensionCount   = InstanceExts.size();
        InstanceInfo.ppEnabledExtensionNames = InstanceExts.data();

        auto InstRes = vk::createInstance(InstanceInfo);

        if (InstRes.result != vk::Result::eSuccess)
            return {"Vulkan: Failed to create instance", E_MessageLevel::Error};
        else
            StateVk.Instance = InstRes.value;

        return {Void {}, "Vulkan: Created instance", E_MessageLevel::Success};
    }

    Result<Void> VulkanApp::PickPhysicalDeviceVk()
    {
        auto RVk_Devices = StateVk.Instance.enumeratePhysicalDevices();
        if (RVk_Devices.result != vk::Result::eSuccess || RVk_Devices.value.empty())
            return {"Vulkan: Failed to find GPUs with Vulkan support", E_MessageLevel::Error};
        auto Devices = RVk_Devices.value;

        for (const auto& D : Devices)
        {
            auto R_Suitable = IsDeviceSuitableVk(D);
            VIEW_BLASTER_RETURN_IF_ERR(R_Suitable);
            bool Suitable = R_Suitable.Value();
            if (Suitable)
            {
                StateVk.PhysicalDevice = D;
                break;
            }
        }
        if (!StateVk.PhysicalDevice)
        {
            return {"Vulkan: Failed to find suitable GPU", E_MessageLevel::Error};
        }
        else
        {
            auto Props = StateVk.PhysicalDevice.getProperties();
            return {Void{}, fmt::format(FMT_STRING("Vulkan: Picked physical device, `{}`"), Props.deviceName.data()), E_MessageLevel::Debug};
        }
    }

    Result<bool> VulkanApp::IsDeviceSuitableVk(vk::PhysicalDevice Device)
    {
        return {true};
    }

} // namespace viewblaster
