#include "engine/resource_manager.hpp"
#include "entities/transform.hpp"
#include "graphics/opengl/render_device_gl.hpp"
#include "graphics/render_paths/debug_render_path.hpp"
#include "graphics/render_paths/point_light_render_path.hpp"
#include "graphics/vulkan/render_device_vk.hpp"
#include "graphics/render_paths/deferred_render_path.hpp"
#include "io/file.hpp"
#include "math/matrix.hpp"
#include "platform/window_sdl2.hpp"
#include "core/log.hpp"
#include "ui/font.hpp"
#include "utils/utf8.hpp"
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_timer.h>
#include <fmt/format.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/projection.hpp>
#include <vector>

using namespace bf;

struct Vertex3D
{
	float x;
	float y;
	float z;
};

std::vector<Vertex3D> GenerateGrid(float size, float step)
{
	float grid_half_size = size / 2.0f;
	std::vector<Vertex3D> verts;
	verts.reserve(size_t(size) / 16 * 4 + 4);

	for (int i = -grid_half_size; i <= grid_half_size; i += 1)
	{
		float fi = i;

		if (i == 0)
			continue;

		verts.push_back({ fi, 0.0f,  grid_half_size });
		verts.push_back({ fi, 0.0f, -grid_half_size });

		verts.push_back({ -grid_half_size, 0.0f, fi });
		verts.push_back({  grid_half_size, 0.0f, fi });
	}

	verts.push_back({ -grid_half_size, 0.0f, 0.0f });
	verts.push_back({  grid_half_size, 0.0f, 0.0f });

	verts.push_back({ 0.0f, 0.0f,  grid_half_size });
	verts.push_back({ 0.0f, 0.0f, -grid_half_size });

	//Mesh mesh;
	//mesh.vbo = device->CreateBuffer(GPUBuffer::Type::VERTEX, verts);

	/*uint32_t grid_vert_count = verts.size();
	mesh.surfaces = {
		{ {}, 0, grid_vert_count - 4 },
		{ {}, grid_vert_count - 4, 2 },
		{ {}, grid_vert_count - 2, 2 }
	};*/

	return verts;
}

/*std::vector<Vertex3D> generate_sphere()
{
	float R = 0.5f;
	int sector_count = 8;
	int stack_count = 8;
	float PI = glm::pi<float>();
	float sector_step = 2 * PI / float(sector_count);
	float stack_step = PI / float(stack_count);

	for(int i = 0; i <= sector_count; i++)
	{
		//

		for(int j = 0; j <= sector_count; j++)
		{

		}
	}
}*/

uint32_t FOUR_CC(std::string_view string)
{
	return string[0] | (string[1] << 8) | (string[2] << 16) | (string[3] << 24);
}

