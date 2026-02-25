#include "vk_enumerate_stuff.hpp"

BF_BEGIN_NAMESPACE

std::vector<const char *> Enumerate::InstanceExtensions(SDL_Window *wnd)
{
	/*std::vector<const char *> extensions
		{
			"VK_KHR_surface",
			"VK_KHR_win32_surface",
		};*/

	uint32_t count = 0;
	const char *const *extensions = SDL_Vulkan_GetInstanceExtensions(&count);

	std::vector<const char *> result(count);
	for (size_t i = 0; i < count; i++)
		result[i] = extensions[i];

	return result;
}

std::vector<VkLayerProperties> Enumerate::LayerProperties()
{
	uint32_t count = 0;
	vkEnumerateInstanceLayerProperties(&count, nullptr);

	std::vector<VkLayerProperties> result(count);
	vkEnumerateInstanceLayerProperties(&count, result.data());
	return result;
}

std::vector<VkPhysicalDevice> Enumerate::PhysicalDevices(VkInstance instance)
{
	uint32_t count = 0;
	vkEnumeratePhysicalDevices(instance, &count, nullptr);

	std::vector<VkPhysicalDevice> result(count);
	vkEnumeratePhysicalDevices(instance, &count, result.data());
	return result;
}

std::vector<VkQueueFamilyProperties> Enumerate::QueueFamilyProperties(VkPhysicalDevice phys_device)
{
	uint32_t count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(phys_device, &count, nullptr);

	std::vector<VkQueueFamilyProperties> result(count);
	vkGetPhysicalDeviceQueueFamilyProperties(phys_device, &count, result.data());
	return result;
}

std::vector<VkSurfaceFormatKHR> Enumerate::SurfaceFormats(VkPhysicalDevice phys_device, VkSurfaceKHR surface)
{
	uint32_t count = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(phys_device, surface, &count, nullptr);

	std::vector<VkSurfaceFormatKHR> result(count);
	vkGetPhysicalDeviceSurfaceFormatsKHR(phys_device, surface, &count, result.data());
	return result;
}

std::vector<VkPresentModeKHR> Enumerate::PresentModes(VkPhysicalDevice phys_device, VkSurfaceKHR surface)
{
	uint32_t count = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(phys_device, surface, &count, nullptr);

	std::vector<VkPresentModeKHR> result(count);
	vkGetPhysicalDeviceSurfacePresentModesKHR(phys_device, surface, &count, result.data());
	return result;
}

BF_END_NAMESPACE
