#pragma once
#include "core/defines.hpp"
#include <vulkan/vulkan.h>
#include <SDL3/SDL_vulkan.h>
#include <vector>

BF_BEGIN_NAMESPACE

struct Enumerate
{
	static std::vector<const char *>             InstanceExtensions(SDL_Window *wnd);
	static std::vector<VkLayerProperties>        LayerProperties();
	static std::vector<VkPhysicalDevice>         PhysicalDevices(VkInstance instance);
	static std::vector<VkQueueFamilyProperties>  QueueFamilyProperties(VkPhysicalDevice phys_device);
	static std::vector<VkSurfaceFormatKHR>       SurfaceFormats(VkPhysicalDevice phys_device, VkSurfaceKHR surface);
	static std::vector<VkPresentModeKHR>         PresentModes(VkPhysicalDevice phys_device, VkSurfaceKHR surface);
};

BF_END_NAMESPACE


