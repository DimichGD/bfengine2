#include "vk_internal.hpp"
#include "core/log.hpp"
#include "vk_enumerate_stuff.hpp"
#include "graphics/vulkan/vk_convert_enum.hpp"
#include <fmt/format.h>
#include <vector>
#include <string>
#include <stdexcept>

BF_BEGIN_NAMESPACE

void RenderDeviceVK::Internal::CreateInstance(SDL_Window *wnd, bool enable_debug_layers)
{
	const char *layer_name = "VK_LAYER_KHRONOS_validation";
	std::vector<const char *> extensions = Enumerate::InstanceExtensions(wnd);
	std::vector<const char *> layers;

	/*for (const VkLayerProperties &prop: Enumerate::LayerProperties())
	{
		Log() << prop.layerName << ":";

		uint32_t count = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
		std::vector<VkExtensionProperties> extensions(count);
		vkEnumerateInstanceExtensionProperties(nullptr, &count, extensions.data());

		for (auto &ext: extensions)
		{
			Log() << " --- " << ext.extensionName;
		}
	}*/

	if (enable_debug_layers)
	{
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		//extensions.push_back(VK_EXT_LAYER_SETTINGS_EXTENSION_NAME);
	}

	VkBool32 enable = VK_TRUE;
	const char *mute_ids[] = { "VUID-vkDestroyDevice-device-05137" }; // MessageID = 0x675dc32e
	const char *debug_actions[] = { "VK_DBG_LAYER_ACTION_LOG_MSG" };
	std::vector<VkLayerSettingEXT> settings
	{
		{ layer_name, "validate_core", VK_LAYER_SETTING_TYPE_BOOL32_EXT, 1, &enable },
		{ layer_name, "validate_sync", VK_LAYER_SETTING_TYPE_BOOL32_EXT, 1, &enable },
		{ layer_name, "thread_safety", VK_LAYER_SETTING_TYPE_BOOL32_EXT, 1, &enable },
		{ layer_name, "validate_best_practices", VK_LAYER_SETTING_TYPE_BOOL32_EXT, 1, &enable },
		{ layer_name, "message_id_filter", VK_LAYER_SETTING_TYPE_STRING_EXT, uint32_t(std::size(mute_ids)), mute_ids },
		{ layer_name, "debug_action", VK_LAYER_SETTING_TYPE_STRING_EXT, uint32_t(std::size(debug_actions)), debug_actions },
	};

	VkLayerSettingsCreateInfoEXT layer_settings_ci
	{
		.sType = VK_STRUCTURE_TYPE_LAYER_SETTINGS_CREATE_INFO_EXT,
		.pNext = nullptr,
		.settingCount = uint32_t(settings.size()),
		.pSettings = settings.data(),
	};

	if (enable_debug_layers)
	{
		for (const VkLayerProperties &prop: Enumerate::LayerProperties())
			if (std::string(prop.layerName) == layer_name)
				layers.push_back(layer_name);
	}

	VkApplicationInfo application_info
	{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = nullptr,
		.pApplicationName = nullptr,
		.applicationVersion = 0,
		.pEngineName = nullptr,
		.engineVersion = 0,
		.apiVersion = VK_API_VERSION_1_4
	};

	const VkInstanceCreateInfo instance_ci
	{
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = enable_debug_layers ? &layer_settings_ci : nullptr,
		.flags = 0,
		.pApplicationInfo = &application_info,
		.enabledLayerCount = uint32_t(layers.size()),
		.ppEnabledLayerNames = layers.data(),
		.enabledExtensionCount = uint32_t(extensions.size()),
		.ppEnabledExtensionNames = extensions.data(),
	};

	VkResult result = vkCreateInstance(&instance_ci, nullptr, &instance);
	if (result != VK_SUCCESS)	
	{
		Log() << result;
		throw std::runtime_error("vkCreateInstance failed");
	}

	SetDebugUtilsObjectName =
		reinterpret_cast<PFN_vkSetDebugUtilsObjectNameEXT>(vkGetInstanceProcAddr(instance, "vkSetDebugUtilsObjectNameEXT"));
}

