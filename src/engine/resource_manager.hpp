#pragma once
#include "core/log.hpp"
#include "graphics/opengl/render_device_gl.hpp"
#include "graphics/render_device.hpp"
#include "graphics/render_paths/graphics_context.hpp"
#include "graphics/vulkan/vk_render_device.hpp"
#include "utils/parser.hpp"
#include <memory>
#include <string>

BF_BEGIN_NAMESPACE

class IMaterial
{
public:
	virtual ~IMaterial() = default;
	virtual void Setup(RenderDevice *device, DescriptorSet descriptor_set) = 0;
	virtual void Setup2(RenderDevice *device, GraphicsContext *context, Descriptor2::Set set_index, DescriptorSet descriptor_set) {}
};

class Material: public IMaterial
{
public:
	Material(Texture diffuse_map)
	{
		this->diffuse_map = diffuse_map;
	}

	void Setup(RenderDevice *device, DescriptorSet descriptor_set) override
	{
		device->WriteDescriptor(descriptor_set, 0, diffuse_map);
	}

private:
	Texture diffuse_map;
};

class PhongMaterial: public IMaterial
{
public:
	PhongMaterial(Texture diffuse_map, Texture normal_map, Texture specular_map)
	{
		this->diffuse_map = diffuse_map;
		this->normal_map = normal_map;
		this->specular_map = specular_map;
	}

	void Setup(RenderDevice *device, DescriptorSet descriptor_set) override
	{
		device->WriteDescriptor(descriptor_set, 0, diffuse_map, 0);
		device->WriteDescriptor(descriptor_set, 0, normal_map, 1);
		device->WriteDescriptor(descriptor_set, 0, specular_map, 2);
	}

private:
	Texture diffuse_map;
	Texture normal_map;
	Texture specular_map;
};



struct MaterialID: Handle {};



struct TextureInputDesc
{
	//std::string slot_name;
	Texture::Format format;
};

class CustomMaterial: public IMaterial
{
public:
	CustomMaterial(std::string name, const std::vector<Texture> &textures, uint32_t index)
	{
		this->textures = std::move(textures);
		this->name = name;
		this->index = index;
	}

	void Setup(RenderDevice *device, DescriptorSet descriptor_set) override
	{
		std::terminate();
	}

	void Setup2(RenderDevice *device, GraphicsContext *context, Descriptor2::Set set_index, DescriptorSet descriptor_set) override
	{
		// for (uint32_t i = 0; i < textures.size(); i++)
		// 	device->WriteDescriptor(descriptor_set, i, textures.at(i));

		for (uint32_t i = 0; i < textures.size(); i++)
			device->WriteDescriptor(descriptor_set, 0, textures.at(i), index + i);
	}

	uint32_t index;
	std::string name;

private:
	std::vector<Texture> textures;
};

struct Surface
{
	Range vertex_range {};
	std::shared_ptr<IMaterial> material {};
	uint32_t material_index = 0;
	DescriptorSet descriptor_set {};
	//uint32_t texture_index;
};

struct Mesh
{
	//Range surfaces {};
	std::string name;
	std::vector<Surface> surfaces;
	GPUBuffer vbo {};
	uint32_t matrix_index = 0;
};

class ResourceManager
{
public:
	ResourceManager(RenderDevice *device, FileSystem *fs);
	~ResourceManager();
	BF_NON_COPYABLE(ResourceManager)
	BF_NON_MOVABLE(ResourceManager)

	Texture	LoadKTX2(std::string_view filename);
	Texture LoadTexture(std::string_view filename, Texture::Format format = Texture::Format::SRGBA8);
	auto    LoadMaterial(const std::string &name) -> std::shared_ptr<IMaterial>;
	Shader  LoadShader(const std::string &name);

	Mesh    LoadMesh(std::string_view filename);

private:
	RenderDevice *device = nullptr;
	FileSystem *fs = nullptr;

	std::map<std::string, Shader> shader_cache;
	std::map<std::string, ShaderDesc> shader_descriptions;
	std::map<std::string, std::shared_ptr<IMaterial>> materials;
	//std::map<std::string, std::vector<std::pair<std::string, Texture::Format>>> material_defs;
};

BF_END_NAMESPACE
