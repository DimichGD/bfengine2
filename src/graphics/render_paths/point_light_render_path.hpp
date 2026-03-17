#pragma once
#include "engine/resource_manager.hpp"
#include "graphics/render_paths/graphics_context.hpp"
#include "graphics/vulkan/vk_render_device.hpp"

BF_BEGIN_NAMESPACE

class PointLightRenderPath
{
public:
	PointLightRenderPath(RenderDevice *device, Config *config, ResourceManager *resources);
	BF_NON_MOVABLE(PointLightRenderPath)
	BF_NON_COPYABLE(PointLightRenderPath)

	void Create(GraphicsContext &context, const std::vector<Texture> &textures, Texture depth_texture, FramebufferID out_fbo);
	void Destroy();
	void Render(GraphicsContext &context, uint32_t current_index);

private:
	//RenderDeviceVK *device = nullptr;
	RenderDevice *device = nullptr;
	Config *config = nullptr;
	ResourceManager *resources = nullptr;
	GraphicsContext *context = nullptr;

	PipelineID pipeline {};
	//FramebufferID gbuffer {};
	//FramebufferID light_buffer {};
	float width = 0.0f;
	float height = 0.0f;
	//DescriptorSet scene_set {};
	DescriptorSet material_set {};
	GPUBuffer quad_vbo {};
	GPUBuffer sphere_vbo {};
	uint32_t sphere_vertex_count = 0;
};

BF_END_NAMESPACE
