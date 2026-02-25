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

void Deferred::Create(GraphicsContext *context, FramebufferID out_fbo)
{
	this->context = context;
	const char *deferred_texture_shader_name = config->render.api == Config::Render::API::VK ? "deferred/vk_texture" : "deferred/gl_texture";

	Shader vs = device->LoadShader(Shader::Type::VERTEX, deferred_texture_shader_name);
	Shader fs = device->LoadShader(Shader::Type::FRAGMENT, deferred_texture_shader_name);

	PipelineDesc pipeline_desc
	{
		.shaders = { vs, fs },
		.topology = Topology::TRIANGLES,
		.vertex_attribs = Vertex::Attrib::POSITION | Vertex::Attrib::TEXCOORD_0| Vertex::Attrib::NORMAL | Vertex::Attrib::TANGENT,
		.raster = {},
		.framebuffer_id = out_fbo,
	};

	pipeline = device->CreatePipeline("deferred/static_meshes", pipeline_desc);

	scene_set = device->CreateDescriptorSet(pipeline, Descriptor2::Set::SCENE);
	device->WriteDescriptor(scene_set, 0, context->active_camera_ubo);
	device->WriteDescriptor(scene_set, 1, context->model_matrices_ubo);
}

void Deferred::Destroy()
{
	//
}

void Deferred::Render(std::vector<Mesh> &meshes)
{
	//device->BeginRenderPass(gbuffer, RenderPass::Clear::COLOR_DEPTH);

	device->BindPipeline(pipeline);
	device->BindDescriptorSet(Descriptor2::Set::SCENE, scene_set);
	//device->BindDescriptorSet(Descriptor2::Set::MATERIAL, context->material_set);

	for (auto &mesh: meshes)
	{
		device->BindVertexBuffer(mesh.vbo);
		for (auto &surf: mesh.surfaces)
		{
			//device->Push(Shader::Type::VERTEX, 0, mesh.matrix_index);
			device->PushConstant(0, int(mesh.matrix_index));
			//device->Push(Shader::Type::FRAGMENT, 4, surf.texture_index);
			//materials.at(surf.texture_index).Bind(device);
			//if (!surf.material->Ready())
			//	surf.material->Setup(device, device->CreateDescriptorSet(pipeline, Descriptor2::Set::MATERIAL));
			if (!surf.descriptor_set)
			{
				surf.descriptor_set = device->CreateDescriptorSet(pipeline, Descriptor2::Set::MATERIAL);
				//surf.material->Setup(device, surf.descriptor_set);
				std::static_pointer_cast<CustomMaterial>(surf.material)->Setup2(device, context, Descriptor2::Set::MATERIAL, surf.descriptor_set);
			}

			//surf.material->Bind(device);
			device->BindDescriptorSet(Descriptor2::Set::MATERIAL, surf.descriptor_set);
			device->Draw(surf.vertex_range.start, surf.vertex_range.count);
		}
	}

	//device->EndRenderPass(gbuffer);
}



BF_END_NAMESPACE
