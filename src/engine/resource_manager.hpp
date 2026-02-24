#pragma once
#include "graphics/opengl/render_device_gl.hpp"
#include "graphics/render_device.hpp"
#include "graphics/vulkan/render_device_vk.hpp"
#include <memory>
#include <string>

BF_BEGIN_NAMESPACE

class IMaterial
{
public:
	virtual ~IMaterial() = default;
	virtual void Setup(RenderDevice *device, DescriptorSet descriptor_set) = 0;
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
		device->WriteDescriptor(descriptor_set, 0, diffuse_map);
		device->WriteDescriptor(descriptor_set, 1, normal_map);
		device->WriteDescriptor(descriptor_set, 2, specular_map);
	}

private:
	Texture diffuse_map;
	Texture normal_map;
	Texture specular_map;
};

struct MaterialID: Handle {};

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

	Texture LoadTexture(std::string_view filename);
	Mesh    LoadMesh(std::string_view filename);
	auto    LoadMaterial(const std::string &name) -> std::shared_ptr<IMaterial>;

private:
	RenderDevice *device = nullptr;
	FileSystem *fs = nullptr;

	std::map<std::string, std::shared_ptr<IMaterial>> materials;
};

BF_END_NAMESPACE
