#include "debug_render_path.hpp"

BF_BEGIN_NAMESPACE

Debug::Debug(RenderDevice *device, Config *config, ResourceManager *resources)
{
	this->device = device;
	this->config = config;
	this->resources = resources;
	this->width = config->window.width;
	this->height = config->window.height;
}

void Debug::Create(std::vector<GraphicsContext> &context, FramebufferID out_fbo)
{
	//this->context = context;
	const char *forward_line_shader_name = config->render.api == Config::Render::API::VK ? "forward/vk_line" : "forward/gl_line";
	const char *forward_texture_shader_name = config->render.api == Config::Render::API::VK ? "forward/vk_texture" : "forward/gl_texture";

	Shader vs_line = device->LoadShader(Shader::Type::VERTEX, forward_line_shader_name);
	Shader fs_line = device->LoadShader(Shader::Type::FRAGMENT, forward_line_shader_name);
	Shader vs_texture = device->LoadShader(Shader::Type::VERTEX, forward_texture_shader_name);
	Shader fs_texture = device->LoadShader(Shader::Type::FRAGMENT, forward_texture_shader_name);

	PipelineDesc pipeline_line_desc
	{
		.shaders = { vs_line, fs_line },
		.topology = Topology::LINES,
		.vertex_attribs = Vertex::Attrib::POSITION,
		.raster = {
			.blend = Blend::NONE,
			.depth_test = true,
			.depth_write = false,
		},
		.framebuffer_id = out_fbo,
	};

	PipelineDesc pipeline_mesh_desc
	{
		.shaders = { vs_texture, fs_texture },
		.topology = Topology::TRIANGLES,
		.vertex_attribs = Vertex::Attrib::POSITION | Vertex::Attrib::TEXCOORD_0,
		.raster = {
			.blend = Blend::NONE,
			.depth_test = true,
			.depth_write = false,
		},
		.framebuffer_id = out_fbo,
	};

	pipeline_lines = device->CreatePipeline("debug/colored_lines", pipeline_line_desc);
	pipeline_meshes = device->CreatePipeline("debug/textured_meshes", pipeline_mesh_desc);

	for (uint32_t i = 0; i < 3; i++)
	{
		scene_set_lines[i] = device->CreateDescriptorSet(pipeline_lines, Descriptor2::Set::SCENE);
		scene_set_meshes[i] = device->CreateDescriptorSet(pipeline_meshes, Descriptor2::Set::SCENE);

		device->WriteDescriptor(scene_set_lines[i], 0, context[i].active_camera_ubo);
		device->WriteDescriptor(scene_set_lines[i], 1, context[i].model_matrices_ubo);
		device->WriteDescriptor(scene_set_lines[i], 2, context[i].colors_ubo);

		device->WriteDescriptor(scene_set_meshes[i], 0, context[i].active_camera_ubo);
		device->WriteDescriptor(scene_set_meshes[i], 1, context[i].model_matrices_ubo);
	}
}

void Debug::Destroy()
{
	//
}

void Debug::Render(std::vector<Mesh> &meshes, std::vector<Mesh> &meshes2, uint32_t current_index)
{
	//device->BeginRenderPass({}, RenderPass::Clear::COLOR);

	device->BindPipeline(pipeline_lines);
	device->BindDescriptorSet(Descriptor2::Set::SCENE, scene_set_lines[current_index]);
	//device->BindDescriptorSet(Descriptor2::Set::MATERIAL, context->material_set);

	for (auto &mesh: meshes)
	{
		device->BindVertexBuffer(mesh.vbo);
		//device->Push(Shader::Type::VERTEX, 0, mesh.matrix_index);
		device->PushConstant(0, int(mesh.matrix_index));
		for (auto &surf: mesh.surfaces)
		{
			//device->Push(Shader::Type::FRAGMENT, 4, surf.material_index);
			device->PushConstant(1, int(surf.material_index));
			//materials.at(surf.texture_index).Bind(device);
			//if (!surf.material->Ready())
			//	surf.material->Setup(device, device->CreateDescriptorSet(pipeline_lines, Descriptor2::Set::MATERIAL));

			//surf.material->Bind(device);
			//device->BindDescriptorSet(Descriptor2::Set::MATERIAL, surf.material.descriptor_set);
			device->Draw(surf.vertex_range.start, surf.vertex_range.count);
		}
	}

	device->BindPipeline(pipeline_meshes);
	device->BindDescriptorSet(Descriptor2::Set::SCENE, scene_set_meshes[current_index]);

	for (auto &mesh: meshes2)
	{
		device->BindVertexBuffer(mesh.vbo);
		//device->Push(Shader::Type::VERTEX, 0, mesh.matrix_index);
		device->PushConstant(0, int(mesh.matrix_index));
		for (auto &surf: mesh.surfaces)
		{
			//device->Push(Shader::Type::FRAGMENT, 4, 0);
			if (!surf.descriptor_set)
			{
				surf.descriptor_set = device->CreateDescriptorSet(pipeline_meshes, Descriptor2::Set::MATERIAL);
				surf.material->Setup(device, surf.descriptor_set);
			}

			device->BindDescriptorSet(Descriptor2::Set::MATERIAL, surf.descriptor_set);
			device->Draw(surf.vertex_range.start, surf.vertex_range.count);
		}
	}

	//device->EndRenderPass({});
}

BF_END_NAMESPACE
