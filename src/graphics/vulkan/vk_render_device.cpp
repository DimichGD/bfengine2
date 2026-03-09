#include "core/log.hpp"
#include "graphics/render_doc.hpp"
#include "graphics/vulkan/vk_internal.hpp"
#include "graphics/vulkan/vk_render_device.hpp"
#include "graphics/vulkan/vk_convert_enum.hpp"
#include "graphics/vulkan/vk_shader_builder.hpp"
#include "graphics/vulkan/vk_shader_reflection.hpp"
#include "graphics/vulkan/vk_pipeline_builder.hpp"
#include "io/file.hpp"
#include "utils/lexer.hpp"
#include <SDL3/SDL_timer.h>
#include <fmt/format.h>
#include <glm/gtc/type_ptr.hpp>
//#include <spirv_cross/spirv_cross_c.h>
#include <processthreadsapi.h>
#include <shaderc/shaderc.h>
#include <cassert>
#include <map>

BF_BEGIN_NAMESPACE

BF_BEGIN_VK_NAMESPACE
/*struct Shader
{
	std::vector<uint32_t> spirv;
	bf::Shader::Type type;
	VkPipelineLayout layout;
};*/
BF_END_VK_NAMESPACE

struct RenderDeviceVK::Storage
{
	std::vector<VkShaderModule> shader_modules;
	std::vector<vk::Pipeline> pipelines;
	vk::Pipeline current_pipeline;
	//VkPipeline pipeline;
	//VkPipelineLayout pipeline_layout;
	VkDescriptorPool descriptor_pool;

	//std::vector<VkPipelineLayout> pipeline_layouts;
	std::vector<VkDescriptorPool> descriptor_pools;
	std::vector<VkDescriptorSet> descriptor_sets;
	std::map<uint32_t, VkDescriptorSetLayout> descriptor_set_layouts;

	std::vector<vk::Buffer> buffers;
	std::vector<vk::Texture> textures;
	std::vector<Framebuffer> framebuffers;

	//std::map<uint32_t, std::vector<Descriptor2>> shader_reflection;
	std::map<uint32_t, ShaderReflectionData> shader_reflection;
};


RenderDeviceVK::RenderDeviceVK(Config *config, FileSystem *fs)
{
	this->config = config;
	this->fs = fs;
	vk = new Internal;
	store = new Storage;
}

RenderDeviceVK::~RenderDeviceVK()
{
	delete store;
	delete vk;
}


bool RenderDeviceVK::Create(SDL_Window *window_handle)
{
	vk->CreateInstance(window_handle, true); //!IsRenderDocAttached());
	vk->ChoosePhysicalDevice();
	vk->CreateSurface(window_handle);
	vk->CreateDevice();
	vk->CreateSwapchain();

/*	for (uint32_t i = 0; i < vk->frames.size(); i++)
		swapchain_image_prev_layouts.push_back(ImageLayout::UNDEFINED);

	TextureDesc depth_texture_desc
	{
		.width = vk->width,
		.height = vk->height,
		.format = Texture::Format::D24S8,
		.usage = Texture::Usage::DEPTH_ATTACHMENT | Texture::Usage::SHADER_READ,
		.levels = 1,
		.pixels = nullptr,
		.generate_mipmaps = false,
	};
	Texture depth_texture_handle = CreateTexture("Backbuffer Depth Texture", depth_texture_desc);
	//vk->depth_texture = store->textures.at(depth_texture_handle.handle);
	vk->depth_texture_fffuuu = depth_texture_handle;*/

	VkPhysicalDeviceProperties props;
	vkGetPhysicalDeviceProperties(vk->phys_device, &props);
	//Log() << props.limits.maxViewportDimensions[0] << props.limits.maxViewportDimensions[1];
	//Log() << props.limits.minUniformBufferOffsetAlignment;


	vk->frame_resources.resize(2);

	VkSemaphoreTypeCreateInfoKHR semaphore_type_ci
	{
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO_KHR,
		.pNext = nullptr,
		.semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
		.initialValue = 0,
	};

	VkSemaphoreCreateInfo semaphore_ci
	{
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		.pNext = &semaphore_type_ci,
		.flags = 0,
	};

	vkCreateSemaphore(vk->device, &semaphore_ci, nullptr, &vk->timeline_semaphore);


	VkCommandPoolCreateInfo command_pool_ci
	{
		.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.pNext = nullptr,
		.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
		.queueFamilyIndex = vk->graphics_family_index,
	};

	for (uint32_t i = 0; i < vk->frame_resources.size(); i++)
	{
		vkCreateCommandPool(vk->device, &command_pool_ci, nullptr, &vk->frame_resources[i].command_pool);
		vk->SetObjectName(VK_OBJECT_TYPE_COMMAND_POOL, vk->frame_resources[i].command_pool,
						  fmt::format("Graphics Command Pool {}", i).c_str());

		VkCommandBufferAllocateInfo alloc_info
		{
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
			.pNext = nullptr,
			.commandPool = vk->frame_resources[i].command_pool,
			.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
			.commandBufferCount = 1,
		};

		vkAllocateCommandBuffers(vk->device, &alloc_info, &vk->frame_resources[i].command_buffer);
		vk->SetObjectName(VK_OBJECT_TYPE_COMMAND_BUFFER, vk->frame_resources[i].command_buffer,
						  fmt::format("Graphics Command Buffer {}", i).c_str());

		VkSemaphoreCreateInfo semaphore_ci
		{
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
		};

		vkCreateSemaphore(vk->device, &semaphore_ci, nullptr, &vk->frame_resources[i].present_semaphore);
		vk->SetObjectName(VK_OBJECT_TYPE_SEMAPHORE, vk->frame_resources[i].present_semaphore,
						  fmt::format("Present Semaphore {}", i).c_str());

		VkFenceCreateInfo fence_ci
		{
			.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
			.pNext = nullptr,
			.flags = VK_FENCE_CREATE_SIGNALED_BIT,
		};

		vkCreateFence(vk->device, &fence_ci, nullptr, &vk->frame_resources[i].fence);
		vk->SetObjectName(VK_OBJECT_TYPE_FENCE, vk->frame_resources[i].fence,
						  fmt::format("Fence {}", i).c_str());

		// new stuff

		vk->frame_resources[i].last_signaled_value = i;

		/*vkCreateSemaphore(vk->device, &semaphore_ci, nullptr, &vk->frame_resources[i].render_semaphore);
		vk->SetObjectName(VK_OBJECT_TYPE_SEMAPHORE, vk->frame_resources[i].render_semaphore,
						  fmt::format("new render_semaphore {}", i).c_str());*/
	};

	for (uint32_t i = 0; i < vk->swapchain_resources.size(); i++)
	{
		VkSemaphoreCreateInfo semaphore_ci
		{
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
		};

		vkCreateSemaphore(vk->device, &semaphore_ci, nullptr, &vk->swapchain_resources[i].render_semaphore);
		vk->SetObjectName(VK_OBJECT_TYPE_SEMAPHORE, vk->swapchain_resources[i].render_semaphore,
						  fmt::format("Render Semaphore {}", i).c_str());

		// new stuff

		/*vkCreateSemaphore(vk->device, &semaphore_ci, nullptr, &vk->swapchain_resources[i].acquire_semaphore);
		vk->SetObjectName(VK_OBJECT_TYPE_SEMAPHORE, vk->swapchain_resources[i].acquire_semaphore,
						  fmt::format("new acquire_semaphore {}", i).c_str());

		vkCreateSemaphore(vk->device, &semaphore_ci, nullptr, &vk->swapchain_resources[i].wait_semaphore);
		vk->SetObjectName(VK_OBJECT_TYPE_SEMAPHORE, vk->swapchain_resources[i].wait_semaphore,
						  fmt::format("new wait_semaphore {}", i).c_str());

		VkFenceCreateInfo fence_ci
		{
			.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
			.pNext = nullptr,
			.flags = VK_FENCE_CREATE_SIGNALED_BIT,
		};

		vkCreateFence(vk->device, &fence_ci, nullptr, &vk->swapchain_resources[i].acquire_fence);
		vk->SetObjectName(VK_OBJECT_TYPE_FENCE, vk->swapchain_resources[i].acquire_fence,
						  fmt::format("new acquire_fence {}", i).c_str());

		vkCreateFence(vk->device, &fence_ci, nullptr, &vk->swapchain_resources[i].present_fence);
		vk->SetObjectName(VK_OBJECT_TYPE_FENCE, vk->swapchain_resources[i].present_fence,
						  fmt::format("new present_fence {}", i).c_str());*/
	}

	vk->current_command_buffer = vk->frame_resources[vk->frame_index].command_buffer;

	/*poolInfo.queueFamilyIndex = vk->transfer_family_index;
	vkCreateCommandPool(vk->device, &poolInfo, nullptr, &vk->transfer_command_pool);

	allocInfo.commandPool = vk->transfer_command_pool;
	vkAllocateCommandBuffers(vk->device, &allocInfo, &vk->transfer_command_buffer);
	vk->SetObjectName(VK_OBJECT_TYPE_COMMAND_BUFFER, vk->transfer_command_buffer, "Transfer Command Buffer");*/


	std::vector<VkDescriptorPoolSize> pool_sizes
	{
		{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 100 },
		{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 100 },
		{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
	};

	VkDescriptorPoolCreateInfo descritor_pool_ci
	{
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
		.pNext = nullptr,
		.flags = VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT,
		.maxSets = 100,
		.poolSizeCount = uint32_t(pool_sizes.size()),
		.pPoolSizes = pool_sizes.data(),
	};

	vkCreateDescriptorPool(vk->device, &descritor_pool_ci, nullptr, &store->descriptor_pool);


	GPUBuffer staging = CreateBuffer(GPUBuffer::STAGING, 16 * 1024 * 1024);
	vk->staging_buffer = store->buffers[staging.handle].buffer;
	vk->staging_memory = store->buffers[staging.handle].memory;

	VkSamplerCreateInfo sampler_ci
	{
		.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.magFilter = VK_FILTER_LINEAR,
		.minFilter = VK_FILTER_LINEAR,
		.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
		.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.mipLodBias = 0.0f,
		.anisotropyEnable = VK_FALSE,
		.maxAnisotropy = 1.0f,
		.compareEnable = VK_FALSE,
		.compareOp = VK_COMPARE_OP_ALWAYS,
		.minLod = 0.0f,
		.maxLod = VK_LOD_CLAMP_NONE,
		.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
		.unnormalizedCoordinates = VK_FALSE,
	};

	vkCreateSampler(vk->device, &sampler_ci, nullptr, &vk->linear_sampler);

	vk->clear_color = {{ 0.0f, 0.0f, 0.0f, 1.0f }};
	vk->clear_depth_stencil = { 1.0f, 0 };

	std::vector<char> cache;
	/*File cache_file("pipelines.bin");
	if (cache_file.Open())
		cache = cache_file.Read();*/

	VkPipelineCacheCreateInfo pipeline_cache_ci
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.initialDataSize = cache.size(),
		.pInitialData = cache.data(),
	};

	vkCreatePipelineCache(vk->device, &pipeline_cache_ci, nullptr, &vk->pipeline_cache);

	/*vkAcquireNextImageKHR(vk->device, vk->swapchain, UINT64_MAX,
											vk->frame_resources[vk->frame_index].present_semaphore,
											VK_NULL_HANDLE, &vk->image_index);*/

	return true;
}

