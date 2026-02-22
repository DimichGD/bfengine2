#pragma once
#include "engine/resource_manager.hpp"
#include "graphics/render_paths/graphics_context.hpp"
#include "graphics/vulkan/render_device_vk.hpp"

BF_BEGIN_NAMESPACE

class PointLightRenderPath
{
public:
	PointLightRenderPath(RenderDeviceVK *device, Config *config, ResourceManager *resources);
	BF_NON_MOVABLE(PointLightRenderPath)
	BF_NON_COPYABLE(PointLightRenderPath)

	void Create(GraphicsContext *context, const std::vector<Texture> &textures, Texture depth_texture, FramebufferID out_fbo);
	void Destroy();
	void Render();

private:
	RenderDeviceVK *device = nullptr;
	Config *config = nullptr;
	ResourceManager *resources = nullptr;
	GraphicsContext *context = nullptr;

	PipelineID pipeline {};
	//FramebufferID gbuffer {};
	//FramebufferID light_buffer {};
	float width = 0.0f;
	float height = 0.0f;
	DescriptorSet scene_set {};
	DescriptorSet material_set {};
	GPUBuffer quad_vbo {};
};

BF_END_NAMESPACE
