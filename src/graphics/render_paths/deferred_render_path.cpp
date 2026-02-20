#include "deferred_render_path.hpp"

BF_BEGIN_NAMESPACE

Deferred::Deferred(RenderDeviceVK *device, Config *config, ResourceManager *resources)
{
	this->device = device;
	this->config = config;
	this->resources = resources;
	this->width = config->window.width;
	this->height = config->window.height;
}

void Deferred::Create(GraphicsContext *context)
{
	this->context = context;

	TextureDesc color_desc
	{
		.width = width,
		.height = height,
		.format = Texture::Format::SRGBA8,
		.usage = Texture::Usage::COLOR_ATTACHMENT | Texture::Usage::SHADER_READ,
		.levels = 1,
		.pixels = nullptr,
	};

	/*TextureDesc depth_desc
	{
		.width = width,
		.height = height,
		.format = Texture::Format::D24S8,
		.usage = Texture::Usage::DEPTH_ATTACHMENT | Texture::Usage::SHADER_READ,
		.levels = 1,
		.pixels = nullptr,
	};*/

	FramebufferDesc framebuffer_desc
	{
		.width = width,
		.height = height,
		/*.color_texture_count = 1,
		.color_format = Texture::Format::RGBA8_SRGB,
		.depth_format = Texture::Format::D24S8,*/
		.color_textures = { device->CreateTexture(color_desc, false) },
		.depth_texture = device->GetDepthTexture(), //device->CreateTexture(depth_desc, false),
	};

	gbuffer = device->CreateFramebuffer(framebuffer_desc);
	Shader vs = device->LoadShader(Shader::Type::VERTEX, "forward/vk_texture");
	Shader fs = device->LoadShader(Shader::Type::FRAGMENT, "forward/vk_texture");

	PipelineDesc pipeline_desc
	{
		.shaders = { vs, fs },
		.topology = Topology::TRIANGLES,
		.vertex_attribs = Vertex::Attrib::POSITION | Vertex::Attrib::TEXCOORD_0,
		.raster = {},
		.framebuffer_id = gbuffer,
	};

	pipeline = device->CreatePipeline("deferred/static_meshes", pipeline_desc);

	scene_set = device->CreateDescriptorSet(pipeline, Descriptor2::Set::SCENE);
	//context->material_set = device->CreateDescriptorSet(pipeline, Descriptor2::Set::MATERIAL);
	device->WriteDescriptor(scene_set, 0, context->active_camera_ubo);
	device->WriteDescriptor(scene_set, 1, context->model_matrices_ubo);
}

void Deferred::Destroy()
{
	//
}

void Deferred::Render(std::vector<Mesh> &meshes)
{
	device->LayoutTransition(device->GetFramebuffer(gbuffer).color_textures[0], ImageLayout::UNDEFINED, ImageLayout::COLOR_ATTACHMENT);
	device->LayoutTransition(device->GetFramebuffer(gbuffer).depth_texture, ImageLayout::UNDEFINED, ImageLayout::DEPTH_STENCIL_ATTACHMENT);

	device->BeginRenderPass(gbuffer, RenderPass::Clear::COLOR_DEPTH);

	device->BindPipeline(pipeline);
	device->BindDescriptorSet(Descriptor2::Set::SCENE, scene_set);
	//device->BindDescriptorSet(Descriptor2::Set::MATERIAL, context->material_set);

	for (auto &mesh: meshes)
	{
		device->BindVertexBuffer(mesh.vbo);
		for (auto &surf: mesh.surfaces)
		{
			device->Push(Shader::Type::VERTEX, 0, mesh.matrix_index);
			//device->Push(Shader::Type::FRAGMENT, 4, surf.texture_index);
			//materials.at(surf.texture_index).Bind(device);
			if (!surf.material->Ready())
				surf.material->Setup(device, device->CreateDescriptorSet(pipeline, Descriptor2::Set::MATERIAL));

			surf.material->Bind(device);
			//device->BindDescriptorSet(Descriptor2::Set::MATERIAL, surf.material.descriptor_set);
			device->Draw(surf.vertex_range.start, surf.vertex_range.count);
		}
	}

	device->EndRenderPass(gbuffer);

	device->LayoutTransition(GetColorTexture(0), ImageLayout::COLOR_ATTACHMENT, ImageLayout::SHADER_READ_ONLY);
}



BF_END_NAMESPACE
