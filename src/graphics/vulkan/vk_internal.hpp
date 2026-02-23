#pragma once
#include "core/defines.hpp"
#include "graphics/vulkan/render_device_vk.hpp"
#include <SDL3/SDL_video.h>
#include <vulkan/vulkan.h>
#include <vector>

BF_BEGIN_NAMESPACE
BF_BEGIN_VK_NAMESPACE

struct Buffer
{
	VkBuffer buffer;
	VkDeviceMemory memory;
};

struct Texture
{
	VkImage image;
	VkImageView image_view;
	VkDeviceMemory memory;
	VkImageLayout layout;
};

struct Pipeline
{
	VkPipeline pipeline;
	VkPipelineLayout layout;
	std::vector<VkDescriptorSetLayout> decriptor_set_layouts;
	//VkDescriptorSetLayout decriptor_set_layouts[3] { VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE };
};

BF_END_VK_NAMESPACE

struct SwapchainResource
{
	//VkImage image = VK_NULL_HANDLE;
	//VkImageView image_view = VK_NULL_HANDLE;
	vk::Texture texture {};
	VkSemaphore render_semaphore = VK_NULL_HANDLE;
	VkCommandBuffer command_buffer = VK_NULL_HANDLE;
};

enum class MemoryType
{
	HOST,
	DEVICE,
	STAGING,
};

struct Memory
{
	uint32_t host_type_index = 0;
	uint32_t device_type_index = 0;
	uint32_t staging_type_index = 0;
};

struct Queue
{
	uint32_t graphics_family_index = 0;
	uint32_t transfer_family_index = 0;

	VkQueue graphics = VK_NULL_HANDLE;
	VkQueue transfer = VK_NULL_HANDLE;
};

struct RenderDeviceVK::Internal
{
	VkInstance instance = VK_NULL_HANDLE;
	VkSurfaceKHR surface = VK_NULL_HANDLE;
	VkPhysicalDevice phys_device = VK_NULL_HANDLE;
	VkDevice device = VK_NULL_HANDLE;
	VkPipelineCache pipeline_cache = VK_NULL_HANDLE;

	uint32_t graphics_family_index = 0;
	uint32_t transfer_family_index = 0;
	VkQueue graphics_queue = VK_NULL_HANDLE;
	VkQueue transfer_queue = VK_NULL_HANDLE;

	uint32_t width = 0;
	uint32_t height = 0;

	VkSwapchainKHR swapchain = VK_NULL_HANDLE;
	VkFormat swapchain_format = VK_FORMAT_UNDEFINED;
	std::vector<SwapchainResource> frames;
	/*VkImage depth_image = VK_NULL_HANDLE;
	VkDeviceMemory depth_memory = VK_NULL_HANDLE;
	VkImageView depth_image_view = VK_NULL_HANDLE;*/
	//vk::Texture depth_texture {};
	//bf::Texture depth_texture_fffuuu {};
	VkClearColorValue clear_color;
	VkClearDepthStencilValue clear_depth_stencil;
	VkSemaphore swapchain_semaphore = VK_NULL_HANDLE;
	VkFence fence = VK_NULL_HANDLE;

	VkImageSubresourceRange generic_subresource
	{
		.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
		.baseMipLevel = 0,
		.levelCount = 1, // VK_REMAINING_MIP_LEVELS
		.baseArrayLayer = 0,
		.layerCount = 1, // VK_REMAINING_ARRAY_LAYERS
	};

	VkCommandPool graphics_command_pool = VK_NULL_HANDLE;
	VkCommandPool transfer_command_pool = VK_NULL_HANDLE;
	uint32_t frame_index = 0;
	uint32_t image_index = 0;

	/*uint32_t host_memory_type_index = 3;
	uint32_t device_memory_type_index = 1;
	uint32_t staging_memory_type_index = 5;*/
	VkPhysicalDeviceMemoryProperties memory_properties {};

	VkBuffer staging_buffer = VK_NULL_HANDLE;
	VkDeviceMemory staging_memory = VK_NULL_HANDLE;
	VkSampler linear_sampler = VK_NULL_HANDLE;

	VkCommandBuffer transfer_command_buffer = VK_NULL_HANDLE;
	VkCommandBuffer current_command_buffer = VK_NULL_HANDLE;

	PFN_vkSetDebugUtilsObjectNameEXT SetDebugUtilsObjectName = nullptr;

	void CreateInstance(SDL_Window *wnd, bool enable_debug_layers);
	void ChoosePhysicalDevice();
	void CreateSurface(SDL_Window *wnd);
	void CreateDevice();
	void CreateSwapchain();

	//

	uint32_t FindMemoryIndex(VkMemoryRequirements req, MemoryType type);

	//

	void SetObjectName(VkObjectType object_type, void *object_handle, const char *name);
};


BF_END_NAMESPACE
