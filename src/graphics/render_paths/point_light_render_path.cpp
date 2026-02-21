#include "point_light_render_path.hpp"

BF_BEGIN_NAMESPACE

PointLightRenderPath::PointLightRenderPath(RenderDeviceVK *device, Config *config, ResourceManager *resources)
{
	this->device = device;
	this->config = config;
	this->resources = resources;
	this->width = config->window.width;
	this->height = config->window.height;
}

void PointLightRenderPath::Create(GraphicsContext *context, const std::vector<Texture> &textures)
{
	Shader vs = device->LoadShader(Shader::Type::VERTEX, "deferred/vk_point_light");
	Shader fs = device->LoadShader(Shader::Type::FRAGMENT, "deferred/vk_point_light");

	PipelineDesc pipeline_desc
	{
		.shaders = { vs, fs },
		.topology = Topology::TRIANGLES,
		.vertex_attribs = Vertex::Attrib::POSITION | Vertex::Attrib::TEXCOORD_0,
		.raster = {
			.blend = {},
			.depth_test = false,
			.depth_write = false,
		},
		.framebuffer_id = {},
	};

	pipeline = device->CreatePipeline("deferred/point_light", pipeline_desc);

	scene_set = device->CreateDescriptorSet(pipeline, Descriptor2::Set::SCENE);
	material_set = device->CreateDescriptorSet(pipeline, Descriptor2::Set::MATERIAL);

	device->WriteDescriptor(scene_set, 0, context->active_camera_ubo);
	device->WriteDescriptor(scene_set, 1, context->model_matrices_ubo);
	device->WriteDescriptor(scene_set, 2, context->point_lights_ubo);
	device->WriteDescriptor(scene_set, 3, context->camera_pos_ubo);

	device->WriteDescriptor(material_set, 0, textures[0]);
	device->WriteDescriptor(material_set, 1, textures[1]);
	device->WriteDescriptor(material_set, 2, textures[2]);
	device->WriteDescriptor(material_set, 3, textures[3]);

	/*std::vector<float> quad_verts
	{
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, height, 0.0f, 0.0f, 1.0f,
		width, 0.0f, 0.0, 1.0f, 0.0f,

		width, 0.0f, 0.0, 1.0f, 0.0f,
		0.0f, height, 0.0f, 0.0f, 1.0f,
		width, height, 0.0, 1.0f, 1.0f,
	};*/

	std::vector<float> quad_verts
	{
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0, 1.0f, 0.0f,

		1.0f, 1.0f, 0.0, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0, 1.0f, 1.0f,
	};

	quad_vbo = device->CreateBuffer(GPUBuffer::VERTEX, quad_verts);
}

void PointLightRenderPath::Destroy()
{
	//
}

void PointLightRenderPath::Render()
{
	//device->BeginRenderPass({}, RenderPass::Clear::COLOR);

	device->BindPipeline(pipeline);
	device->BindDescriptorSet(Descriptor2::Set::SCENE, scene_set);
	device->BindDescriptorSet(Descriptor2::Set::MATERIAL, material_set);

	device->BindVertexBuffer(quad_vbo);
	//device->Push(Shader::Type::VERTEX, 0, 0);
	device->Push(Shader::Type::FRAGMENT, 4, 0);
	device->Draw(0, 6);

	//device->EndRenderPass({});
}


BF_END_NAMESPACE