int main()
{
	Log::Init(Log::Destination::STDOUT);
	Config cfg;
	cfg.window.swap_interval = 1;
	cfg.render.api = Config::Render::API::VK;
	if (!cfg.Load())
		cfg.Save();

	WindowSDL3 wnd(&cfg);
	if (!wnd.Create())
		return 0;

	FileSystem fs;
	if (!fs.Create())
		return 0;

	RenderDeviceVK device2(&cfg, &fs);
	device2.Create(wnd.WindowHandle());

	ResourceManager resources(&device2, &fs);

	Shader vs_flip = device2.LoadShader(Shader::Type::VERTEX, "vk_flip");
	Shader fs_flip = device2.LoadShader(Shader::Type::FRAGMENT, "vk_flip");

	TextureDesc final_texture_desc
	{
		.width = cfg.window.width,
		.height = cfg.window.height,
		.format = Texture::Format::RGBA8,
		.usage = Texture::Usage::COLOR_ATTACHMENT | Texture::Usage::SHADER_READ,
		.levels = 1,
		.pixels = nullptr,
		.generate_mipmaps = false,
	};

	Texture flip_texture = device2.CreateTexture("Flip Texture", final_texture_desc);

	FramebufferDesc final_fbo_desc
	{
		.width = cfg.window.width,
		.height = cfg.window.height,
		.color_textures = { flip_texture },
		.depth_texture = device2.GetDepthTexture(),
	};

	FramebufferID final_fbo = device2.CreateFramebuffer(final_fbo_desc);

	PipelineDesc pipeline_flip_desc
	{
		.shaders = { vs_flip, fs_flip },
		.topology = Topology::TRIANGLES,
		.vertex_attribs = Vertex::Attrib::POSITION | Vertex::Attrib::TEXCOORD_0,
		.raster = {
			.blend = Blend::NONE,
			.depth_test = false,
			.depth_write = false,
		},
		.framebuffer_id = {},
	};

	glm::mat4 ortho = glm::ortho(0.0f, float(cfg.window.width), float(cfg.window.height), 0.0f);
	GPUBuffer ortho_ubo = device2.CreateBuffer(GPUBuffer::UNIFORM, sizeof(glm::mat4));
	device2.UpdateBuffer(ortho_ubo, sizeof(glm::mat4), glm::value_ptr(ortho), 0);

	PipelineID pipeline_flip = device2.CreatePipeline("Flip Pipeline", pipeline_flip_desc);
	DescriptorSet flip_scene_set = device2.CreateDescriptorSet(pipeline_flip, Descriptor2::Set::SCENE);
	DescriptorSet flip_material_set = device2.CreateDescriptorSet(pipeline_flip, Descriptor2::Set::MATERIAL);
	device2.WriteDescriptor(flip_scene_set, 0, ortho_ubo);
	device2.WriteDescriptor(flip_material_set, 0, flip_texture);

	Shader vs4 = device2.LoadShader(Shader::Type::VERTEX, "ui/vk_texture");
	Shader fs4 = device2.LoadShader(Shader::Type::FRAGMENT, "ui/vk_texture");

	PipelineDesc desc4
	{
		.shaders = { vs4, fs4 },
		.topology = Topology::TRIANGLES,
		.vertex_attribs = Vertex::Attrib::POSITION | Vertex::Attrib::TEXCOORD_0,
		.raster = {
			.blend = Blend::ALPHA,
			.depth_test = false,
			.depth_write = false,
		},
		.framebuffer_id = final_fbo,
	};
	PipelineID pipeline_ui = device2.CreatePipeline("ui", desc4);


	auto grid_verts = GenerateGrid(32.0f, 2.0f);
	GPUBuffer grid_vbo = device2.CreateBuffer(GPUBuffer::VERTEX, grid_verts);
	//GPUBuffer grid_vbo = device2.CreateBuffer(GPUBuffer::VERTEX, sizeof(Vertex3D) * grid_verts.size());
	//device2.UpdateBuffer(grid_vbo, sizeof(Vertex3D) * grid_verts.size(), grid_verts.data(), 0);


	float width = cfg.window.width;
	float height = cfg.window.height;

	std::vector<float> quad_verts
	{
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, height, 0.0f, 0.0f, 1.0f,
		width, 0.0f, 0.0, 1.0f, 0.0f,

		width, 0.0f, 0.0, 1.0f, 0.0f,
		0.0f, height, 0.0f, 0.0f, 1.0f,
		width, height, 0.0, 1.0f, 1.0f,
	};

	GPUBuffer quad_vbo = device2.CreateBuffer(GPUBuffer::VERTEX, quad_verts);

	Transform view_transform;
	view_transform.pos = glm::vec3(5.0f, 4.0f, 10.0f);
	view_transform.rot = glm::quat(glm::vec3(glm::radians(-30.0f), glm::radians(30.0f), 0.0f));
	glm::mat4 proj = glm::perspectiveFovZO(glm::radians(80.0f), float(width), float(height), 0.1f, 100.0f);
	//proj[1][1] *= -1;

	GPUBuffer camera_ubo = device2.CreateBuffer(GPUBuffer::UNIFORM, sizeof(glm::mat4) * 2);
	device2.UpdateBuffer(camera_ubo, sizeof(glm::mat4), glm::value_ptr(proj), 0);

	//ResourceManager resources(&device2);
	//Texture tex = resources.LoadTexture("test.png");
	//device2.CreateDescriptor(Descriptor::Set::MATERIAL, 0, tex);
	//uint32_t material_set = device2.CreateDescriptorSet(pipeline2, Descriptor2::Set::MATERIAL);
	//device2.WriteDescriptor(pipeline2, material_set, 0, tex);

	std::vector<glm::mat4> matrices(32, glm::mat4(1.0f));
	matrices[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -4.0f, 0.0f));
	GPUBuffer matrices_ubo = device2.CreateBuffer(GPUBuffer::UNIFORM, matrices);

	/*uint32_t scene_set = device2.CreateDescriptorSet(pipeline2, Descriptor2::Set::SCENE);
	device2.WriteDescriptor(pipeline2, scene_set, 0, camera_ubo);
	device2.WriteDescriptor(pipeline2, scene_set, 1, matrices_ubo);*/

	std::vector<glm::vec4> colors
	{
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
	};

	GPUBuffer colors_ubo = device2.CreateBuffer(GPUBuffer::UNIFORM, colors);

	std::vector<glm::vec4> point_lights
	{
		{ 0.0f, 0.0f, 0.0f, 8.0f },
	};

	GPUBuffer point_lights_ubo = device2.CreateBuffer(GPUBuffer::UNIFORM, point_lights);
	GPUBuffer camera_pos_ubo = device2.CreateBuffer(GPUBuffer::UNIFORM, sizeof(glm::vec4) + sizeof(glm::mat4) * 2);

	std::vector<Mesh> meshes;

	GraphicsContext graphics_context
	{
		.active_camera_ubo = camera_ubo,
		.model_matrices_ubo = matrices_ubo,
		.colors_ubo = colors_ubo,
		.point_lights_ubo = point_lights_ubo,
		.camera_pos_ubo = camera_pos_ubo,
	};
	Deferred deferred(&device2, &cfg, &resources);
	deferred.Create(&graphics_context);
	//device2.SetDepthTexture(deferred.GetDepthTexture());
	device2.SetTrackedResource(device2.GetDepthTexture());

	PointLightRenderPath point_light_rp(&device2, &cfg, &resources);
	point_light_rp.Create(&graphics_context, deferred.GetColorTextures(), deferred.GetDepthTexture(), final_fbo);

	Debug debug(&device2, &cfg, &resources);
	debug.Create(&graphics_context, final_fbo);

	meshes.push_back(resources.LoadMesh("cubes.bin"));

	Font font;
	Texture font_tex = resources.LoadTexture(font.TextureName());
	font.SetTextureScale(1.0f / 512.0f);
	DescriptorSet ui_scene_set = device2.CreateDescriptorSet(pipeline_ui, Descriptor2::Set::SCENE);
	DescriptorSet ui_material_set = device2.CreateDescriptorSet(pipeline_ui, Descriptor2::Set::MATERIAL);
	device2.WriteDescriptor(ui_scene_set, 0, ortho_ubo);
	device2.WriteDescriptor(ui_scene_set, 1, colors_ubo);
	device2.WriteDescriptor(ui_material_set, 0, font_tex);

	std::string text_string;
	uint32_t text_verts_count = 0;

	GPUBuffer text_vbo = device2.CreateBuffer(GPUBuffer::VERTEX, sizeof(float) * 5 * 6 * 100);
	//std::span<float> text_verts = device2.MapBuffer<float>(text_vbo);
	//text_verts_count = font.MakeString(utf8_view(text_string), text_verts);
	//device2.UnMapBuffer(text_vbo);

	//Shader vs5 = resources.LoadShader(Shader::Type::VERTEX, "forward/vk_combine_vert.glsl");
	//Shader fs5 = resources.LoadShader(Shader::Type::FRAGMENT, "forward/vk_combine_frag.glsl");
	Shader vs5 = device2.LoadShader(Shader::Type::VERTEX, "forward/vk_combine");
	Shader fs5 = device2.LoadShader(Shader::Type::FRAGMENT, "forward/vk_combine");
	PipelineDesc desc5
	{
		.shaders = { vs5, fs5 },
		.topology = Topology::TRIANGLES,
		.vertex_attribs = Vertex::Attrib::POSITION | Vertex::Attrib::TEXCOORD_0,
		.raster = {
			.blend = Blend::NONE,
			.depth_test = false,
			.depth_write = false,
		},
		.framebuffer_id = {},
	};
	PipelineID pipeline_final = device2.CreatePipeline("final", desc5);
	DescriptorSet scene_set_final = device2.CreateDescriptorSet(pipeline_final, Descriptor2::Set::SCENE);
	DescriptorSet material_set_final = device2.CreateDescriptorSet(pipeline_final, Descriptor2::Set::MATERIAL);
	device2.WriteDescriptor(scene_set_final, 0, ortho_ubo);
	device2.WriteDescriptor(material_set_final, 0, deferred.GetColorTexture(0));
	//device2.WriteDescriptor(material_set_final, 0, device2.GetFramebuffer(deferred.GetFramebuffer()).color_textures[0]);

	uint32_t start_time = 0;
	uint32_t end_time = 0;
	uint32_t max_time = 0;

	//device2.Test();
	Mesh grid_mesh { { { { 0, uint32_t(grid_verts.size()) }, nullptr, 3 } }, grid_vbo, 1 };
	std::vector<Mesh> meshes2;
	meshes2.push_back(grid_mesh);

	std::vector<Mesh> meshes3;
	meshes3.push_back(resources.LoadMesh("sphere.bin"));
	meshes3[0].matrix_index = 2;



	bool capture_mouse = true;
	wnd.CaptureMouse(capture_mouse);
	Input input;
	while (wnd.Update(input))
	{
		if (wnd.Minimized()) // Wrong
			continue;

		if (input.KeyJustPressed(SDL_SCANCODE_ESCAPE))
			wnd.Close();

		if (input.KeyJustPressed(SDL_SCANCODE_E))
		{
			capture_mouse = !capture_mouse;
			wnd.CaptureMouse(capture_mouse);
			// if not capture, move cursor to center?
		}

		float move_speed = 10.0f;
		float turn_speed = 5.0f;
		float dt = 1.0f / 60.0f;
		float speed_modifier = 1.0f;

		uint32_t KEY_MOVE_LEFT = SDL_SCANCODE_A;
		uint32_t KEY_MOVE_RIGHT = SDL_SCANCODE_D;
		uint32_t KEY_MOVE_FORWARD = SDL_SCANCODE_W;
		uint32_t KEY_MOVE_BACKWARD = SDL_SCANCODE_S;
		uint32_t KEY_MOVE_UP = SDL_SCANCODE_SPACE;
		uint32_t KEY_MOVE_DOWN = SDL_SCANCODE_LCTRL;
		uint32_t KEY_RUN = SDL_SCANCODE_LSHIFT;

		if (input.KeyPressed(KEY_RUN))
			speed_modifier = 2.0f;

		float dx = (input.KeyPressed(KEY_MOVE_RIGHT) - input.KeyPressed(KEY_MOVE_LEFT)) * move_speed * speed_modifier * dt;
		float dy = (input.KeyPressed(KEY_MOVE_UP) - input.KeyPressed(KEY_MOVE_DOWN)) * move_speed * dt;
		float dz = (input.KeyPressed(KEY_MOVE_BACKWARD) - input.KeyPressed(KEY_MOVE_FORWARD)) * move_speed * speed_modifier * dt;
		float yaw = input.MouseRelativePos().x * turn_speed * dt;
		float pitch = input.MouseRelativePos().y * turn_speed * dt;

		if (!input.IsKBM())
		{
			dx = input.LeftStick().x * move_speed * dt;
			dz = input.LeftStick().y * move_speed * dt;
			yaw = input.RightStick().x * turn_speed * dt * 20.0f;
			pitch = input.RightStick().y * turn_speed * dt * 20.0f;
		}

		if (capture_mouse)
		{
			glm::quat qx = glm::angleAxis(glm::radians(-yaw), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::quat qy = glm::angleAxis(glm::radians(-pitch), glm::vec3(1.0f, 0.0f, 0.0f));
			view_transform.rot = qx * view_transform.rot * qy;
		}
		view_transform.pos += view_transform.rot * glm::vec3(1.0f, 0.0f, 0.0f) * dx;
		view_transform.pos += view_transform.rot * glm::vec3(0.0f, 0.0f, 1.0f) * dz;
		view_transform.pos += glm::vec3(0.0f, dy, 0.0f);
		input.Flush();

		glm::mat4 view = glm::mat4_cast(glm::normalize(view_transform.rot));
		view[3] = glm::vec4(view_transform.pos, 1.0f);
		//glm::mat4 view2 = view;
		view = glm::inverse(view);
		//FastInverse(view);
		uint32_t stride = sizeof(glm::mat4);
		device2.UpdateBuffer(camera_ubo, stride, glm::value_ptr(view), stride);
		glm::vec4 temp_pos = glm::vec4(view_transform.pos, 1.0f);
		//glm::mat4 inv_proj_view = glm::inverse(proj * view);
		device2.UpdateBuffer(camera_pos_ubo, sizeof(glm::mat4), glm::value_ptr(glm::inverse(proj)), 0);
		device2.UpdateBuffer(camera_pos_ubo, sizeof(glm::mat4), glm::value_ptr(glm::inverse(view)), sizeof(glm::mat4));
		device2.UpdateBuffer(camera_pos_ubo, sizeof(glm::vec4), glm::value_ptr(temp_pos), sizeof(glm::mat4) * 2);

		// mouse picking

		glm::vec3 dir;
		if (capture_mouse)
		{
			dir = view_transform.rot * glm::vec3(0.0f, 0.0f, -1.0f);
		}
		else
		{
			glm::vec3 win_coords = glm::vec3(input.MousePos().x, height - input.MousePos().y, 1.0f);
			glm::vec4 viewport = glm::vec4(0.0f, 0.0f, width, height);
			glm::vec3 result = glm::unProject(win_coords, view, proj, viewport);
			dir = glm::normalize(result - view_transform.pos);
		}

		glm::vec3 sphere_pos(0.0f);
		glm::vec3 orig = view_transform.pos; //glm::vec3(10.0f, 10.0f, 10.0f);
		//glm::vec3 dir = glm::normalize(-orig);
		glm::vec3 plane_orig = glm::vec3(0.0f, -4.0f, 0.0f);
		glm::vec3 plane_normal = glm::vec3(0.0f, 1.0f, 0.0f);
		float dist;
		if (glm::intersectRayPlane(orig, dir, plane_orig, plane_normal, dist))
		{
			sphere_pos = orig + dir * dist;
			sphere_pos = glm::round(sphere_pos / 1.0f) * 1.0f;
		}

		glm::mat sphere_matrix = glm::translate(glm::mat4(1.0f), sphere_pos);
		device2.UpdateBuffer(matrices_ubo, sizeof(glm::mat4), glm::value_ptr(sphere_matrix), sizeof(glm::mat4) * 2);

		// begin rendering

		start_time = SDL_GetTicks();
		device2.BeginFrame();

		/*device2.LayoutTransition(deferred.GetColorTexture(0), ImageLayout::UNDEFINED, ImageLayout::COLOR_ATTACHMENT);
		device2.LayoutTransition(deferred.GetColorTexture(1), ImageLayout::UNDEFINED, ImageLayout::COLOR_ATTACHMENT);
		device2.LayoutTransition(deferred.GetColorTexture(2), ImageLayout::UNDEFINED, ImageLayout::COLOR_ATTACHMENT);*/
		for (auto texture: deferred.GetColorTextures())
			device2.LayoutTransition(texture, ImageLayout::UNDEFINED, ImageLayout::COLOR_ATTACHMENT);
		device2.LayoutTransition(deferred.GetDepthTexture(), ImageLayout::UNDEFINED, ImageLayout::DEPTH_STENCIL_ATTACHMENT);

		deferred.Render(meshes);

		/*device2.LayoutTransition(deferred.GetColorTexture(0), ImageLayout::COLOR_ATTACHMENT, ImageLayout::SHADER_READ_ONLY);
		device2.LayoutTransition(deferred.GetColorTexture(1), ImageLayout::COLOR_ATTACHMENT, ImageLayout::SHADER_READ_ONLY);
		device2.LayoutTransition(deferred.GetColorTexture(2), ImageLayout::COLOR_ATTACHMENT, ImageLayout::SHADER_READ_ONLY);*/
		for (auto texture: deferred.GetColorTextures())
			device2.LayoutTransition(texture, ImageLayout::COLOR_ATTACHMENT, ImageLayout::SHADER_READ_ONLY);
		device2.LayoutTransition(deferred.GetDepthTexture(), ImageLayout::DEPTH_STENCIL_ATTACHMENT, ImageLayout::DEPTH_READ);

		device2.LayoutTransition(flip_texture, ImageLayout::UNDEFINED, ImageLayout::COLOR_ATTACHMENT);
		device2.LayoutTransition({}, ImageLayout::UNDEFINED, ImageLayout::COLOR_ATTACHMENT);

		device2.BeginRenderPass(final_fbo, RenderPass::Clear::COLOR);

		point_light_rp.Render();

		/*device2.BindPipeline(pipeline_final);
		device2.BindDescriptorSet(Descriptor2::Set::SCENE, scene_set_final);
		device2.BindDescriptorSet(Descriptor2::Set::MATERIAL, material_set_final);
		device2.BindVertexBuffer(quad_vbo);
		device2.Draw(0, 6);*/

		//device2.LayoutTransition(deferred.GetDepthTexture(), ImageLayout::DEPTH_READ, ImageLayout::DEPTH_STENCIL_ATTACHMENT);

		meshes2.clear();
		debug.Render(meshes2, meshes3); // grid, sphere

		device2.BindPipeline(pipeline_ui);
		device2.BindDescriptorSet(Descriptor2::Set::SCENE, ui_scene_set);
		device2.BindDescriptorSet(Descriptor2::Set::MATERIAL, ui_material_set);
		device2.Push(Shader::Type::FRAGMENT, 4, 3);

		std::span<float> text_verts = device2.MapBuffer<float>(text_vbo);
		//text_string = fmt::format("{} {} {} {}", view_transform.rot.x, view_transform.rot.y, view_transform.rot.z, view_transform.rot.w);
		text_verts_count = font.MakeString(utf8_view(text_string), text_verts);
		device2.UnMapBuffer(text_vbo);

		device2.BindVertexBuffer(text_vbo);
		device2.Draw(0, text_verts_count);

		device2.EndRenderPass(final_fbo);

		device2.LayoutTransition(flip_texture, ImageLayout::COLOR_ATTACHMENT, ImageLayout::SHADER_READ_ONLY);

		device2.BeginRenderPass({}, RenderPass::Clear::COLOR);
		device2.BindPipeline(pipeline_flip);
		device2.BindDescriptorSet(Descriptor2::Set::SCENE, flip_scene_set);
		device2.BindDescriptorSet(Descriptor2::Set::MATERIAL, flip_material_set);
		device2.BindVertexBuffer(quad_vbo);
		device2.Draw(0, 6);
		device2.EndRenderPass({});

		device2.LayoutTransition({}, ImageLayout::COLOR_ATTACHMENT, ImageLayout::PRESENT);

		if (!device2.EndFrame())
			break;

		SDL_Delay(1);
		end_time = SDL_GetTicks();
		if (end_time - start_time > 17) max_time++;
		text_string = fmt::format("frame_time = {}, max_time_count = {}", end_time - start_time, max_time);
		//if (input.KeyPressed(SDL_SCANCODE_E)) max_time = 0;
	}

	device2.Destroy();
	wnd.Destroy();

	return 0;

#if 0
	RenderDeviceGL device(&cfg);
	device.Create();

	ResourceManager resources(&device);
	Texture tex = resources.LoadTexture("test.png");
	device.CreateDescriptor(Uniform::Texture::DIFFUSE, tex);

	File vs_file("../../data/shaders/forward/line_vert.glsl");
	File fs_file("../../data/shaders/forward/line_frag.glsl");
	vs_file.Open();
	fs_file.Open();
	auto vs_source = vs_file.Read();
	auto fs_source = fs_file.Read();
	Shader vs = device.CreateShader(Shader::Type::VERTEX, vs_source);
	Shader fs = device.CreateShader(Shader::Type::FRAGMENT, fs_source);

	PipelineDesc desc
	{
		.shaders = { vs, fs },
		.topology = Topology::TRIANGLE_STRIP,
		.vertex_attribs = Vertex::Attrib::POSITION | Vertex::Attrib::TEXCOORD_0,
		.raster = {},
	};
	Pipeline pipeline = device.CreatePipeline(desc);

	std::vector<float> verts
	{
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0, 1.0f, 1.0f,
	};

	std::vector<uint32_t> indices
	{
		0, 1, 2, 3,
	};

	GPUBuffer vbo = device.CreateBuffer(GPUBuffer::VERTEX, verts);
	GPUBuffer ibo = device.CreateBuffer(GPUBuffer::INDEX, indices);

	glm::mat4 proj = glm::perspective(glm::radians(80.0f), 16.0f / 9.0f, 0.1f, 100.0f);

	uint64_t current_time = SDL_GetTicks64();
	float fps = 1.0 / 60.0;
	float acc = 0.0;

	MotionState state;
	state.Reserve(32);
	std::vector<glm::mat4> matrices(32);
	//matrices[0] = glm::perspective(glm::radians(80.0f), 16.0f / 9.0f, 0.1f, 100.0f);

	GPUBuffer camera_ubo = device.CreateBuffer(GPUBuffer::UNIFORM, sizeof(glm::mat4) * 2);
	device.UpdateBuffer(camera_ubo, sizeof(proj), glm::value_ptr(proj));

	GPUBuffer matrices_ubo = device.CreateBuffer(GPUBuffer::UNIFORM, sizeof(glm::mat4) * matrices.size());
	//device.UpdateBuffer(matrices_ubo, sizeof(proj), glm::value_ptr(proj));

	//size_t view_index = state.Allocate();
	/*Transform &view_transform = state.GetTransform(view_index);
	view_transform.pos = glm::vec3(0.0f, 0.0f, 4.0f);*/

	size_t model_index = state.Allocate();
	//state.GetTransform(model_index).pos.y += 1.0f;


	//bool capture = false;

	//PlayerController controller(wnd.KeyboardState());
	Gameplay gameplay;
	//gameplay.state = &state;
	//gameplay.keyboard_state = wnd.KeyboardState();
	//gameplay.view_index = view_index;
	gameplay.Create();

	state.NextFrame();
	wnd.CaptureMouse(true);

	//gameplay.input.BindAction(SDL_SCANCODE_ESCAPE, [&wnd](){ wnd.Close(); });

	/*std::vector<int> v { 1, 2, 4, 5, 6, 7 };
	auto it = std::lower_bound(v.begin(), v.end(), 3);
	//v.erase(std::remove(v.begin(), v.end(), 3));
	if (*it == 3)
		Log() << *it;*/

	while (wnd.Update(gameplay.input))
	{
		if (gameplay.input.KeyJustPressed(SDL_SCANCODE_ESCAPE))
			wnd.Close();

		uint64_t new_time = SDL_GetTicks64();
		uint64_t frame_time = new_time - current_time;

		//if (frame_time > 1.0 / 30.0) // min fps?
		//	frame_time = 1.0 / 30.0;

		current_time = new_time;
		acc += frame_time;

		while (acc >= fps)
		{
			state.NextFrame();
			gameplay.FixedUpdate(fps);
			//gameplay.input.Flush();
			//controller.Update(state.GetTransform(view_index));

			acc -= fps;
		}

		gameplay.Update(fps);
		gameplay.input.Flush();

		state.InterpolateTo(acc / fps, { matrices.begin(), matrices.end() });
		glm::mat4 view = glm::mat4_cast(glm::normalize(gameplay.view_transform.rot));
		view[3] = glm::vec4(gameplay.view_transform.pos, 1.0f);
		FastInverse(view);
		//FastInverse(matrices[gameplay.view_index]);

		uint32_t stride = sizeof(glm::mat4);
		device.UpdateBuffer(camera_ubo, stride, glm::value_ptr(view), stride);
		device.UpdateBuffer(matrices_ubo, matrices);

		device.BeginRenderPass({ glm::ivec2 {}, wnd.Size() }, RenderPass::Clear::COLOR_DEPTH);
		device.BindPipeline(pipeline);
		device.SetUniform(Uniform::Buffer::CAMERA, camera_ubo);
		device.SetUniform(Uniform::Buffer::MATRICES, matrices_ubo);
		device.SetUniform(Uniform::Name::INDEX_MODEL, model_index);
		device.BindDescriptors(0, 1);
		device.BindVertexBuffer(vbo);
		device.BindIndexBuffer(ibo);
		//device.Draw(0, 4);
		device.DrawIndexed(0, 4);
		device.EndRenderPass();

		wnd.Swap();
	}

	wnd.Destroy();
	return 0;
#endif
}
