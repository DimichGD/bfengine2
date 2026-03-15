#include "deferred_render_path.hpp"
#include "core/log.hpp"

BF_BEGIN_NAMESPACE

Deferred::Deferred(RenderDevice *device, Config *config, ResourceManager *resources)
{
	this->device = device;
	this->config = config;
	this->resources = resources;
	this->width = config->window.width;
	this->height = config->window.height;
}

void Deferred::Create(std::vector<GraphicsContext> &context, FramebufferID out_fbo)
{
	//this->context = context;
	//const char *deferred_texture_shader_name = config->render.api == Config::Render::API::VK ? "deferred/vk_texture" : "deferred/gl_texture";

	//Shader vs = device->LoadShader(Shader::Type::VERTEX, deferred_texture_shader_name);
	Shader vs = resources->LoadShader("general vertex static normal tangent");
	Shader fs = resources->LoadShader("deferred fragment diffuse normal specular");
	//Shader fs = device->LoadShader(Shader::Type::FRAGMENT, deferred_texture_shader_name);

	PipelineDesc pipeline_desc
	{
		.shaders = { vs, fs },
		.topology = Topology::TRIANGLES,
		.vertex_attribs = Vertex::Attrib::POSITION | Vertex::Attrib::TEXCOORD_0 | Vertex::Attrib::NORMAL | Vertex::Attrib::TANGENT,
		.raster = {},
		.framebuffer_id = out_fbo,
	};

	pipeline = device->CreatePipeline("deferred/static_meshes", pipeline_desc);

	for (uint32_t i = 0; i < static_cast<RenderDeviceVK *>(device)->GetFrameCount(); i++)
	{
		scene_set[i] = device->CreateDescriptorSet(pipeline, Descriptor2::Set::SCENE);
		device->WriteDescriptor(scene_set[i], 0, context[i].active_camera_ubo);
		device->WriteDescriptor(scene_set[i], 1, context[i].model_matrices_ubo);
	}

	//material_set = device->CreateDescriptorSet(pipeline, Descriptor2::Set::MATERIAL);
}

void Deferred::Destroy()
{
	//
}

void Deferred::Render(std::vector<Mesh> &meshes, uint32_t current_index)
{
	//device->BeginRenderPass(gbuffer, RenderPass::Clear::COLOR_DEPTH);

	device->BindPipeline(pipeline);
	device->BindDescriptorSet(Descriptor2::Set::SCENE, scene_set[current_index]);
	//device->BindDescriptorSet(Descriptor2::Set::SCENE, static_cast<RenderDeviceVK *>(device)->graphics_data.frame_data[current_index].vertex_set);
	//device->BindDescriptorSet(Descriptor2::Set::MATERIAL, static_cast<RenderDeviceVK *>(device)->graphics_data.textures_set);

	for (auto &mesh: meshes)
	{
		device->BindVertexBuffer(mesh.vbo);
		device->PushConstant(EngineConstants::OBJECT_INDEX, int(mesh.matrix_index));

		for (auto &surf: mesh.surfaces)
		{
			//int material_index = std::static_pointer_cast<CustomMaterial>(surf.material)->index;
			//device->PushConstant(EngineConstants::MATERIAL_INDEX, material_index);
			device->BindDescriptorSet(Descriptor2::Set::MATERIAL, surf.descriptor_set);
			device->Draw(surf.vertex_range.start, surf.vertex_range.count);
		}
	}

	//device->EndRenderPass(gbuffer);
}



BF_END_NAMESPACE