void RenderDeviceVK::Destroy()
{
	vkDeviceWaitIdle(vk->device);

	/*size_t cache_size = 0;
	vkGetPipelineCacheData(vk->device, vk->pipeline_cache, &cache_size, nullptr);
	std::vector<char> cache(cache_size);
	vkGetPipelineCacheData(vk->device, vk->pipeline_cache, &cache_size, cache.data());

	{
		File cache_file("pipelines.bin");
		if (cache_file.Open(File::Access::WRITE))
			cache_file.Write(cache.data(), cache_size);
	}*/

	vkDestroyPipelineCache(vk->device, vk->pipeline_cache, nullptr);

	for (auto handle: store->buffers)
	{
		vkDestroyBuffer(vk->device, handle.buffer, nullptr);
		vkFreeMemory(vk->device, handle.memory, nullptr);
	}

	for (auto handle: store->textures)
	{
		vkDestroyImageView(vk->device, handle.image_view, nullptr);
		vkDestroyImage(vk->device, handle.image, nullptr);
		vkFreeMemory(vk->device, handle.memory, nullptr);
	}

	vkDestroySampler(vk->device, vk->linear_sampler, nullptr);

	//vkDestroyBuffer(vk->device, vk->staging_buffer, nullptr);
	//vkFreeMemory(vk->device, vk->staging_memory, nullptr);

	vkDestroyCommandPool(vk->device, vk->graphics_command_pool, nullptr);
	vkDestroyCommandPool(vk->device, vk->transfer_command_pool, nullptr);

	for (uint32_t i = 0; i < vk->swapchain_resources.size(); i++)
	{
		//vkDestroySemaphore(vk->device, vk->frames[i].swapchain_semaphore, nullptr);
		vkDestroySemaphore(vk->device, vk->swapchain_resources[i].render_semaphore, nullptr);
		//vkDestroyFence(vk->device, vk->frames[i].fence, nullptr);
		vkDestroyImageView(vk->device, vk->swapchain_resources[i].texture.image_view, nullptr);
	}


	//vkDestroySemaphore(vk->device, vk->swapchain_semaphore, nullptr);
	//vkDestroyFence(vk->device, vk->fence, nullptr);

	for (auto shader: store->shader_modules)
		vkDestroyShaderModule(vk->device, shader, nullptr);

	vkDestroyDescriptorPool(vk->device, store->descriptor_pool, nullptr);

	for (auto &decriptor_set_layout: store->descriptor_set_layouts)
		vkDestroyDescriptorSetLayout(vk->device, decriptor_set_layout.second, nullptr);

	for (auto pipeline: store->pipelines)
	{
		vkDestroyPipeline(vk->device, pipeline.pipeline, nullptr);
		vkDestroyPipelineLayout(vk->device, pipeline.layout, nullptr);
	}

	vkDestroySwapchainKHR(vk->device, vk->swapchain, nullptr);
	vkDestroyDevice(vk->device, nullptr);
	vkDestroySurfaceKHR(vk->instance, vk->surface, nullptr);
	vkDestroyInstance(vk->instance, nullptr);
}


