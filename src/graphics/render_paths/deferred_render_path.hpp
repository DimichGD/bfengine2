#pragma once
#include "engine/resource_manager.hpp"
#include "graphics/render_paths/graphics_context.hpp"
#include "graphics/vulkan/vk_render_device.hpp"

BF_BEGIN_NAMESPACE

class Deferred
{
public:
	Deferred(RenderDevice *device, Config *config, ResourceManager *resources);
	BF_NON_MOVABLE(Deferred)
	BF_NON_COPYABLE(Deferred)

	void Create(std::vector<GraphicsContext> &context, FramebufferID out_fbo);
	void Destroy();
	void Render(std::vector<Mesh> &meshes, uint32_t current_index);
	/*FramebufferID GetFramebuffer() const { return gbuffer; }
	Texture GetColorTexture(uint32_t index) { return device->GetFramebuffer(gbuffer).color_textures[index]; }
	std::vector<Texture> GetColorTextures() { return device->GetFramebuffer(gbuffer).color_textures; }
	Texture GetDepthTexture() const { return device->GetFramebuffer(gbuffer).depth_texture; }*/

	/*MaterialID CreateMaterial()
	{
		//materials.emplace_back(device->CreateDescriptorSet(pipeline, Descriptor2::Set::MATERIAL));
		return { { uint32_t(materials.size() - 1) } };
	}

	Material &GetMaterial(MaterialID mat_id)
	{
		return materials.at(mat_id.handle);
	}*/

//private:
	//RenderDeviceVK *device = nullptr;
	RenderDevice *device = nullptr;
	Config *config = nullptr;
	ResourceManager *resources = nullptr;
	//GraphicsContext *context = nullptr;

	PipelineID pipeline {};
	//FramebufferID gbuffer {};
	//FramebufferID light_buffer {};
	uint32_t width = 0;
	uint32_t height = 0;

	//uint32_t current_index = 0;
	DescriptorSet scene_set[3] {};
	//uint32_t material_set = 0;
	//std::vector<Texture> render_targets;
	//Texture depth_texture;
	//std::vector<Material> materials;
};

BF_END_NAMESPACE
