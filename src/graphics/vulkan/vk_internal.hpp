#pragma once
#include "core/defines.hpp"
#include "core/log.hpp"
#include "graphics/vulkan/vk_convert_enum.hpp"
#include "graphics/vulkan/vk_render_device.hpp"
#include "utils/hash.hpp"
#include <SDL3/SDL_video.h>
#include <vulkan/vulkan.h>
#include <vector>

BF_BEGIN_NAMESPACE
BF_BEGIN_VK_NAMESPACE

struct Buffer
{
	VkBuffer buffer;
	uint32_t buffer_size;
	VkDeviceMemory memory;
	VkDeviceSize memory_size;
};

struct Texture
{
	VkImage image;
	VkImageView image_view;
	VkDeviceMemory memory;
	VkImageLayout layout;
};

/*struct ConstantRange
{
	VkShaderStageFlags stage_flags;
	uint32_t offset = 0;
	uint32_t size = 0;
};*/

struct Pipeline
{
	VkPipeline pipeline;
	VkPipelineLayout layout;
	std::vector<VkDescriptorSetLayout> decriptor_set_layouts;
	std::array<VkPushConstantRange, 6> constant_ranges {};
	std::vector<DescriptorSet> descriptors;
};

BF_END_VK_NAMESPACE

struct SwapchainResource
{
	//VkImage image = VK_NULL_HANDLE;
	//VkImageView image_view = VK_NULL_HANDLE;
	vk::Texture texture {};
	VkSemaphore render_semaphore = VK_NULL_HANDLE;
	VkFence fence = VK_NULL_HANDLE;

	/*VkFence acquire_fence = VK_NULL_HANDLE;
	VkFence present_fence = VK_NULL_HANDLE;
	VkSemaphore acquire_semaphore  = VK_NULL_HANDLE;
	VkSemaphore wait_semaphore = VK_NULL_HANDLE;*/
};

struct FrameResource
{
	VkFence fence = VK_NULL_HANDLE;
	VkSemaphore present_semaphore = VK_NULL_HANDLE;
	VkCommandBuffer command_buffer = VK_NULL_HANDLE;

	VkCommandPool command_pool = VK_NULL_HANDLE;
	uint64_t last_signaled_value = 0;

	//VkSemaphore render_semaphore = VK_NULL_HANDLE;
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
	std::vector<SwapchainResource> swapchain_resources;
	std::vector<FrameResource> frame_resources;
	VkSemaphore timeline_semaphore = VK_NULL_HANDLE;
	uint64_t present_id = 0;
	/*VkImage depth_image = VK_NULL_HANDLE;
	VkDeviceMemory depth_memory = VK_NULL_HANDLE;
	VkImageView depth_image_view = VK_NULL_HANDLE;*/
	//vk::Texture depth_texture {};
	//bf::Texture depth_texture_fffuuu {};
	VkClearColorValue clear_color;
	VkClearDepthStencilValue clear_depth_stencil;
	//VkSemaphore swapchain_semaphore = VK_NULL_HANDLE;
	//VkFence fence = VK_NULL_HANDLE;

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
	uint64_t frame_timeline_index = 0;

	/*uint32_t host_memory_type_index = 3;
	uint32_t device_memory_type_index = 1;
	uint32_t staging_memory_type_index = 5;*/
	VkPhysicalDeviceMemoryProperties memory_properties {};
	VkPhysicalDeviceProperties device_properties {};

	//VkBuffer staging_buffer = VK_NULL_HANDLE;
	//VkDeviceMemory staging_memory = VK_NULL_HANDLE;
	VkSampler linear_sampler = VK_NULL_HANDLE;

	VkCommandBuffer transfer_command_buffer = VK_NULL_HANDLE;
	VkCommandBuffer current_command_buffer = VK_NULL_HANDLE;

	PFN_vkSetDebugUtilsObjectNameEXT SetDebugUtilsObjectName = nullptr;
	PFN_vkWaitForPresentKHR WaitForPresentKHR = nullptr;

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

class DescriptorSetLayoutBuilder
{
public:
	DescriptorSetLayoutBuilder &AddBinding(uint32_t binding_index, VkDescriptorType type, VkShaderStageFlags stage_flags, uint32_t array_size = 1)
	{
		VkDescriptorSetLayoutBinding binding
		{
			.binding = binding_index,
			.descriptorType = type,
			.descriptorCount = array_size,
			.stageFlags = stage_flags,
			.pImmutableSamplers = nullptr,
		};

		bindings.push_back(binding);
		flags.push_back(array_size > 1 ? VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT : 0);

		return *this;
	}

	VkDescriptorSetLayout Build(VkDevice device, const std::map<uint32_t, VkDescriptorSetLayout> &global_layouts)
	{
		uint32_t set_hash = bindings.size();
		for (auto &binding: bindings)
		{
			set_hash = hash(set_hash, binding.binding);
			set_hash = hash(set_hash, binding.descriptorType);
			set_hash = hash(set_hash, binding.descriptorCount);
			set_hash = hash(set_hash, binding.stageFlags);
		}

		auto it = global_layouts.find(set_hash);
		if (it != global_layouts.end())
		{
			Info() << "Found layout in cache";
			return it->second;
		}

		VkDescriptorSetLayoutBindingFlagsCreateInfo flags_ci
		{
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
			.pNext = nullptr,
			.bindingCount = uint32_t(flags.size()),
			.pBindingFlags = flags.data(),
		};

		VkDescriptorSetLayoutCreateInfo descriptor_set_layout_ci
		{
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
			.pNext = &flags_ci,
			.flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT,
			.bindingCount = uint32_t(bindings.size()),
			.pBindings = bindings.data(),
		};

		VkDescriptorSetLayout descriptor_set_layout = VK_NULL_HANDLE;
		vkCreateDescriptorSetLayout(device, &descriptor_set_layout_ci, nullptr, &descriptor_set_layout);

		return descriptor_set_layout;
	}

private:
	std::vector<VkDescriptorSetLayoutBinding> bindings;
	std::vector<VkDescriptorBindingFlags> flags;
};


BF_END_NAMESPACE