Shader RenderDeviceVK::LoadShader(Shader::Type type, const std::string &name)
{
	std::string suffix;
	switch (type)
	{
		case Shader::Type::VERTEX:   suffix = "_vert"; break;
		case Shader::Type::FRAGMENT: suffix = "_frag"; break;
		case Shader::Type::GEOMETRY: suffix = "_geom"; break;
		case Shader::Type::COMPUTE:  suffix = "_comp"; break;
	}

	//std::string temp_filename = fs->GetDataPath() + "shaders/" + name + suffix;
	// TODO: Make sure directory cache exists

	std::string temp_name = name;
	std::replace(temp_name.begin(), temp_name.end(), '/', '_');

	File binary_file(fs->GetDataPath() + "shaders/cache/" + temp_name + suffix + ".spv"); // TODO: merge strings func
	File source_file(fs->GetDataPath() + "shaders/" + name + suffix + ".glsl");

	std::vector<uint32_t> binary;

	if (binary_file.Open())
	{
		if (!source_file.Open()) // FIXME: what to do if source is not available?
			return {};

		if (source_file.LastWriteTime() > binary_file.LastWriteTime())
		{
			Log() << "Binary is outdated";
			// recompile

			auto source = source_file.Read();
			binary = vk::CompileShader(name, source);
			if (!binary_file.Open(File::Access::WRITE))
				return {};

			binary_file.Write(binary.data(), binary.size() * sizeof(uint32_t));
		}
		else
		{
			binary.resize(binary_file.Size() / sizeof(uint32_t));
			binary_file.Read(binary.data(), binary_file.Size());
		}
		//Log() << "Found compiled shader";
	}
	else
	{
		if (source_file.Open())
		{
			//Log() << "Found shader source";
			auto source = source_file.Read();
			binary = vk::CompileShader(name, source);
			if (!binary_file.Open(File::Access::WRITE))
				return {};

			binary_file.Write(binary.data(), binary.size() * sizeof(uint32_t));
		}
		else
		{
			Error() << "Shader" << name + suffix << "not found";
			return {};
		}
	}

	ShaderReflectionData reflection_data = vk::GetShaderReflection(name, type, binary.data(), binary.size());

	VkShaderModuleCreateInfo shader_ci
	{
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.codeSize = binary.size() * sizeof(uint32_t),
		.pCode = binary.data(),
	};

	VkShaderModule module;
	VkResult result = vkCreateShaderModule(vk->device, &shader_ci, nullptr, &module);
	if (result != VK_SUCCESS)
	{
		Log() << "vkCreateShaderModule failed";
		return {};
	}

	vk->SetObjectName(VK_OBJECT_TYPE_SHADER_MODULE, module, name.c_str());

	store->shader_modules.push_back(module);
	store->shader_reflection[store->shader_modules.size() - 1] = std::move(reflection_data);
	return Shader(store->shader_modules.size() - 1, type);
}

Shader RenderDeviceVK::LoadShader(const std::string &name, const ShaderDesc &desc)
{
	Log() << "Create shader cache for" << name;

	File source_file(fs->GetDataPath() + "shaders/" + desc.filename);
	source_file.Open();

	std::string source;
	source.resize(source_file.Size());
	source_file.Read(source.data(), source.size());

	source = vk::GetShaderString(desc) + source;
	//Log() << name;
	//Log() << source;

	std::vector<uint32_t> binary;
	binary = vk::CompileShader(desc.filename, desc.type, source);

	File binary_file(fs->GetDataPath() + "shaders/cache/" + name);
	if (!binary_file.Open(File::Access::WRITE))
		return {};

	binary_file.Write(binary.data(), binary.size() * sizeof(uint32_t));

	ShaderReflectionData reflection_data = vk::GetShaderReflection(desc.filename, desc.type, binary.data(), binary.size());

	VkShaderModuleCreateInfo shader_ci
	{
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.codeSize = binary.size() * sizeof(uint32_t),
		.pCode = binary.data(),
	};

	VkShaderModule module;
	VkResult result = vkCreateShaderModule(vk->device, &shader_ci, nullptr, &module);
	if (result != VK_SUCCESS)
	{
		Log() << "vkCreateShaderModule failed";
		return {};
	}

	vk->SetObjectName(VK_OBJECT_TYPE_SHADER_MODULE, module, desc.filename.c_str());

	shader_desc_map[store->shader_modules.size()] = desc;

	store->shader_modules.push_back(module);
	store->shader_reflection[store->shader_modules.size() - 1] = std::move(reflection_data);
	return Shader(store->shader_modules.size() - 1, desc.type);
}

Shader RenderDeviceVK::LoadShader(const std::string &name, ShaderDesc &desc, const std::vector<uint32_t> &binary)
{
	ShaderReflectionData reflection_data = vk::GetShaderReflection(name, desc.type, binary.data(), binary.size());

	VkShaderModuleCreateInfo shader_ci
	{
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.codeSize = binary.size() * sizeof(uint32_t),
		.pCode = binary.data(),
	};

	VkShaderModule module;
	VkResult result = vkCreateShaderModule(vk->device, &shader_ci, nullptr, &module);
	if (result != VK_SUCCESS)
	{
		Log() << "vkCreateShaderModule failed";
		return {};
	}

	vk->SetObjectName(VK_OBJECT_TYPE_SHADER_MODULE, module, name.c_str());

	shader_desc_map[store->shader_modules.size()] = desc;

	store->shader_modules.push_back(module);
	store->shader_reflection[store->shader_modules.size() - 1] = std::move(reflection_data);
	return Shader(store->shader_modules.size() - 1, desc.type);
}

void RenderDeviceVK::LoadMaterialDefinition(const std::string &filename)
{
	//
}

PipelineID RenderDeviceVK::CreatePipeline(const std::string &name, const PipelineDesc &desc)
{
	vk::Pipeline pipeline;

	/*pipeline.layout = vk::CreatePipelineLayout(vk->device,
		store->descriptor_set_layouts,
		{ &store->shader_reflection[desc.shaders[0].handle], &store->shader_reflection[desc.shaders[1].handle] },
		pipeline.constant_ranges, pipeline.decriptor_set_layouts, 0);*/

	vk::CreatePipelineLayout(vk->device, pipeline, store->descriptor_set_layouts,
							 { shader_desc_map[desc.shaders[0].handle], shader_desc_map[desc.shaders[1].handle] });

	//if (name == "deferred/static_meshes")
	//	std::terminate();

	for (size_t i = 0; i < pipeline.decriptor_set_layouts.size(); i++)
	{
		vk->SetObjectName(VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT, pipeline.decriptor_set_layouts[i],
						  fmt::format("{} {}", name, i).c_str());
	}

	vk::GraphicsPipelineBuilder builder(vk->device);
	builder.SetTopology(desc.topology);
	builder.SetVertexFormat(desc.vertex_attribs);
	//builder.CreateVertexInputStage(desc.vertex_attribs, desc.topology);
	builder.SetRasterState(desc.raster);
	builder.SetLayout(pipeline.layout);

	if (desc.framebuffer_id)
		builder.SetFramebuffer(GetFramebuffer(desc.framebuffer_id));
	else
		builder.SetSwapchainFormat(vk->swapchain_format);

	for (const Shader &shader: desc.shaders)
		builder.AppendShader(vk::ConvertEnum(shader.type), store->shader_modules[shader.handle]);

	pipeline.pipeline = builder.Build(vk->device, VK_NULL_HANDLE); // TODO: measure pipeline cache speedup if any
	if (pipeline.pipeline == VK_NULL_HANDLE)
		return {};

	vk->SetObjectName(VK_OBJECT_TYPE_PIPELINE, pipeline.pipeline, name.c_str());

	store->pipelines.push_back(pipeline);
	return { { uint32_t(store->pipelines.size() - 1) } };
}


void RenderDeviceVK::BindPipeline(PipelineID pipeline)
{
	store->current_pipeline = store->pipelines.at(pipeline.handle);
	vkCmdBindPipeline(vk->current_command_buffer,
					  VK_PIPELINE_BIND_POINT_GRAPHICS, store->current_pipeline.pipeline);
}