void RenderDeviceVK::Internal::ChoosePhysicalDevice()
{
	for (const VkPhysicalDevice &tmp_device: Enumerate::PhysicalDevices(instance))
	{
		VkPhysicalDeviceProperties props;
		vkGetPhysicalDeviceProperties(tmp_device, &props);

		if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		{
			phys_device = tmp_device;
			break;
		}

		if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
		{
			phys_device = tmp_device;
		}
	}

	if (phys_device == VK_NULL_HANDLE)
		throw std::runtime_error("Physical device not found");

	vkGetPhysicalDeviceMemoryProperties(phys_device, &memory_properties);

	/*VkPhysicalDeviceDescriptorBufferPropertiesEXT descriptor_buffer_props {};
	descriptor_buffer_props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_PROPERTIES_EXT;

	VkPhysicalDeviceProperties2 props
	{
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
		.pNext = &descriptor_buffer_props,
		.properties = {},
	};
	vkGetPhysicalDeviceProperties2(phys_device, &props);

	Log() << descriptor_buffer_props.descriptorBufferOffsetAlignment;*/

	//Log() << props.properties.limits.minUniformBufferOffsetAlignment << props.properties.limits.minStorageBufferOffsetAlignment;
}

void RenderDeviceVK::Internal::CreateSurface(SDL_Window *wnd)
{
	if (!SDL_Vulkan_CreateSurface(wnd, instance, nullptr, &surface))
		throw std::runtime_error("vkCreateInstance failed");

	//SDL_Vulkan_GetDrawableSize(wnd, reinterpret_cast<int *>(&width), reinterpret_cast<int *>(&height));
	SDL_GetWindowSizeInPixels(wnd, reinterpret_cast<int *>(&width), reinterpret_cast<int *>(&height));

	VkSurfaceCapabilitiesKHR capabilities;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(phys_device, surface, &capabilities);
	// TODO: check usage flags

	/*for (auto &mode: Enumerate::PresentModes(phys_device, surface))
	{
		Log() << mode;
	}*/

	std::vector<VkSurfaceFormatKHR> formats = Enumerate::SurfaceFormats(phys_device, surface);
	auto pred = [](const VkSurfaceFormatKHR &format) -> bool
	{
		// TODO: manual srgb convert?
		return (format.format == VK_FORMAT_B8G8R8A8_SRGB /*|| format.format == VK_FORMAT_R8G8B8A8_SRGB*/);
		//return (format.format == VK_FORMAT_B8G8R8A8_UNORM || format.format == VK_FORMAT_R8G8B8A8_UNORM);
	};

	if (auto it = std::ranges::find_if(formats, pred); it != formats.end())
		swapchain_format = it->format;

	else
		throw std::runtime_error("Suitable swapchain format not found");
}

