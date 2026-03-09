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
	const char *deferred_texture_shader_name = config->render.api == Config::Render::API::VK ? "deferred/vk_texture" : "deferred/gl_texture";

	//Shader vs = device->LoadShader(Shader::Type::VERTEX, deferred_texture_shader_name);
	Shader vs = resources->LoadShader("general vertex static normal tangent");
	Shader fs = resources->LoadShader("deferred fragment diffuse normal specular");
	//Shader fs = device->LoadShader(Shader::Type::FRAGMENT, deferred_texture_shader_name);

	PipelineDesc pipeline_desc
	{
		.shaders = { vs, fs },
		.topology = Topology::TRIANGLES,
		.vertex_attribs = Vertex::Attrib::POSITION | Vertex::Attrib::TEXCOORD_0| Vertex::Attrib::NORMAL | Vertex::Attrib::TANGENT,
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

	material_set = device->CreateDescriptorSet(pipeline, Descriptor2::Set::MATERIAL);
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
	device->BindDescriptorSet(Descriptor2::Set::MATERIAL, material_set);

	for (auto &mesh: meshes)
	{
		device->BindVertexBuffer(mesh.vbo);
		for (auto &surf: mesh.surfaces)
		{
			//device->Push(Shader::Type::VERTEX, 0, mesh.matrix_index);
			device->PushConstant(EngineConstants::OBJECT_INDEX, int(mesh.matrix_index));
			//device->PushConstant(1, int(surf.material_index));
			//device->Push(Shader::Type::FRAGMENT, 4, surf.texture_index);
			//materials.at(surf.texture_index).Bind(device);
			//if (!surf.material->Ready())
			//	surf.material->Setup(device, device->CreateDescriptorSet(pipeline, Descriptor2::Set::MATERIAL));
			if (!surf.descriptor_set)
			{
				//surf.descriptor_set = device->CreateDescriptorSet(pipeline, Descriptor2::Set::MATERIAL);
				//surf.material->Setup2(device, nullptr, Descriptor2::Set::MATERIAL, surf.descriptor_set);
				surf.material->Setup2(device, nullptr, Descriptor2::Set::MATERIAL, material_set);

				//std::static_pointer_cast<CustomMaterial>(surf.material)->Setup2(device, nullptr, Descriptor2::Set::MATERIAL, surf.descriptor_set);
				/*std::static_pointer_cast<CustomMaterial>(surf.material)->Setup2(device, nullptr, Descriptor2::Set::SCENE, scene_set[0]);
				std::static_pointer_cast<CustomMaterial>(surf.material)->Setup2(device, nullptr, Descriptor2::Set::SCENE, scene_set[1]);
				std::static_pointer_cast<CustomMaterial>(surf.material)->Setup2(device, nullptr, Descriptor2::Set::SCENE, scene_set[2]);*/
			}

			//surf.material->Bind(device);
			//device->BindDescriptorSet(Descriptor2::Set::MATERIAL, surf.descriptor_set);
			device->PushConstant(EngineConstants::MATERIAL_INDEX, int(std::static_pointer_cast<CustomMaterial>(surf.material)->index));
			//device->PushConstant(EngineConstants::TEXTURE_1, int(std::static_pointer_cast<CustomMaterial>(surf.material)->index + 1));
			//device->PushConstant(EngineConstants::TEXTURE_2, int(std::static_pointer_cast<CustomMaterial>(surf.material)->index + 2));
			device->Draw(surf.vertex_range.start, surf.vertex_range.count);
		}
	}

	//device->EndRenderPass(gbuffer);
}



BF_END_NAMESPACE