void RenderDeviceVK::Draw(uint32_t first, uint32_t count)
{
	vkCmdDraw(vk->current_command_buffer, count, 1, first, 0);
}

void RenderDeviceVK::DrawIndexed(uint32_t first, uint32_t count)
{
	vkCmdDrawIndexed(vk->current_command_buffer, count, 1, first, 0, 0);
}

void RenderDeviceVK::BeginFrame()
{
	uint32_t prev_time = times[1] - times[0];

	times[0] = SDL_GetTicks();
	/*if (prev_time > 30)
		vkQueueWaitIdle(vk->graphics_queue);

	else*/
	uint32_t prev_frame_index = vk->frame_index == 0 ? vk->frame_resources.size() - 1 : vk->frame_index - 1;

	/*uint64_t wait_value = vk->frame_resources[vk->frame_index].last_signaled_value;
	VkSemaphoreWaitInfo wait_semaphore_present_info
	{
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
		.pNext = nullptr,
		.flags = 0,
		.semaphoreCount = 1,
		.pSemaphores = &vk->timeline_semaphore,
		.pValues = &wait_value,
	};

	vkWaitSemaphores(vk->device, &wait_semaphore_present_info, UINT64_MAX);*/

	//Log() << vk->present_id;

	if (vk->present_id > vk->swapchain_resources.size())
		vk->WaitForPresentKHR(vk->device, vk->swapchain, vk->present_id - 1, UINT64_MAX);


	vkWaitForFences(vk->device, 1, &vk->frame_resources[vk->frame_index].fence, VK_TRUE, UINT64_MAX);
	vkResetFences(vk->device, 1, &vk->frame_resources[vk->frame_index].fence);
	//vkQueueWaitIdle(vk->graphics_queue);
	//times[1] = SDL_GetTicks();

	VkResult result = vkAcquireNextImageKHR(vk->device, vk->swapchain, UINT64_MAX,
											vk->frame_resources[vk->frame_index].present_semaphore,
											VK_NULL_HANDLE, &vk->image_index);
	//Log() << vk->image_index << vk->frame_index;
	//times[2] = SDL_GetTicks();

	if (result == VK_ERROR_OUT_OF_DATE_KHR)
		throw std::runtime_error("Swapchain out of date!!!");

	VkCommandBufferBeginInfo beginInfo
	{
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.pNext = nullptr,
		.flags = 0,
		.pInheritanceInfo = nullptr,
	};

	/*if (vk->frame_timeline_index >= vk->frame_resources.size())
	{
		uint64_t wait_value = (vk->frame_timeline_index - vk->frame_resources.size()) + 1;
		VkSemaphoreWaitInfo wait_semaphore_present_info
		{
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
			.pNext = nullptr,
			.flags = 0,
			.semaphoreCount = 1,
			.pSemaphores = &vk->timeline_semaphore,
			.pValues = &wait_value,
		};

		vkWaitSemaphores(vk->device, &wait_semaphore_present_info, UINT64_MAX);
	}*/

	vk->current_command_buffer = vk->frame_resources[vk->frame_index].command_buffer;
	vkResetCommandBuffer(vk->current_command_buffer, 0);
	vkBeginCommandBuffer(vk->current_command_buffer, &beginInfo);

	//for (auto resource: tracked_resources)
	//	resource.second.prev = ImageLayout::UNDEFINED;

	//swapchain_image_prev_layouts[vk->image_index] = ImageLayout::UNDEFINED;
}


void RenderDeviceVK::EndFrame()
{
	uint32_t prev_frame_index = vk->frame_index == 0 ? vk->frame_resources.size() - 1 : vk->frame_index - 1;
	//LayoutTransition({}, ImageLayout::COLOR_ATTACHMENT, ImageLayout::PRESENT);

	vkEndCommandBuffer(vk->current_command_buffer);

	VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

	VkSubmitInfo submit_info
	{
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.pNext = nullptr,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &vk->frame_resources[vk->frame_index].present_semaphore,
		.pWaitDstStageMask = wait_stages,
		.commandBufferCount = 1,
		.pCommandBuffers = &vk->current_command_buffer,
		.signalSemaphoreCount = 1,
		.pSignalSemaphores = &vk->swapchain_resources[vk->image_index].render_semaphore,
	};

	times[3] = SDL_GetTicks();
	//vkResetFences(vk->device, 1, &vk->frame_resources[vk->frame_index].fence);
	times[4] = SDL_GetTicks();
	//vkQueueSubmit(vk->graphics_queue, 1, &submit_info, vk->frame_resources[vk->frame_index].fence);

	VkSemaphoreSubmitInfo wait_semaphore_submit_info
	{
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
		.pNext = nullptr,
		.semaphore = vk->frame_resources[vk->frame_index].present_semaphore,
		.value = 0,
		.stageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		.deviceIndex = 0,
	};

	VkSemaphoreSubmitInfo signal_semaphore_submit_info
	{
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
		.pNext = nullptr,
		.semaphore = vk->timeline_semaphore, //vk->swapchain_resources[vk->image_index].render_semaphore,
		.value = vk->frame_timeline_index + 1,
		.stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
		.deviceIndex = 0,
	};

	VkSemaphoreSubmitInfo signal_semaphore_submit_info_2
	{
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
		.pNext = nullptr,
		.semaphore = vk->swapchain_resources[vk->image_index].render_semaphore,
		.value = 0,
		.stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
		.deviceIndex = 0,
	};

	VkCommandBufferSubmitInfo command_buffer_info
	{
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO,
		.pNext = nullptr,
		.commandBuffer = vk->current_command_buffer,
		.deviceMask = 0,
	};

	VkSemaphoreSubmitInfo signals[2] { signal_semaphore_submit_info_2, signal_semaphore_submit_info };

	VkSubmitInfo2 submit_info_2
	{
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
		.pNext = nullptr,
		.flags = 0,
		.waitSemaphoreInfoCount = 1,
		.pWaitSemaphoreInfos = &wait_semaphore_submit_info,
		.commandBufferInfoCount = 1,
		.pCommandBufferInfos = &command_buffer_info,
		.signalSemaphoreInfoCount = 1,
		.pSignalSemaphoreInfos = signals,
	};

	//vkResetFences(vk->device, 1, &vk->frame_resources[vk->frame_index].fence);

	vkQueueSubmit2(vk->graphics_queue, 1, &submit_info_2, vk->frame_resources[vk->frame_index].fence); //vk->frame_resources[vk->frame_index].fence);

	/*uint64_t wait_value = vk->frame_timeline_index + 1;
	VkSemaphoreWaitInfo wait_semaphore_present_info
	{
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
		.pNext = nullptr,
		.flags = 0,
		.semaphoreCount = 1,
		.pSemaphores = &vk->timeline_semaphore,
		.pValues = &wait_value,
	};

	vkWaitSemaphores(vk->device, &wait_semaphore_present_info, UINT64_MAX);*/

	times[5] = SDL_GetTicks();

	VkPresentIdKHR present_id_info
	{
		.sType = VK_STRUCTURE_TYPE_PRESENT_ID_KHR,
		.pNext = nullptr,
		.swapchainCount = 1,
		.pPresentIds = &vk->present_id,
	};

	VkResult result;
	VkPresentInfoKHR present_info
	{
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.pNext = &present_id_info,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &vk->swapchain_resources[vk->image_index].render_semaphore,
		.swapchainCount = 1,
		.pSwapchains = &vk->swapchain,
		.pImageIndices = &vk->image_index,
		.pResults = &result,
	};

	vkQueuePresentKHR(vk->graphics_queue, &present_info);
	times[6] = SDL_GetTicks();

	vk->frame_timeline_index += 1;
	vk->frame_resources[vk->frame_index].last_signaled_value = vk->frame_timeline_index;

	vk->frame_index = (vk->frame_index + 1) % vk->frame_resources.size();
	vk->present_id++;

	/*vkWaitForFences(vk->device, 1, &vk->frame_resources[vk->frame_index].fence, VK_TRUE, UINT64_MAX);

	//vkQueueWaitIdle(vk->graphics_queue);
	//times[1] = SDL_GetTicks();

	vkAcquireNextImageKHR(vk->device, vk->swapchain, UINT64_MAX,
											vk->frame_resources[vk->frame_index].present_semaphore,
											VK_NULL_HANDLE, &vk->image_index);*/
	//Log() << vk->image_index << vk->frame_index;
	//times[2] = SDL_GetTicks();

	if (result != VK_SUCCESS)
		throw std::runtime_error("Swapchain out of date!!!");

	//Log() << times[1] - times[0] << times[2] - times[1] << times[3] - times[2] << times[4] - times[3] << times[5] - times[4] << times[6] - times[5];
}