void RenderDeviceVK::Internal::CreateDevice()
{
	std::vector<VkQueueFamilyProperties> queue_family_props = Enumerate::QueueFamilyProperties(phys_device);
	for (size_t i = 0; i < queue_family_props.size(); i++)
	{
		if (queue_family_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			graphics_family_index = i;
			break;
		}
	}

	for (size_t i = 0; i < queue_family_props.size(); i++)
	{
		VkQueueFlags mask = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT;
		if (!(queue_family_props[i].queueFlags & (VK_QUEUE_VIDEO_DECODE_BIT_KHR | VK_QUEUE_VIDEO_ENCODE_BIT_KHR)))
			if ((queue_family_props[i].queueFlags & mask) == VK_QUEUE_TRANSFER_BIT)
				transfer_family_index = i;
	}

	float queue_priority = 1.0f;
	std::array<VkDeviceQueueCreateInfo, 2> device_queue_ci
	{
		VkDeviceQueueCreateInfo
		{
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.queueFamilyIndex = graphics_family_index,
			.queueCount = 1,
			.pQueuePriorities = &queue_priority
		},

		VkDeviceQueueCreateInfo
		{
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.queueFamilyIndex = transfer_family_index,
			.queueCount = 1,
			.pQueuePriorities = &queue_priority
		},
	};

	std::array device_extensions
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
		VK_KHR_PRESENT_ID_EXTENSION_NAME,
		VK_KHR_PRESENT_WAIT_EXTENSION_NAME,
		VK_EXT_EXTENDED_DYNAMIC_STATE_3_EXTENSION_NAME,
		VK_EXT_DESCRIPTOR_BUFFER_EXTENSION_NAME,
	};

	/*VkPhysicalDeviceGraphicsPipelineLibraryFeaturesEXT device_pipeline_library {};
	device_pipeline_library.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GRAPHICS_PIPELINE_LIBRARY_FEATURES_EXT;
	device_pipeline_library.graphicsPipelineLibrary = VK_TRUE;*/

	VkPhysicalDeviceDescriptorBufferFeaturesEXT decriptor_buffer_fratures
	{
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_FEATURES_EXT,
		.pNext = nullptr,
		.descriptorBuffer = VK_TRUE,
		.descriptorBufferCaptureReplay = VK_TRUE,
		.descriptorBufferImageLayoutIgnored = VK_FALSE,
		.descriptorBufferPushDescriptors = VK_FALSE,
	};

	VkPhysicalDevicePresentWaitFeaturesKHR present_wait_features
	{
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_WAIT_FEATURES_KHR,
		.pNext = &decriptor_buffer_fratures,
		.presentWait = VK_TRUE,
	};

	VkPhysicalDevicePresentIdFeaturesKHR present_id_features
	{
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_ID_FEATURES_KHR,
		.pNext = &present_wait_features,
		.presentId = VK_TRUE,
	};

	/*VkPhysicalDeviceDescriptorIndexingFeatures descriptor_indexing_features {};
	descriptor_indexing_features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES;
	descriptor_indexing_features.pNext = &device_pipeline_library;
	// descriptor_indexing_features.shaderSampledImageArrayNonUniformIndexing = VK_TRUE;
	// descriptor_indexing_features.runtimeDescriptorArray = VK_TRUE;
	// descriptor_indexing_features.descriptorBindingVariableDescriptorCount = VK_TRUE;
	descriptor_indexing_features.descriptorBindingPartiallyBound = VK_TRUE;*/

	VkPhysicalDeviceVulkan14Features device_features_1_4 {};
	device_features_1_4.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES;
	device_features_1_4.pNext = &present_id_features;
	device_features_1_4.hostImageCopy = VK_TRUE;

	VkPhysicalDeviceVulkan13Features device_features_1_3 {};
	device_features_1_3.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
	device_features_1_3.pNext = &device_features_1_4;
	device_features_1_3.dynamicRendering = VK_TRUE;
	device_features_1_3.synchronization2 = VK_TRUE;

	VkPhysicalDeviceVulkan12Features device_features_1_2 {};
	device_features_1_2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
	device_features_1_2.pNext = &device_features_1_3;
	device_features_1_2.timelineSemaphore = VK_TRUE;
	device_features_1_2.descriptorIndexing = VK_TRUE;
	device_features_1_2.runtimeDescriptorArray = VK_TRUE;
	device_features_1_2.descriptorBindingPartiallyBound = VK_TRUE;
	device_features_1_2.descriptorBindingSampledImageUpdateAfterBind = VK_TRUE;

	VkPhysicalDeviceFeatures2 phys_device_features {};
	phys_device_features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
	phys_device_features.pNext = &device_features_1_2;
	phys_device_features.features.sampleRateShading = VK_TRUE;
	//phys_device_features.features.samplerAnisotropy = VK_TRUE;
	//phys_device_features.features.shaderUniformBufferArrayDynamicIndexing = VK_TRUE;
	//phys_device_features.features.multiDrawIndirect = VK_TRUE;

	VkDeviceCreateInfo device_ci
	{
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = &phys_device_features,
		.flags = 0,
		.queueCreateInfoCount = uint32_t(device_queue_ci.size()),
		.pQueueCreateInfos = device_queue_ci.data(),
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = nullptr,
		.enabledExtensionCount = uint32_t(device_extensions.size()),
		.ppEnabledExtensionNames = device_extensions.data(),
		.pEnabledFeatures = nullptr,
	};

	VkResult result = vkCreateDevice(phys_device, &device_ci, nullptr, &device);
	if (result != VK_SUCCESS)
		throw std::runtime_error("vkCreateDevice error");

	vkGetDeviceQueue(device, graphics_family_index, 0, &graphics_queue);
	vkGetDeviceQueue(device, transfer_family_index, 0, &transfer_queue);

	WaitForPresentKHR =
		std::bit_cast<PFN_vkWaitForPresentKHR>(vkGetDeviceProcAddr(device, "vkWaitForPresentKHR"));

	if (!WaitForPresentKHR)
		throw std::runtime_error("vkWaitForPresentKHR not found"); // TODO: make it optional
}

