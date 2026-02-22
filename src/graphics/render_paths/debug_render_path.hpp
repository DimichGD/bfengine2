#pragma once
#include "engine/resource_manager.hpp"
#include "graphics/render_paths/graphics_context.hpp"
#include "graphics/vulkan/render_device_vk.hpp"

BF_BEGIN_NAMESPACE

class Debug
{
public:
	Debug(RenderDeviceVK *device, Config *config, ResourceManager *resources);
	BF_NON_MOVABLE(Debug)
	BF_NON_COPYABLE(Debug)

	void Create(GraphicsContext *context, FramebufferID out_fbo);
	void Destroy();
	void Render(std::vector<Mesh> &meshes, std::vector<Mesh> &meshes2);

private:
	RenderDeviceVK *device = nullptr;
	Config *config = nullptr;
	ResourceManager *resources = nullptr;
	GraphicsContext *context = nullptr;

	uint32_t width = 0;
	uint32_t height = 0;

	PipelineID pipeline_meshes {};
	PipelineID pipeline_lines {};
	DescriptorSet scene_set_lines {};
	DescriptorSet scene_set_meshes {};
};

BF_END_NAMESPACE