void RenderDeviceVK::BeginRenderPass(FramebufferID framebuffer_id, RenderPass::Clear clear_flags)
{
	BeginRenderPass(framebuffer_id, clear_flags, {});
}

void RenderDeviceVK::BeginRenderPass(FramebufferID framebuffer_id, RenderPass::Clear clear_flags, Texture resolve_depth)
{
	/*if (framebuffer_id)
	{
		// framebuffer
		//LayoutTransition(GetFramebuffer(framebuffer_id).color_textures[0], ImageLayout::UNDEFINED, ImageLayout::COLOR_ATTACHMENT);
		//LayoutTransition(GetFramebuffer(framebuffer_id).depth_texture, ImageLayout::UNDEFINED, ImageLayout::DEPTH_STENCIL_ATTACHMENT, true);
		Framebuffer framebuffer = GetFramebuffer(framebuffer_id);
		for (auto texture: framebuffer.color_textures)
			LayoutTransition(texture, ImageLayout::UNDEFINED, ImageLayout::COLOR_ATTACHMENT);
			//MakeResourceTransition(texture, ImageLayout::COLOR_ATTACHMENT);
		MakeResourceTransition(GetFramebuffer(framebuffer_id).depth_texture, ImageLayout::DEPTH_STENCIL_ATTACHMENT);
	}
	else
	{
		// back buffer
		LayoutTransition({}, ImageLayout::UNDEFINED, ImageLayout::COLOR_ATTACHMENT);
		//LayoutTransition({}, ImageLayout::SHADER_READ_ONLY, ImageLayout::DEPTH_STENCIL_ATTACHMENT, true);
		MakeResourceTransition(vk->depth_texture_fffuuu, ImageLayout::DEPTH_STENCIL_ATTACHMENT);
	}*/

	// TODO: implement clear_flags
	std::vector<VkImageView> color_image_views;
	VkImageView depth_image_view;
	VkImageLayout depth_layout;
	uint32_t width, height;
	//VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT;

	if (framebuffer_id)
	{
		Framebuffer framebuffer = store->framebuffers[framebuffer_id.handle];
		for (auto &texture: framebuffer.color_textures)
			color_image_views.push_back(store->textures[texture.handle].image_view);
		depth_image_view = store->textures[framebuffer.depth_texture.handle].image_view;
		depth_layout = store->textures[framebuffer.depth_texture.handle].layout;
		width = framebuffer.width;
		height = framebuffer.height;
	}
	else
	{
		color_image_views.push_back(vk->swapchain_resources[vk->image_index].texture.image_view);
		//depth_image_view = store->textures.at(vk->depth_texture_fffuuu.handle).image_view;
		//depth_layout = store->textures.at(vk->depth_texture_fffuuu.handle).layout;
		depth_image_view = VK_NULL_HANDLE;
		depth_layout = VK_IMAGE_LAYOUT_UNDEFINED;
		width = vk->width;
		height = vk->height;
	}

	VkAttachmentLoadOp depth_load_op = VK_ATTACHMENT_LOAD_OP_CLEAR;
	if (clear_flags == RenderPass::Clear::COLOR)
		depth_load_op = VK_ATTACHMENT_LOAD_OP_LOAD;

	std::vector<VkRenderingAttachmentInfo> color_attachments(color_image_views.size());
	for (size_t i = 0; i < color_image_views.size(); i++)
	{
		VkRenderingAttachmentInfo color_attachment =
		{
			.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
			.pNext = nullptr,
			.imageView = color_image_views[i],
			.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
			.resolveMode = VK_RESOLVE_MODE_NONE,
			.resolveImageView = VK_NULL_HANDLE,
			.resolveImageLayout = VK_IMAGE_LAYOUT_UNDEFINED,
			.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR, // VK_ATTACHMENT_LOAD_OP_DONT_CARE
			.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
			.clearValue = { .color = vk->clear_color },
		};

		color_attachments[i] = color_attachment;
	}

	VkRenderingAttachmentInfo depth_attachment =
	{
		.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
		.pNext = nullptr,
		.imageView = depth_image_view, //store->textures[framebuffer.depth_texture.handle].image_view,
		.imageLayout = depth_layout, //VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL, //VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
		.resolveMode = VK_RESOLVE_MODE_NONE,
		.resolveImageView = VK_NULL_HANDLE,
		.resolveImageLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.loadOp = depth_load_op,
		.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
		.clearValue = { .depthStencil = vk->clear_depth_stencil },
	};

	if (resolve_depth)
	{
		depth_attachment.resolveMode = VK_RESOLVE_MODE_MIN_BIT;
		depth_attachment.resolveImageView = store->textures[resolve_depth.handle].image_view;
		depth_attachment.resolveImageLayout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;
	}


	VkRenderingInfo rendering_info =
	{
		.sType = VK_STRUCTURE_TYPE_RENDERING_INFO,
		.pNext = nullptr,
		.flags = 0,
		.renderArea = { { 0, 0 }, { width, height } },
		.layerCount = 1,
		.viewMask = 0,
		.colorAttachmentCount = uint32_t(color_attachments.size()),
		.pColorAttachments = color_attachments.data(),
		.pDepthAttachment = bool(framebuffer_id) ? &depth_attachment : nullptr,
		.pStencilAttachment = nullptr
	};

	vkCmdBeginRendering(vk->current_command_buffer, &rendering_info);

	SetViewport({ 0, 0, width, height });
}

void RenderDeviceVK::SetViewport(glm::ivec4 viewport)
{
	VkViewport vk_viewport { float(viewport.x), float(viewport.y), float(viewport.z), float(viewport.w), 0.0f, 1.0f };
	//VkViewport vk_viewport { float(viewport.x), float(viewport.w), float(viewport.z), float(-viewport.w), 0.0f, 1.0f };
	VkRect2D vk_scissor { { viewport.x, viewport.y }, { uint32_t(viewport.z), uint32_t(viewport.w) } };
	vkCmdSetViewport(vk->current_command_buffer, 0, 1, &vk_viewport);
	vkCmdSetScissor(vk->current_command_buffer, 0, 1, &vk_scissor);
}

void RenderDeviceVK::SetCullMode(uint32_t mode)
{
	//VK_CULL_MODE_NONE = 0,
	//VK_CULL_MODE_FRONT_BIT = 0x00000001,
	//VK_CULL_MODE_BACK_BIT = 0x00000002,
	//VK_CULL_MODE_FRONT_AND_BACK = 0x00000003,
	VkCullModeFlags cull_mode = VK_CULL_MODE_NONE;
	switch (mode)
	{
		case 1: cull_mode = VK_CULL_MODE_FRONT_BIT; break;
		case 2: cull_mode = VK_CULL_MODE_BACK_BIT; break;
		case 3: cull_mode = VK_CULL_MODE_FRONT_AND_BACK; break;
	}

	vkCmdSetCullMode(vk->current_command_buffer, cull_mode);
}

