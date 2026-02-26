#include "engine/resource_manager.hpp"
#include "entities/transform.hpp"
#include "graphics/geometry.hpp"
#include "graphics/opengl/render_device_gl.hpp"
#include "graphics/render_paths/debug_render_path.hpp"
#include "graphics/render_paths/point_light_render_path.hpp"
#include "graphics/vulkan/vk_render_device.hpp"
#include "graphics/render_paths/deferred_render_path.hpp"
#include "io/file.hpp"
#include "math/matrix.hpp"
#include "platform/window_sdl2.hpp"
#include "core/log.hpp"
#include "ui/font.hpp"
#include "utils/utf8.hpp"
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_mouse.h>
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

uint32_t FOUR_CC(std::string_view string)
{
	return string[0] | (string[1] << 8) | (string[2] << 16) | (string[3] << 24);
}

struct PointLightCameraData
{
	glm::mat4 inv_proj;
	glm::mat4 inv_view;
	glm::vec4 camera_pos;
};

struct CameraMatrices
{
	glm::mat4 proj;
	glm::mat4 view;
};

int main()
{
	Log::Init(Log::Destination::STDOUT, Log::Level::WARN);
	Config config;
	config.window.swap_interval = 1;
	config.render.api = Config::Render::API::VK;
	if (!config.Load())
		config.Save();

	WindowSDL3 wnd(&config);
	if (!wnd.Create())
		return 0;

	FileSystem fs;
	if (!fs.Create())
		return 0;

	const char *flip_shader_name = config.render.api == Config::Render::API::VK ? "vk_flip" : "gl_flip";
	const char *ui_texture_shader_name = config.render.api == Config::Render::API::VK ? "ui/vk_texture" : "ui/gl_texture";

	RenderDeviceVK *device = new RenderDeviceVK(&config, &fs);
	/*switch (config.render.api)
	{
		case Config::Render::API::VK: device = new RenderDeviceVK(&config, &fs); break;
		case Config::Render::API::GL: device = new RenderDeviceGL(&config, &fs); break;
	}*/

	device->Create(wnd.WindowHandle());

	ResourceManager resources(device, &fs);
	//resources.LoadKTX2("wall/gotbwall4_d.ktx2");

	TextureDesc color_desc
	{
		.width = config.window.width,
		.height = config.window.height,
		.format = Texture::Format::RGBA16F,
		.usage = Texture::Usage::COLOR_ATTACHMENT | Texture::Usage::SHADER_READ,
		.levels = 1,
		.pixels = nullptr,
		.generate_mipmaps = false,
	};

	TextureDesc depth_desc
	{
		.width = config.window.width,
		.height = config.window.height,
		.format = Texture::Format::D24S8,
		.usage = Texture::Usage::DEPTH_ATTACHMENT | Texture::Usage::SHADER_READ,
		.levels = 1,
		.pixels = nullptr,
		.generate_mipmaps = false,
	};

	/*std::vector<Texture> gbuffer_textures
	{
		device->CreateTexture("Render Target 0", color_desc),
		device->CreateTexture("Render Target 1", color_desc),
		device->CreateTexture("Render Target 2", color_desc),
	};

	//Texture gbuffer_depth = device->GetDepthTexture();
	Texture gbuffer_depth = device->CreateTexture("Render Target Depth", depth_desc);*/

	std::vector<glm::mat4> matrices(32, glm::mat4(1.0f));
	matrices[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -4.03f, 0.0f)); // TODO: depth bias

	std::vector<glm::vec4> colors
	{
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
	};

	std::vector<glm::vec4> point_lights
	{
		{ 0.0f, 0.0f, 0.0f, 16.0f },
	};

	std::vector<GraphicsContext> graphics_context(device->GetFrameCount());

	uint32_t frame_index = 0;
	for (auto &context: graphics_context)
	{
		context.active_camera_ubo = device->CreateBuffer(GPUBuffer::UNIFORM, sizeof(glm::mat4) * 2);
		context.model_matrices_ubo = device->CreateBuffer(GPUBuffer::UNIFORM, matrices);
		context.colors_ubo = device->CreateBuffer(GPUBuffer::UNIFORM, colors);
		context.point_lights_ubo = device->CreateBuffer(GPUBuffer::UNIFORM, point_lights);
		context.camera_light_data = device->CreateBuffer(GPUBuffer::UNIFORM, sizeof(PointLightCameraData) * 1);

		context.gbuffer_textures.resize(3);
		context.gbuffer_textures[0] = device->CreateTexture(fmt::format("Render Target 0 frame {}", frame_index), color_desc);
		context.gbuffer_textures[1] = device->CreateTexture(fmt::format("Render Target 1 frame {}", frame_index), color_desc);
		context.gbuffer_textures[2] = device->CreateTexture(fmt::format("Render Target 2 frame {}", frame_index), color_desc);
		context.gbuffer_depth = device->CreateTexture(fmt::format("Render Target Depth frame {}", frame_index), depth_desc);

		FramebufferDesc framebuffer_desc
		{
			.width = config.window.width,
			.height = config.window.height,
			.color_textures = context.gbuffer_textures,
			.depth_texture = context.gbuffer_depth,
		};

		context.gbuffer = device->CreateFramebuffer(framebuffer_desc);

		context.final_texture = device->CreateTexture(fmt::format("Final Render Target frame {}", frame_index), color_desc);

		FramebufferDesc final_fbo_desc
		{
			.width = config.window.width,
			.height = config.window.height,
			.color_textures = { context.final_texture },
			.depth_texture = context.gbuffer_depth,
		};

		context.final_fbo = device->CreateFramebuffer(final_fbo_desc);

		context.text_vbo = device->CreateBuffer(GPUBuffer::VERTEX, sizeof(float) * 5 * 6 * 100);
	}



	//FramebufferID gbuffer = device->CreateFramebuffer(framebuffer_desc);

	Shader vs_flip = device->LoadShader(Shader::Type::VERTEX, flip_shader_name);
	Shader fs_flip = device->LoadShader(Shader::Type::FRAGMENT, flip_shader_name);

	TextureDesc final_texture_desc
	{
		.width = config.window.width,
		.height = config.window.height,
		.format = Texture::Format::RGBA16F,
		.usage = Texture::Usage::COLOR_ATTACHMENT | Texture::Usage::SHADER_READ,
		.levels = 1,
		.pixels = nullptr,
		.generate_mipmaps = false,
	};

	/*Texture flip_texture = device->CreateTexture("Flip Texture", final_texture_desc);

	FramebufferDesc final_fbo_desc
	{
		.width = config.window.width,
		.height = config.window.height,
		.color_textures = { flip_texture },
		.depth_texture = gbuffer_depth,
	};

	FramebufferID final_fbo = device->CreateFramebuffer(final_fbo_desc);*/

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

	glm::mat4 ortho;
	switch (config.render.api)
	{
		case Config::Render::API::VK: ortho = glm::ortho(0.0f, float(config.window.width), 0.0f, float(config.window.height)); break;
		case Config::Render::API::GL: ortho = glm::ortho(0.0f, float(config.window.width), float(config.window.height), 0.0f); break;
	}

	//glm::mat4 ortho = glm::ortho(0.0f, float(config.window.width), 0.0f, float(config.window.height));
	//glm::mat4 ortho = glm::ortho(0.0f, float(config.window.width), float(config.window.height), 0.0f);
	//ortho = glm::ortho(0.0f, float(config.window.width), 0.0f, float(config.window.height));
	GPUBuffer ortho_ubo = device->CreateBuffer(GPUBuffer::UNIFORM, sizeof(glm::mat4));
	device->UpdateBuffer(ortho_ubo, sizeof(glm::mat4), glm::value_ptr(ortho), 0);

	PipelineID pipeline_flip = device->CreatePipeline("Flip Pipeline", pipeline_flip_desc);
	DescriptorSet flip_scene_set[3];
	DescriptorSet flip_material_set[3];
	for (uint32_t i = 0; i < 3; i++)
	{
		flip_scene_set[i] = device->CreateDescriptorSet(pipeline_flip, Descriptor2::Set::SCENE);
		flip_material_set[i] = device->CreateDescriptorSet(pipeline_flip, Descriptor2::Set::MATERIAL);
		device->WriteDescriptor(flip_scene_set[i], 0, ortho_ubo);
		device->WriteDescriptor(flip_material_set[i], 0, graphics_context[i].final_texture);
	}
	/*DescriptorSet flip_scene_set = device->CreateDescriptorSet(pipeline_flip, Descriptor2::Set::SCENE);
	DescriptorSet flip_material_set = device->CreateDescriptorSet(pipeline_flip, Descriptor2::Set::MATERIAL);
	device->WriteDescriptor(flip_scene_set, 0, ortho_ubo);
	device->WriteDescriptor(flip_material_set, 0, flip_texture);*/

	Shader vs4 = device->LoadShader(Shader::Type::VERTEX, ui_texture_shader_name);
	Shader fs4 = device->LoadShader(Shader::Type::FRAGMENT, ui_texture_shader_name);

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
		.framebuffer_id = {},
	};
	PipelineID pipeline_ui = device->CreatePipeline("ui", desc4);


	auto grid_verts = GenerateGrid(32.0f, 2.0f);
	GPUBuffer grid_vbo = device->CreateBuffer(GPUBuffer::VERTEX, grid_verts);
	//GPUBuffer grid_vbo = device->CreateBuffer(GPUBuffer::VERTEX, sizeof(Vertex3D) * grid_verts.size());
	//device->UpdateBuffer(grid_vbo, sizeof(Vertex3D) * grid_verts.size(), grid_verts.data(), 0);


	float width = config.window.width;
	float height = config.window.height;

	std::vector<float> quad_verts
	{
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, height, 0.0f, 0.0f, 1.0f,
		width, 0.0f, 0.0, 1.0f, 0.0f,

		width, 0.0f, 0.0, 1.0f, 0.0f,
		0.0f, height, 0.0f, 0.0f, 1.0f,
		width, height, 0.0, 1.0f, 1.0f,
	};

	GPUBuffer quad_vbo = device->CreateBuffer(GPUBuffer::VERTEX, quad_verts);

	Transform view_transform;
	view_transform.pos = glm::vec3(5.0f, 4.0f, 10.0f);
	view_transform.rot = glm::quat(glm::vec3(glm::radians(-30.0f), glm::radians(30.0f), 0.0f));
	//glm::mat4 proj = glm::perspectiveFovZO(glm::radians(80.0f), float(width), float(height), 0.1f, 100.0f);
	glm::mat4 proj = glm::perspectiveFovZO(glm::radians(80.0f), float(width), float(height), 0.1f, 100.0f);
	if (config.render.api == Config::Render::API::VK)
		proj[1][1] *= -1;

	GPUBuffer camera_ubo = device->CreateBuffer(GPUBuffer::UNIFORM, sizeof(glm::mat4) * 2);
	device->UpdateBuffer(camera_ubo, sizeof(glm::mat4), glm::value_ptr(proj), 0);


	//GPUBuffer matrices_ubo = device->CreateBuffer(GPUBuffer::UNIFORM, matrices);




	//GPUBuffer colors_ubo = device->CreateBuffer(GPUBuffer::UNIFORM, colors);

	//GPUBuffer point_lights_ubo = device->CreateBuffer(GPUBuffer::UNIFORM, point_lights);
	//GPUBuffer camera_pos_ubo = device->CreateBuffer(GPUBuffer::UNIFORM, sizeof(PointLightCameraData));

	std::vector<Mesh> meshes;

	/*GraphicsContext graphics_context
	{
		.active_camera_ubo = camera_ubo,
		.model_matrices_ubo = matrices_ubo,
		.colors_ubo = colors_ubo,
		.point_lights_ubo = point_lights_ubo,
		.camera_pos_ubo = camera_pos_ubo,
	};*/
	Deferred deferred(device, &config, &resources);
	deferred.Create(graphics_context, graphics_context[0].gbuffer);

	PointLightRenderPath point_light_rp(device, &config, &resources);
	point_light_rp.Create(graphics_context, /*gbuffer_textures, gbuffer_depth,*/ graphics_context[0].final_fbo);

	Debug debug(device, &config, &resources);
	debug.Create(graphics_context, graphics_context[0].final_fbo);

	meshes.push_back(resources.LoadMesh("cubes.bin"));

	Font font;
	Texture font_tex = resources.LoadTexture(font.TextureName());
	font.SetTextureScale(1.0f / 512.0f);
	DescriptorSet ui_scene_set[3];
	DescriptorSet ui_material_set[3];
	for (uint32_t i = 0; i < 3; i++)
	{
		ui_scene_set[i] = device->CreateDescriptorSet(pipeline_ui, Descriptor2::Set::SCENE);
		ui_material_set[i] = device->CreateDescriptorSet(pipeline_ui, Descriptor2::Set::MATERIAL);

		device->WriteDescriptor(ui_scene_set[i], 0, ortho_ubo);
		device->WriteDescriptor(ui_scene_set[i], 1, graphics_context[i].colors_ubo);
		device->WriteDescriptor(ui_material_set[i], 0, font_tex);
	}

	/*DescriptorSet ui_scene_set = device->CreateDescriptorSet(pipeline_ui, Descriptor2::Set::SCENE);
	DescriptorSet ui_material_set = device->CreateDescriptorSet(pipeline_ui, Descriptor2::Set::MATERIAL);
	device->WriteDescriptor(ui_scene_set, 0, ortho_ubo);
	device->WriteDescriptor(ui_scene_set, 1, colors_ubo);
	device->WriteDescriptor(ui_material_set, 0, font_tex);*/

	std::string text_string;
	uint32_t text_verts_count = 0;
	//GPUBuffer text_vbo = device->CreateBuffer(GPUBuffer::VERTEX, sizeof(float) * 5 * 6 * 100);

	uint32_t start_time = 0;
	uint32_t end_time = 0;
	uint32_t max_time = 0;

	//device->Test();
	Mesh grid_mesh { "grid_mesh", { { { 0, uint32_t(grid_verts.size()) }, nullptr, 3 } }, grid_vbo, 1 };
	std::vector<Mesh> meshes2;
	meshes2.push_back(grid_mesh);

	std::vector<Mesh> meshes3;
	meshes3.push_back(resources.LoadMesh("sphere.bin"));
	meshes3[0].matrix_index = 2;

	enum class EditingMode
	{
		WAIT,
		DRAW,
	};

	EditingMode editing_mode = EditingMode::WAIT;
	glm::vec3 pos[2];
	glm::vec3 sphere_pos(0.0f);

	GPUBuffer editing_vbo = device->CreateBuffer(GPUBuffer::VERTEX, sizeof(float) * (3 + 2 + 3 + 4) * 512);
	std::vector<std::array<NormalMappedVertex, 6>> walls;
	//std::array<glm::vec3, 2> pos;
	//walls.push_back(MakeWall({{ { -8.0f, -4.0f, 8.0f, }, { -8.0f, -4.0f, -8.0f, } }}));
	//device->UpdateBuffer(editing_vbo, sizeof(NormalMappedVertex) * 6 * walls.size(), walls.data(), 0);
	// next 2 lines is working
	//Surface wall_surf { { 0, 6 * uint32_t(walls.size()) }, resources.LoadMaterial("wall/gotbwall4"), 0, device->CreateDescriptorSet(deferred.pipeline, Descriptor2::Set::MATERIAL) };
	//std::static_pointer_cast<CustomMaterial>(wall_surf.material)->Setup2(device, &graphics_context, Descriptor2::Set::MATERIAL, wall_surf.descriptor_set);

	uint32_t editing_wall_index = 0;

	bool capture_mouse = false;
	wnd.CaptureMouse(capture_mouse);
	Input input;
	while (wnd.Update(input))
	{
		if (wnd.Minimized()) // Wrong
			continue;

		if (input.KeyJustPressed(SDL_SCANCODE_ESCAPE))
			wnd.Close();

		if (input.MouseButtonJustPressed(SDL_BUTTON_RIGHT))
		{
			capture_mouse = !capture_mouse;
			wnd.CaptureMouse(capture_mouse);
			// if not capture, move cursor to center?
		}

		if (input.MouseButtonJustPressed(SDL_BUTTON_LEFT))
		{
			if (editing_mode == EditingMode::WAIT)
			{
				// begin draw
				pos[0] = pos[1] = sphere_pos;
				walls.push_back({});
				//wall_surf.vertex_range.count = walls.size() * 6;

				editing_mode = EditingMode::DRAW;
			}

			else if (editing_mode == EditingMode::DRAW)
			{
				// complete draw
				editing_wall_index++;

				editing_mode = EditingMode::WAIT;
			}
		}

		if (editing_mode == EditingMode::DRAW)
		{
			pos[1] = sphere_pos;

			if (glm::dot(pos[1] - pos[0], view_transform.rot * glm::vec3(1.0f, 0.0f, 0.0f)) < 0)
				walls[editing_wall_index] = MakeWall({{ pos[1], pos[0] }});

			else
				walls[editing_wall_index] = MakeWall({{ pos[0], pos[1] }});

			//device->UpdateBuffer(editing_vbo, sizeof(NormalMappedVertex) * 6 * walls.size(), walls.data(), 0);
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
		float dz = (input.KeyPressed(KEY_MOVE_FORWARD) - input.KeyPressed(KEY_MOVE_BACKWARD)) * move_speed * speed_modifier * dt;
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
		view_transform.pos += view_transform.rot * glm::vec3(0.0f, 0.0f, -1.0f) * dz;
		view_transform.pos += glm::vec3(0.0f, dy, 0.0f);
		input.Flush();

		glm::mat4 view = glm::mat4_cast(glm::normalize(view_transform.rot));
		view[3] = glm::vec4(view_transform.pos, 1.0f);
		//glm::mat4 view2 = view;
		view = glm::inverse(view);
		//FastInverse(view);
		uint32_t stride = sizeof(glm::mat4);

		//glm::vec4 temp_pos = glm::vec4(view_transform.pos, 1.0f);

		PointLightCameraData point_light_camera_data
		{
			.inv_proj = glm::inverse(proj),
			.inv_view = glm::inverse(view),
			.camera_pos = glm::vec4(view_transform.pos, 1.0f),
			//.inv_viewport = glm::vec2(1.0f / float(config.window.width), 1.0f / float(config.window.height)),
		};

		CameraMatrices camera_matrices
		{
			.proj = proj,
			.view = view,
		};

		GraphicsContext *context = &graphics_context.at(device->GetFrameIndex());

		device->UpdateBuffer(context->active_camera_ubo, sizeof(CameraMatrices), &camera_matrices, 0);
		device->UpdateBuffer(context->camera_light_data, sizeof(PointLightCameraData), &point_light_camera_data, 0);

		// mouse picking

		glm::vec3 dir;
		if (capture_mouse)
		{
			dir = view_transform.rot * glm::vec3(0.0f, 0.0f, -1.0f);
		}
		else
		{
			//glm::vec3 win_coords = glm::vec3(input.MousePos().x, height - input.MousePos().y, 1.0f); // OpenGL
			glm::vec3 win_coords = glm::vec3(input.MousePos().x, input.MousePos().y, 1.0f); // Vulkan
			glm::vec4 viewport = glm::vec4(0.0f, 0.0f, width, height);
			glm::vec3 result = glm::unProject(win_coords, view, proj, viewport);
			dir = glm::normalize(result - view_transform.pos);
		}

		glm::vec3 orig = view_transform.pos; //glm::vec3(10.0f, 10.0f, 10.0f);
		//glm::vec3 dir = glm::normalize(-orig);
		glm::vec3 plane_orig = glm::vec3(0.0f, -4.0f, 0.0f);
		glm::vec3 plane_normal = glm::vec3(0.0f, 1.0f, 0.0f);
		float dist;
		if (glm::intersectRayPlane(orig, dir, plane_orig, plane_normal, dist))
		{
			sphere_pos = orig + dir * dist;
			sphere_pos = glm::round(sphere_pos / 2.0f) * 2.0f;
		}

		glm::mat sphere_matrix = glm::translate(glm::mat4(1.0f), sphere_pos);
		matrices[2] = sphere_matrix;
		device->UpdateBuffer(context->model_matrices_ubo, sizeof(glm::mat4) * matrices.size(), matrices.data(), 0);

		// begin rendering

		start_time = SDL_GetTicks();
		device->BeginFrame();

		device->SetCullMode(2); // 2

		device->LayoutTransition(context->gbuffer_textures[0], ImageLayout::UNDEFINED, ImageLayout::COLOR_ATTACHMENT);
		device->LayoutTransition(context->gbuffer_textures[1], ImageLayout::UNDEFINED, ImageLayout::COLOR_ATTACHMENT);
		device->LayoutTransition(context->gbuffer_textures[2], ImageLayout::UNDEFINED, ImageLayout::COLOR_ATTACHMENT);
		device->LayoutTransition(context->gbuffer_depth, ImageLayout::UNDEFINED, ImageLayout::DEPTH_STENCIL_ATTACHMENT);
		device->LayoutTransition(context->final_texture, ImageLayout::UNDEFINED, ImageLayout::COLOR_ATTACHMENT);
		device->LayoutTransition({}, ImageLayout::UNDEFINED, ImageLayout::COLOR_ATTACHMENT);

		device->BeginRenderPass(context->gbuffer, RenderPass::Clear::COLOR_DEPTH);
		deferred.Render(meshes, device->GetFrameIndex());

		/*device->BindVertexBuffer(editing_vbo);
		device->BindDescriptorSet(Descriptor2::Set::MATERIAL, wall_surf.descriptor_set);
		//device->Push(Shader::Type::VERTEX, 0, 0);
		device->PushConstant(0, 0);
		device->Draw(wall_surf.vertex_range.start, wall_surf.vertex_range.count);*/

		device->EndRenderPass(context->gbuffer);

		device->LayoutTransition(context->gbuffer_textures[0], ImageLayout::COLOR_ATTACHMENT, ImageLayout::COLOR_READ_ONLY);
		device->LayoutTransition(context->gbuffer_textures[1], ImageLayout::COLOR_ATTACHMENT, ImageLayout::COLOR_READ_ONLY);
		device->LayoutTransition(context->gbuffer_textures[2], ImageLayout::COLOR_ATTACHMENT, ImageLayout::COLOR_READ_ONLY);
		device->LayoutTransition(context->gbuffer_depth, ImageLayout::DEPTH_STENCIL_ATTACHMENT, ImageLayout::DEPTH_STENCIL_READ_ONLY);

		device->BeginRenderPass(context->final_fbo, RenderPass::Clear::COLOR);
		device->SetCullMode(1);
		point_light_rp.Render(device->GetFrameIndex());
		device->SetCullMode(2);

		//meshes2.clear();
		//meshes3.clear();
		//device->SetCullMode(2);
		debug.Render(meshes2, meshes3, device->GetFrameIndex()); // grid, sphere
		//device->SetCullMode(0);
		device->EndRenderPass(context->final_fbo);

		device->LayoutTransition(context->final_texture, ImageLayout::COLOR_ATTACHMENT, ImageLayout::COLOR_READ_ONLY);

		device->BeginRenderPass({}, RenderPass::Clear::COLOR);
		device->BindPipeline(pipeline_flip);
		device->BindDescriptorSet(Descriptor2::Set::SCENE, flip_scene_set[device->GetFrameIndex()]);
		device->BindDescriptorSet(Descriptor2::Set::MATERIAL, flip_material_set[device->GetFrameIndex()]);
		device->BindVertexBuffer(quad_vbo);
		device->Draw(0, 6);

		device->BindPipeline(pipeline_ui);
		device->BindDescriptorSet(Descriptor2::Set::SCENE, ui_scene_set[device->GetFrameIndex()]);
		device->BindDescriptorSet(Descriptor2::Set::MATERIAL, ui_material_set[device->GetFrameIndex()]);
		//device->Push(Shader::Type::FRAGMENT, 4, 3);
		device->PushConstant(0, 3); // slot index is 0 for fragment shader, do something about it?

		std::span<float> text_verts = device->MapBuffer<float>(context->text_vbo);
		//text_string = fmt::format("{} {} {} {}", view_transform.rot.x, view_transform.rot.y, view_transform.rot.z, view_transform.rot.w);
		text_verts_count = font.MakeString(utf8_view(text_string), text_verts);
		device->UnMapBuffer(context->text_vbo);

		device->BindVertexBuffer(context->text_vbo);
		//device->SetCullMode(0);
		device->Draw(0, text_verts_count);

		device->EndRenderPass({});

		device->LayoutTransition({}, ImageLayout::COLOR_ATTACHMENT, ImageLayout::PRESENT);
		//device->LayoutTransition({}, ImageLayout::UNDEFINED, ImageLayout::PRESENT);
		device->EndFrame();
		wnd.Swap();

		//SDL_Delay(1);
		end_time = SDL_GetTicks();
		if (end_time - start_time > 18) max_time++;
		text_string = fmt::format("frame_time = {}, max_time_count = {}", end_time - start_time, max_time);
		//if (input.KeyPressed(SDL_SCANCODE_E)) max_time = 0;
	}

	device->Destroy();
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
