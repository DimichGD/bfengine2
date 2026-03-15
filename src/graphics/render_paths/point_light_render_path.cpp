#include "point_light_render_path.hpp"
#include "graphics/geometry.hpp"

BF_BEGIN_NAMESPACE

PointLightRenderPath::PointLightRenderPath(RenderDevice *device, Config *config, ResourceManager *resources)
{
	this->device = device;
	this->config = config;
	this->resources = resources;
	this->width = config->window.width;
	this->height = config->window.height;
}

void PointLightRenderPath::Create(std::vector<GraphicsContext> &context, const std::vector<Texture> &textures, Texture depth_texture, FramebufferID out_fbo)
{
	const char *deferred_light_shader_name = config->render.api == Config::Render::API::VK ? "deferred/vk_point_light" : "deferred/gl_point_light";
	//Shader vs = device->LoadShader(Shader::Type::VERTEX, deferred_light_shader_name);
	Shader vs = resources->LoadShader("deferred vertex point_light");
	Shader fs = resources->LoadShader("deferred fragment point_light phong");
	//Shader fs = device->LoadShader(Shader::Type::FRAGMENT, deferred_light_shader_name);

	PipelineDesc pipeline_desc
	{
		.shaders = { vs, fs },
		.topology = Topology::TRIANGLES,
		.vertex_attribs = Vertex::Attrib::POSITION, //| Vertex::Attrib::TEXCOORD_0,
		.raster = {
			.blend = {},
			.depth_test = true,
			.depth_write = false,
			.depth_func = DepthFunc::GREATER,
		},
		.framebuffer_id = out_fbo,
	};

	pipeline = device->CreatePipeline("deferred/point_light", pipeline_desc);

	for (uint32_t i = 0; i < static_cast<RenderDeviceVK *>(device)->GetFrameCount(); i++)
	{
		scene_set[i] = device->CreateDescriptorSet(pipeline, Descriptor2::Set::SCENE);
		material_set[i] = device->CreateDescriptorSet(pipeline, Descriptor2::Set::MATERIAL);

		device->WriteDescriptor(scene_set[i], 0, context[i].active_camera_ubo);
		device->WriteDescriptor(scene_set[i], 1, context[i].model_matrices_ubo);
		device->WriteDescriptor(scene_set[i], 4, context[i].point_lights_ubo);
		device->WriteDescriptor(scene_set[i], 3, context[i].camera_light_data);

		device->WriteDescriptor(material_set[i], 0, textures[0]);
		device->WriteDescriptor(material_set[i], 1, textures[1]);
		device->WriteDescriptor(material_set[i], 2, textures[2]);
		device->WriteDescriptor(material_set[i], 3, depth_texture);
	}

	/*scene_set = device->CreateDescriptorSet(pipeline, Descriptor2::Set::SCENE);
	material_set = device->CreateDescriptorSet(pipeline, Descriptor2::Set::MATERIAL);

	device->WriteDescriptor(scene_set, 0, context->active_camera_ubo);
	//device->WriteDescriptor(scene_set, 1, context->model_matrices_ubo);
	device->WriteDescriptor(scene_set, 2, context->point_lights_ubo);
	device->WriteDescriptor(scene_set, 3, context->camera_pos_ubo);

	device->WriteDescriptor(material_set, 0, textures[0]);
	device->WriteDescriptor(material_set, 1, textures[1]);
	device->WriteDescriptor(material_set, 2, textures[2]);
	//device->WriteDescriptor(material_set, 3, textures[3]);
	device->WriteDescriptor(material_set, 3, depth_texture);*/

	/*std::vector<float> quad_verts
	{
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, height, 0.0f, 0.0f, 1.0f,
		width, 0.0f, 0.0, 1.0f, 0.0f,

		width, 0.0f, 0.0, 1.0f, 0.0f,
		0.0f, height, 0.0f, 0.0f, 1.0f,
		width, height, 0.0, 1.0f, 1.0f,
	};*/

	/*std::vector<float> quad_verts
	{
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0, 1.0f, 0.0f,

		1.0f, 1.0f, 0.0, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0, 1.0f, 1.0f,
	};*/

	std::vector<float> quad_verts
	{
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0, 1.0f, 1.0f,

		1.0f, 1.0f, 0.0, 1.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0, 1.0f, 0.0f,
	};

	quad_vbo = device->CreateBuffer(GPUBuffer::VERTEX, quad_verts);

	std::vector<Vertex3D> sphere_verts = GenerateSphere(16, 16);
	sphere_vertex_count = sphere_verts.size();
	sphere_vbo = device->CreateBuffer(GPUBuffer::VERTEX, sphere_verts);
}

void PointLightRenderPath::Destroy()
{
	//
}

void PointLightRenderPath::Render(uint32_t current_index)
{
	//device->BeginRenderPass({}, RenderPass::Clear::COLOR);

	device->BindPipeline(pipeline);
	device->BindDescriptorSet(Descriptor2::Set::SCENE, scene_set[current_index]);
	device->BindDescriptorSet(Descriptor2::Set::MATERIAL, material_set[current_index]);

	device->BindVertexBuffer(sphere_vbo);
	//device->Push(Shader::Type::VERTEX, 0, 0);
	//device->Push(Shader::Type::FRAGMENT, 4, 0);
	device->PushConstant(EngineConstants::OBJECT_INDEX, 3);
	device->PushConstant(EngineConstants::MATERIAL_INDEX, 0);
	device->Draw(0, sphere_vertex_count);

	//device->EndRenderPass({});
}


BF_END_NAMESPACE