void RenderDeviceVK::EndRenderPass(FramebufferID framebuffer_id)
{
	vkCmdEndRendering(vk->current_command_buffer);

	if (framebuffer_id)
	{
		// framebuffer
		//LayoutTransition(GetFramebuffer(framebuffer_id).color_textures[0], ImageLayout::COLOR_ATTACHMENT, ImageLayout::SHADER_READ_ONLY);
		//LayoutTransition(GetFramebuffer(framebuffer_id).depth_texture, ImageLayout::DEPTH_STENCIL_ATTACHMENT, ImageLayout::SHADER_READ_ONLY, true);
	}
	else
	{
		// back buffer
		//LayoutTransition({}, ImageLayout::COLOR_ATTACHMENT, ImageLayout::PRESENT, false);
	}
}



void RenderDeviceVK::LayoutTransition(Texture texture, ImageLayout from, ImageLayout to)
{
	//if (texture == vk->depth_texture_fffuuu)
	//	Log() << "Depth texture" << int(from) << int(to);

	//if (is_depth != Texture::IsDepth(texture.format))
	//	std::terminate();

	vk::Texture *vk_texture = nullptr;
	VkImageSubresourceRange subresource_range = vk->generic_subresource;

	if (!texture)
	{
		vk_texture = &vk->swapchain_resources[vk->image_index].texture;
	}
	else
	{
		// move prev_layout to vk::Texture
		//if (texture.prev_layout == to) // FIXME: does queue transfer has same layout? need to check
		//	return;

		vk_texture = &store->textures[texture.handle];

		if (Texture::IsDepth(texture.format))
			subresource_range.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
	}

	VkPipelineStageFlags2 src_stage_mask = 0;
	VkPipelineStageFlags2 dst_stage_mask = 0;
	VkAccessFlags2 src_access_mask = 0;
	VkAccessFlags2 dst_access_mask = 0;
	VkImageLayout old_layout = vk::ConvertEnum(from);
	VkImageLayout new_layout = vk::ConvertEnum(to);

	switch (from)
	{
		case ImageLayout::UNDEFINED:
			src_stage_mask = VK_PIPELINE_STAGE_2_ALL_GRAPHICS_BIT;
			src_access_mask = VK_ACCESS_2_MEMORY_WRITE_BIT; // VK_ACCESS_2_NONE if depth
			break;

		case ImageLayout::COLOR_ATTACHMENT:
			src_stage_mask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
			src_access_mask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT;
			break;

		case ImageLayout::DEPTH_ATTACHMENT:
			Warn() << "DEPTH_ATTACHMENT 'from' case is not implemented";
			break;

		case ImageLayout::DEPTH_STENCIL_ATTACHMENT:
			src_stage_mask = VK_PIPELINE_STAGE_2_ALL_GRAPHICS_BIT; // depth attachment output? early/late test?
			src_access_mask = VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			break;

		case ImageLayout::COLOR_READ_ONLY:
			break;

		case ImageLayout::DEPTH_STENCIL_READ_ONLY:
			break; // TODO: implement

		case ImageLayout::PRESENT:
			Warn() << "Can't convert from PRESENT layout";
			return;
	}

	switch (to)
	{
		case ImageLayout::UNDEFINED:
			Warn() << "Can't convert to UNDEFINED layout";
			break;

		case ImageLayout::COLOR_ATTACHMENT:
			dst_stage_mask = VK_PIPELINE_STAGE_2_ALL_GRAPHICS_BIT;
			dst_access_mask = VK_ACCESS_2_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT;
			break;

		case ImageLayout::DEPTH_ATTACHMENT:
			Warn() << "DEPTH_ATTACHMENT 'to' case is not implemented";
			break;

		case ImageLayout::DEPTH_STENCIL_ATTACHMENT:
			dst_stage_mask = VK_PIPELINE_STAGE_2_ALL_GRAPHICS_BIT;
			dst_access_mask = VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			break;

		case ImageLayout::COLOR_READ_ONLY:
			dst_stage_mask = VK_PIPELINE_STAGE_2_ALL_GRAPHICS_BIT; // VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT if color
			dst_access_mask = VK_ACCESS_2_SHADER_READ_BIT; // VK_ACCESS_2_NONE if color
			break;

		case ImageLayout::DEPTH_STENCIL_READ_ONLY:
			dst_stage_mask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT;
			dst_access_mask = VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
			break; // TODO: implement

		case ImageLayout::PRESENT:
			dst_stage_mask = VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT;
			dst_access_mask = VK_ACCESS_2_NONE;
			break;
	}

	VkImageMemoryBarrier2 barrier
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
		.pNext = nullptr,
		.srcStageMask = src_stage_mask,
		.srcAccessMask = src_access_mask,
		.dstStageMask = dst_stage_mask,
		.dstAccessMask = dst_access_mask,
		.oldLayout = old_layout,
		.newLayout = new_layout,
		.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.image = vk_texture->image,
		.subresourceRange = subresource_range,
	};

	VkDependencyInfo dependency_info
	{
		.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
		.pNext = nullptr,
		.dependencyFlags = 0,
		.memoryBarrierCount = 0,
		.pMemoryBarriers = nullptr,
		.bufferMemoryBarrierCount = 0,
		.pBufferMemoryBarriers = nullptr,
		.imageMemoryBarrierCount = 1,
		.pImageMemoryBarriers = &barrier,
	};

	vkCmdPipelineBarrier2(vk->current_command_buffer, &dependency_info);

	vk_texture->layout = vk::ConvertEnum(to);
}

void RenderDeviceVK::LayoutTransition2(Texture texture, uint32_t step)
{
	VkImageMemoryBarrier2 barrier;
	VkImageSubresourceRange subresource_range = vk->generic_subresource;
	subresource_range.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;

	if (step == 0)
	{
		barrier = VkImageMemoryBarrier2
		{
			.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
			.pNext = nullptr,
			.srcStageMask = VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT,
			.srcAccessMask = VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
			.dstStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT,
			.dstAccessMask = VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_READ_BIT,
			.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
			.newLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
			.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
			.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
			.image = store->textures[texture.handle].image,
			.subresourceRange = subresource_range,
		};
	}

	VkDependencyInfo dependency_info
	{
		.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
		.pNext = nullptr,
		.dependencyFlags = 0,
		.memoryBarrierCount = 0,
		.pMemoryBarriers = nullptr,
		.bufferMemoryBarrierCount = 0,
		.pBufferMemoryBarriers = nullptr,
		.imageMemoryBarrierCount = 1,
		.pImageMemoryBarriers = &barrier,
	};

	vkCmdPipelineBarrier2(vk->current_command_buffer, &dependency_info);
}