void RenderDeviceVK::Internal::CreateSwapchain()
{
	uint32_t count;
	vkGetPhysicalDeviceSurfacePresentModesKHR(phys_device, surface, &count, nullptr);
	std::vector<VkPresentModeKHR> present_modes(count);
	vkGetPhysicalDeviceSurfacePresentModesKHR(phys_device, surface, &count, present_modes.data());
	//for (const VkPresentModeKHR &mode: present_modes)
	//	Log() << mode;
	// TODO: do something with this

	VkSwapchainCreateInfoKHR swapchain_ci =
	{
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.pNext = nullptr,
		.flags = 0,
		.surface = surface,
		.minImageCount = 3,
		.imageFormat = swapchain_format,
		.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
		.imageExtent = { width, height },
		.imageArrayLayers = 1,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = nullptr,
		.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = VK_PRESENT_MODE_FIFO_KHR, //VK_PRESENT_MODE_FIFO_KHR,
		.clipped = VK_TRUE,
		.oldSwapchain = swapchain,
	};

	VkResult result = vkCreateSwapchainKHR(device, &swapchain_ci, nullptr, &swapchain);
	if (result != VK_SUCCESS)
		throw std::runtime_error("vkCreateSwapchainKHR failed");


	vkGetSwapchainImagesKHR(device, swapchain, &count, nullptr);
	//Log() << count << "images";

	swapchain_resources.resize(count);

	std::vector<VkImage> swapchain_images(count);
	vkGetSwapchainImagesKHR(device, swapchain, &count, swapchain_images.data());

	for (uint32_t i = 0; i < count; i++)
	{
		swapchain_resources[i].texture.image = swapchain_images[i];
		SetObjectName(VK_OBJECT_TYPE_IMAGE, swapchain_resources[i].texture.image, fmt::format("Swapchain Image {}", i).c_str());
	}

	VkComponentMapping mapping =
	{
		.r = VK_COMPONENT_SWIZZLE_IDENTITY,
		.g = VK_COMPONENT_SWIZZLE_IDENTITY,
		.b = VK_COMPONENT_SWIZZLE_IDENTITY,
		.a = VK_COMPONENT_SWIZZLE_IDENTITY
	};

	for (uint32_t i = 0; i < swapchain_resources.size(); i++)
	{
		VkImageViewCreateInfo image_view_ci =
		{
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.image = swapchain_resources[i].texture.image,
			.viewType = VK_IMAGE_VIEW_TYPE_2D,
			.format = swapchain_format,
			.components = mapping,
			.subresourceRange = generic_subresource,
		};

		VkResult result = vkCreateImageView(device, &image_view_ci, nullptr, &swapchain_resources[i].texture.image_view);
		if (result != VK_SUCCESS)
			throw std::runtime_error("vkCreateImageView failed");
	}


	// ---------------- Depth buffer ---------------

	/*VkImageCreateInfo image_ci
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.imageType = VK_IMAGE_TYPE_2D,
		.format = vk::ConvertEnum(Texture::Format::D24),
		.extent = { width, height, 1 },
		.mipLevels = 1,
		.arrayLayers = 1,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.tiling = VK_IMAGE_TILING_OPTIMAL,
		.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = nullptr,
		.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
	};

	vkCreateImage(device, &image_ci, nullptr, &depth_image);
	SetObjectName(VK_OBJECT_TYPE_IMAGE, depth_image, "Depth Texture");

	VkMemoryRequirements memory_req;
	vkGetImageMemoryRequirements(device, depth_image, &memory_req);

	uint32_t memory_type_index = FindMemoryIndex(memory_req, MemoryType::DEVICE);

	VkMemoryAllocateInfo alloc_info
	{
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.pNext = nullptr,
		.allocationSize = memory_req.size,
		.memoryTypeIndex = memory_type_index,
	};

	vkAllocateMemory(device, &alloc_info, nullptr, &depth_memory);
	vkBindImageMemory(device, depth_image, depth_memory, 0);

	VkImageSubresourceRange depth_subresource
	{
		.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT,
		.baseMipLevel = 0,
		.levelCount = 1, // VK_REMAINING_MIP_LEVELS
		.baseArrayLayer = 0,
		.layerCount = 1, // VK_REMAINING_ARRAY_LAYERS
	};

	VkImageViewCreateInfo image_view_ci
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.image = depth_image,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = vk::ConvertEnum(Texture::Format::D24),
		.components = {},
		.subresourceRange = depth_subresource,
	};

	vkCreateImageView(device, &image_view_ci, nullptr, &depth_image_view);*/
}

uint32_t RenderDeviceVK::Internal::FindMemoryIndex(VkMemoryRequirements req, MemoryType type)
{
	std::array<VkMemoryPropertyFlags, 3> flags
	{
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
	};

	for (uint32_t i = 0; i < memory_properties.memoryTypeCount; i++)
	{
		if (req.memoryTypeBits & (1 << i))
		{
			VkMemoryPropertyFlags desired_flags = flags[std::to_underlying(type)];
			if ((memory_properties.memoryTypes[i].propertyFlags & desired_flags) == desired_flags)
				return i;
		}
	}

	throw std::runtime_error("Can't find memory type");
	return 0; // TODO: fallback to something
}

void RenderDeviceVK::Internal::SetObjectName(VkObjectType object_type, void *object_handle, const char *name)
{
	VkDebugUtilsObjectNameInfoEXT object_name
	{
		.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
		.pNext = nullptr,
		.objectType = object_type,
		.objectHandle = uint64_t(object_handle),
		.pObjectName = name,
	};

	if (SetDebugUtilsObjectName)
		SetDebugUtilsObjectName(device, &object_name);
}

BF_END_NAMESPACE
