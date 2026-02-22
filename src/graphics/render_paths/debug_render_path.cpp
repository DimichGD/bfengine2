#include "debug_render_path.hpp"

BF_BEGIN_NAMESPACE

Debug::Debug(RenderDeviceVK *device, Config *config, ResourceManager *resources)
{
	this->device = device;
	this->config = config;
	this->resources = resources;
	this->width = config->window.width;
	this->height = config->window.height;
}

void Debug::Create(GraphicsContext *context, FramebufferID out_fbo)
{
	this->context = context;

	Shader vs_line = device->LoadShader(Shader::Type::VERTEX, "forward/vk_line");
	Shader fs_line = device->LoadShader(Shader::Type::FRAGMENT, "forward/vk_line");
	Shader vs_texture = device->LoadShader(Shader::Type::VERTEX, "forward/vk_texture");
	Shader fs_texture = device->LoadShader(Shader::Type::FRAGMENT, "forward/vk_texture");

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

	scene_set_lines = device->CreateDescriptorSet(pipeline_lines, Descriptor2::Set::SCENE);
	scene_set_meshes = device->CreateDescriptorSet(pipeline_meshes, Descriptor2::Set::SCENE);

	device->WriteDescriptor(scene_set_lines, 0, context->active_camera_ubo);
	device->WriteDescriptor(scene_set_lines, 1, context->model_matrices_ubo);
	device->WriteDescriptor(scene_set_lines, 2, context->colors_ubo);

	device->WriteDescriptor(scene_set_meshes, 0, context->active_camera_ubo);
	device->WriteDescriptor(scene_set_meshes, 1, context->model_matrices_ubo);
}

void Debug::Destroy()
{
	//
}

void Debug::Render(std::vector<Mesh> &meshes, std::vector<Mesh> &meshes2)
{
	//device->BeginRenderPass({}, RenderPass::Clear::COLOR);

	device->BindPipeline(pipeline_lines);
	device->BindDescriptorSet(Descriptor2::Set::SCENE, scene_set_lines);
	//device->BindDescriptorSet(Descriptor2::Set::MATERIAL, context->material_set);

	for (auto &mesh: meshes)
	{
		device->BindVertexBuffer(mesh.vbo);
		device->Push(Shader::Type::VERTEX, 0, mesh.matrix_index);
		for (auto &surf: mesh.surfaces)
		{
			device->Push(Shader::Type::FRAGMENT, 4, surf.material_index);
			//materials.at(surf.texture_index).Bind(device);
			//if (!surf.material->Ready())
			//	surf.material->Setup(device, device->CreateDescriptorSet(pipeline_lines, Descriptor2::Set::MATERIAL));

			//surf.material->Bind(device);
			//device->BindDescriptorSet(Descriptor2::Set::MATERIAL, surf.material.descriptor_set);
			device->Draw(surf.vertex_range.start, surf.vertex_range.count);
		}
	}

	device->BindPipeline(pipeline_meshes);
	device->BindDescriptorSet(Descriptor2::Set::SCENE, scene_set_meshes);

	for (auto &mesh: meshes2)
	{
		device->BindVertexBuffer(mesh.vbo);
		device->Push(Shader::Type::VERTEX, 0, mesh.matrix_index);
		for (auto &surf: mesh.surfaces)
		{
			//device->Push(Shader::Type::FRAGMENT, 4, 0);
			//materials.at(surf.texture_index).Bind(device);
			if (!surf.material->Ready())
				surf.material->Setup(device, device->CreateDescriptorSet(pipeline_meshes, Descriptor2::Set::MATERIAL));

			surf.material->Bind(device);
			//device->BindDescriptorSet(Descriptor2::Set::MATERIAL, surf.material.descriptor_set);
			device->Draw(surf.vertex_range.start, surf.vertex_range.count);
		}
	}

	//device->EndRenderPass({});
}

BF_END_NAMESPACE