GPUBuffer RenderDeviceVK::CreateBuffer(GPUBuffer::Type type, uint32_t size, const void *data) // TODO: handle data pointer
{
	assert(size > 0);

	VkBufferCreateInfo buffer_ci =
	{
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.size = size,
		.usage = vk::ConvertEnum(type),
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = nullptr,
	};

	VkBuffer buffer;
	VkResult result = vkCreateBuffer(vk->device, &buffer_ci, nullptr, &buffer);
	if (result != VK_SUCCESS)
	{
		Log() << "vkCreateBuffer failed";
		throw;
	}

	VkMemoryRequirements memory_req;
	vkGetBufferMemoryRequirements(vk->device, buffer, &memory_req);

	MemoryType memory_type = type == GPUBuffer::Type::STAGING ? MemoryType::STAGING : MemoryType::HOST;
	uint32_t memory_type_index = vk->FindMemoryIndex(memory_req, memory_type);

	VkMemoryAllocateInfo memory_alloc_info
	{
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.pNext = nullptr,
		.allocationSize = memory_req.size,
		.memoryTypeIndex = memory_type_index,
	};

	VkDeviceMemory device_memory;
	result = vkAllocateMemory(vk->device, &memory_alloc_info, nullptr, &device_memory);
	if (result != VK_SUCCESS)
	{
		Log() << "vkAllocateMemory failed";
		throw;
	}

	result = vkBindBufferMemory(vk->device, buffer, device_memory, 0);
	if (result != VK_SUCCESS)
	{
		Log() << "vkBindBufferMemory failed";
		throw;
	}

	store->buffers.push_back({ buffer, device_memory });
	GPUBuffer gpu_buffer = { { uint32_t(store->buffers.size() - 1) }, uint32_t(size), type };

	if (data)
		UpdateBuffer(gpu_buffer, size, data, 0);

	return gpu_buffer;

	//if (size != memory_req.size)
	//	Log() << "Size mismatch" << size << memory_req.size;

	//store->buffers.push_back({ buffer, device_memory });
	//return { { uint32_t(store->buffers.size() - 1) }, uint32_t(size), type };
}

void RenderDeviceVK::UpdateBuffer(GPUBuffer buffer, uint32_t size, const void *data, uint32_t offset)
{
	if (data != nullptr)
	{
		void *ptr = nullptr;
		vkMapMemory(vk->device, store->buffers[buffer.handle].memory, offset, size, 0, &ptr);
		memcpy(ptr, data, size);
		vkUnmapMemory(vk->device, store->buffers[buffer.handle].memory);
		//vkDeviceWaitIdle(vk->device);
	}
}

void *RenderDeviceVK::MapBuffer(GPUBuffer buffer)
{
	void *ptr = nullptr;
	vkMapMemory(vk->device, store->buffers[buffer.handle].memory, 0, buffer.size, 0, &ptr);
	return ptr;
}

void RenderDeviceVK::UnMapBuffer(GPUBuffer buffer)
{
	vkUnmapMemory(vk->device, store->buffers[buffer.handle].memory);
}

void RenderDeviceVK::BindVertexBuffer(GPUBuffer buffer)
{
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(vk->current_command_buffer, 0, 1, &store->buffers[buffer.handle].buffer, offsets);
}

DescriptorSet RenderDeviceVK::CreateDescriptorSet(PipelineID pipeline, Descriptor2::Set set)
{
	VkDescriptorSetAllocateInfo alloc_info
	{
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
		.pNext = nullptr,
		.descriptorPool = store->descriptor_pool,
		.descriptorSetCount = 1,
		.pSetLayouts = &store->pipelines.at(pipeline.handle).decriptor_set_layouts.at(uint32_t(set)),
		//.pSetLayouts = &store->descriptor_layouts.at(std::to_underlying(set)),
	};

	VkDescriptorSet descriptor_set;
	vkAllocateDescriptorSets(vk->device, &alloc_info, &descriptor_set);

	vk->SetObjectName(VK_OBJECT_TYPE_DESCRIPTOR_SET, descriptor_set,
					  fmt::format("fucking set {}", store->descriptor_sets.size()).c_str());

	store->descriptor_sets.push_back(descriptor_set);
	return { { uint32_t(store->descriptor_sets.size() - 1) } };
}

void RenderDeviceVK::WriteDescriptor(DescriptorSet set, uint32_t binding, GPUBuffer value)
{
	VkDescriptorBufferInfo buffer_info
	{
		.buffer = store->buffers.at(value.handle).buffer,
		.offset = 0,
		.range = value.size,
	};

	VkDescriptorType type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	if (value.type == GPUBuffer::Type::STORAGE)
		type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;

	VkWriteDescriptorSet write_set
	{
		.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
		.pNext = nullptr,
		.dstSet = store->descriptor_sets.at(set.handle),
		.dstBinding = binding,
		.dstArrayElement = 0,
		.descriptorCount = 1,
		.descriptorType = type,
		.pImageInfo = nullptr,
		.pBufferInfo = &buffer_info,
		.pTexelBufferView = nullptr,
	};

	vkUpdateDescriptorSets(vk->device, 1, &write_set, 0, nullptr);
}

void RenderDeviceVK::WriteDescriptor(DescriptorSet set, uint32_t binding, Texture value, uint32_t index)
{
	vk::Texture texture = store->textures.at(value.handle);
	VkImageView image_view = texture.image_view;
	VkImageLayout layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

	if (Texture::IsDepth(value.format))
	{
		VkImageViewCreateInfo image_view_ci
		{
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.image = texture.image,
			.viewType = VK_IMAGE_VIEW_TYPE_2D,
			.format = vk::ConvertEnum(value.format),
			.components = {},
			.subresourceRange = vk->generic_subresource,
		};

		layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
		image_view_ci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
		vkCreateImageView(vk->device, &image_view_ci, nullptr, &image_view);
		vk->SetObjectName(VK_OBJECT_TYPE_IMAGE_VIEW, image_view, "Some depth view");
	}

	VkDescriptorImageInfo image_info
	{
		.sampler = vk->linear_sampler,
		.imageView = image_view,
		.imageLayout = layout,
	};

	VkWriteDescriptorSet write_set
	{
		.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
		.pNext = nullptr,
		.dstSet = store->descriptor_sets.at(set.handle),
		.dstBinding = binding,
		.dstArrayElement = index,
		.descriptorCount = 1,
		.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
		.pImageInfo = &image_info,
		.pBufferInfo = nullptr,
		.pTexelBufferView = nullptr,
	};

	vkUpdateDescriptorSets(vk->device, 1, &write_set, 0, nullptr);
}


void RenderDeviceVK::BindDescriptorSet(Descriptor2::Set index, DescriptorSet descriptor_set)
{
	vkCmdBindDescriptorSets(vk->current_command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
					store->current_pipeline.layout, uint32_t(index), 1, &store->descriptor_sets.at(descriptor_set.handle), 0, nullptr);
}

/*void RenderDeviceVK::Push(Shader::Type type, uint32_t offset, glm::vec4 value)
{
	vkCmdPushConstants(vk->current_command_buffer, store->current_pipeline.layout, vk::ConvertEnum(type),
					offset, sizeof(glm::vec4), glm::value_ptr(value));
}*/

// TODO: make flags for all(graphics) stages
/*void RenderDeviceVK::Push(Shader::Type type, uint32_t offset, int value)
{
	vkCmdPushConstants(vk->current_command_buffer, store->current_pipeline.layout, vk::ConvertEnum(type),
					offset, sizeof(int), &value);
	//vkCmdPushConstants(vk->current_command_buffer, store->current_pipeline.layout, VK_SHADER_STAGE_ALL_GRAPHICS,
	//				   offset, sizeof(int), &value);
}*/

void RenderDeviceVK::PushConstant(EngineConstants slot, int value)
{
	vk::ConstantRange &range = store->current_pipeline.constant_ranges.at(uint32_t(slot));
	if (range.stage_flags == 0 || range.size == 0 || range.size != sizeof(int))
		throw std::runtime_error("Wrong push constants range");

	vkCmdPushConstants(vk->current_command_buffer, store->current_pipeline.layout, range.stage_flags,
					range.offset, range.size, &value);
}

