#pragma once
#include "graphics/opengl/render_device_gl.hpp"
#include "graphics/render_device.hpp"
#include "graphics/vulkan/render_device_vk.hpp"
#include <string>

BF_BEGIN_NAMESPACE

class IMaterial
{
public:
	virtual ~IMaterial() = default;
	virtual void Setup(RenderDeviceVK *device, DescriptorSet descriptor_set) = 0;
	virtual void Bind(RenderDeviceVK *device) = 0;
};

class Material: public IMaterial
{
public:
	Material(Texture diffuse_map)
	{
		this->diffuse_map = diffuse_map;
	}

	void Setup(RenderDeviceVK *device, DescriptorSet descriptor_set) override
	{
		this->descriptor_set = descriptor_set;
		device->WriteDescriptor(descriptor_set, 0, diffuse_map);
	}

	void Bind(RenderDeviceVK *device) override
	{
		device->BindDescriptorSet(Descriptor2::Set::MATERIAL, descriptor_set);
	}

	bool Ready()
	{
		return bool(descriptor_set);
	}

private:
	Texture diffuse_map;
	DescriptorSet descriptor_set {};
};

struct Surface
{
	Range vertex_range {};
	Material *material = nullptr;
	uint32_t material_index = 0;
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
	ResourceManager(RenderDeviceGL *device);
	ResourceManager(RenderDeviceVK *device, FileSystem *fs);
	~ResourceManager();
	BF_NON_COPYABLE(ResourceManager)
	BF_NON_MOVABLE(ResourceManager)

	Texture LoadTexture(std::string_view filename);
	//Shader  LoadShader(Shader::Type type, const std::string &filename);
	Mesh    LoadMesh(std::string_view filename);

private:
	RenderDeviceGL *device = nullptr;
	RenderDeviceVK *device2 = nullptr;
	FileSystem *fs = nullptr;
	//std::string data_path;
};

BF_END_NAMESPACE