void RenderDeviceVK::PushConstant(EngineConstants slot, float value)
{
	// TODO: assert range.size == sizeof(float)
	vk::ConstantRange &range = store->current_pipeline.constant_ranges.at(uint32_t(slot));
	if (range.stage_flags == 0 || range.size == 0 || range.size != sizeof(float))
		throw std::runtime_error("Wrong push constants range");

	vkCmdPushConstants(vk->current_command_buffer, store->current_pipeline.layout, range.stage_flags,
					range.offset, range.size, &value);
}

/*void RenderDeviceVK::Push(size_t size, size_t offset, void *value)
{
	//VkShaderStageFlags flags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
	vkCmdPushConstants(vk->current_command_buffer, store->current_pipeline.layout, VK_SHADER_STAGE_ALL_GRAPHICS,
					   offset, size, value);
}*/

/*void RenderDeviceVK::SetUniform1i(int value)
{
	vkCmdPushConstants(vk->current_command_buffer, store->current_pipeline.layout, VK_SHADER_STAGE_ALL_GRAPHICS,
						0, sizeof(int), &value);
}

void RenderDeviceVK::SetUniform2i(std::array<int, 2> values)
{
	vkCmdPushConstants(vk->current_command_buffer, store->current_pipeline.layout, VK_SHADER_STAGE_ALL_GRAPHICS,
						0, sizeof(int) * values.size(), values.data());
}*/

Texture RenderDeviceVK::CreateTexture(const std::string &name, const TextureDesc &desc)
{
	//Log() << name;

	VkImageUsageFlags usage_flags = 0;
	if (uint32_t(desc.usage & Texture::Usage::SHADER_READ))
		usage_flags |= VK_IMAGE_USAGE_SAMPLED_BIT;

	if (uint32_t(desc.usage & Texture::Usage::COLOR_ATTACHMENT))
		usage_flags |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	if (uint32_t(desc.usage & Texture::Usage::DEPTH_ATTACHMENT))
		usage_flags |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

	if (!desc.pixels.empty()) // FIXME: should it check for not be COLOR_ATTACHMENT?
		usage_flags |= VK_IMAGE_USAGE_HOST_TRANSFER_BIT;

	VkImageCreateInfo image_ci
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.imageType = VK_IMAGE_TYPE_2D,
		.format = vk::ConvertEnum(desc.format),
		.extent = { desc.width, desc.height, 1 },
		.mipLevels = desc.levels,
		.arrayLayers = 1,
		.samples = VkSampleCountFlagBits(desc.samples), //VK_SAMPLE_COUNT_1_BIT,
		.tiling = VK_IMAGE_TILING_OPTIMAL,
		.usage = usage_flags, // /*VK_IMAGE_USAGE_TRANSFER_DST_BIT |*/ VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_HOST_TRANSFER_BIT,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = nullptr,
		.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
	};

	/*if (desc.format == Texture::Format::D24S8)
	{
		image_ci.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
		//image_ci.initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	}*/

	VkImage image;
	vkCreateImage(vk->device, &image_ci, nullptr, &image);
	vk->SetObjectName(VK_OBJECT_TYPE_IMAGE, image, name.c_str());

	VkMemoryRequirements memory_req;
	vkGetImageMemoryRequirements(vk->device, image, &memory_req);

	uint32_t memory_type_index = vk->FindMemoryIndex(memory_req, MemoryType::DEVICE);

	VkMemoryAllocateInfo alloc_info
	{
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.pNext = nullptr,
		.allocationSize = memory_req.size,
		.memoryTypeIndex = memory_type_index,
	};

	VkDeviceMemory memory;
	vkAllocateMemory(vk->device, &alloc_info, nullptr, &memory);

	vkBindImageMemory(vk->device, image, memory, 0);

	VkImageViewCreateInfo image_view_ci
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.image = image,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = vk::ConvertEnum(desc.format),
		.components = {},
		.subresourceRange = vk->generic_subresource,
	};

	image_view_ci.subresourceRange.levelCount = desc.levels;

	if (desc.format == Texture::Format::D24S8)
	{
		image_view_ci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
		//image_ci.initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	}


	VkImageView image_view;
	vkCreateImageView(vk->device, &image_view_ci, nullptr, &image_view);

	if (desc.pixels.empty())
	{
		store->textures.push_back({ image, image_view, memory, VK_IMAGE_LAYOUT_UNDEFINED });
		return { { uint32_t(store->textures.size() - 1) }, desc.format };
	}

	VkHostImageLayoutTransitionInfo layout_transition_info
	{
		.sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO,
		.pNext = nullptr,
		.image = image,
		.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		.subresourceRange = vk->generic_subresource,
	};

	layout_transition_info.subresourceRange.levelCount = desc.levels;

	vkTransitionImageLayout(vk->device, 1, &layout_transition_info);

	/*uint32_t pixel_size = 4;
	if (desc.format == Texture::Format::R8)
		pixel_size = 1;*/

	uint32_t offset = 0;
	for (uint32_t i = 0; i < desc.levels; i++)
	{
		VkImageSubresourceLayers subresource_layers
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.mipLevel = i,
			.baseArrayLayer = 0,
			.layerCount = 1,
		};

		VkMemoryToImageCopy image_copy
		{
			.sType = VK_STRUCTURE_TYPE_MEMORY_TO_IMAGE_COPY,
			.pNext = nullptr,
			.pHostPointer = desc.pixels.data() + offset,
			.memoryRowLength = 0,
			.memoryImageHeight = 0,
			.imageSubresource = subresource_layers,
			.imageOffset = {},
			.imageExtent = { desc.width >> i, desc.height >> i, 1 },
		};

		VkCopyMemoryToImageInfo copy_info
		{
			.sType = VK_STRUCTURE_TYPE_COPY_MEMORY_TO_IMAGE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.dstImage = image,
			.dstImageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
			.regionCount = 1,
			.pRegions = &image_copy,
		};

		vkCopyMemoryToImage(vk->device, &copy_info);
		//vkDeviceWaitIdle(vk->device);

		offset += (desc.width >> i) * (desc.height >> i) * 4; // TODO: get format pixel size
	}

	// ------------------------------------------------------------------------------------------

	store->textures.push_back({ image, image_view, memory, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL });
	return { { uint32_t(store->textures.size() - 1) }, desc.format };
}

FramebufferID RenderDeviceVK::CreateFramebuffer(const FramebufferDesc &desc)
{
	// TODO: check attachment_count range
	// TODO: check width and height less or equal textures width and height

	Framebuffer framebuffer;
	framebuffer.width = desc.width;
	framebuffer.height = desc.height;
	framebuffer.samples = desc.samples;
	framebuffer.color_textures.resize(desc.color_textures.size());
	//framebuffer.color_formats.resize(desc.color_textures.size());

	for (uint32_t i = 0; i < desc.color_textures.size(); i++)
		framebuffer.color_textures[i] = desc.color_textures[i];

	framebuffer.depth_texture = desc.depth_texture;

	store->framebuffers.push_back(framebuffer);	
	return { uint32_t(store->framebuffers.size() - 1) };
}

Framebuffer RenderDeviceVK::GetFramebuffer(FramebufferID framebuffer)
{
	return store->framebuffers[framebuffer.handle];
}

uint32_t RenderDeviceVK::GetFrameIndex() const
{
	return vk->frame_index;
}

uint32_t RenderDeviceVK::GetFrameCount() const
{
	return vk->frame_resources.size();
}



BF_END_NAMESPACE
