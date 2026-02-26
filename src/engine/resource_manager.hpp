#pragma once
#include "core/log.hpp"
#include "graphics/opengl/render_device_gl.hpp"
#include "graphics/render_device.hpp"
#include "graphics/render_paths/graphics_context.hpp"
#include "graphics/vulkan/vk_render_device.hpp"
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

enum class EngineDescriptor
{
	CAMERA_MATRICES,
	MODEL_MATRICES,
	MATERIAL_DATA,
	//CUSTOM_DATA,
	LIGHT_CAMERA_DATA,
	POINT_LIGHTS,
	SPOT_LIGHTS,
	AREA_LIGHTS,
	BONE_MATRICES,
};

enum class EngineConstants
{
	OBJECT_INDEX,
	MATERIAL_INDEX,
	FACTOR,
	TIME,
};

struct TextureInputDesc
{
	//std::string slot_name;
	Texture::Format format;
};

struct MaterialDefinition
{
	std::vector<EngineDescriptor> descriptors;
	std::vector<EngineConstants> constants;
	std::unordered_map<std::string, TextureInputDesc> textures;
	Shader vertex_shader;
	Shader fragment_shader;
};

class CustomMaterial: public IMaterial
{
public:
	CustomMaterial(std::string name, MaterialDefinition *definition, const std::vector<Texture> &textures)
	{
		this->def = definition;
		this->textures = std::move(textures);
		this->name = name;
	}

	void Setup(RenderDevice *device, DescriptorSet descriptor_set) override
	{
		std::terminate();
	}

	void Setup2(RenderDevice *device, GraphicsContext *context, Descriptor2::Set set_index, DescriptorSet descriptor_set) override
	{
		for (uint32_t i = 0; i < def->textures.size(); i++)
			device->WriteDescriptor(descriptor_set, i, textures.at(i));

		/*switch (set_index)
		{
			case Descriptor2::Set::SCENE:
				for (uint32_t i = 0; i < def->descriptors.size(); i++)
				{
					switch (def->descriptors[i])
					{

						case EngineDescriptor::CAMERA_MATRICES:
							device->WriteDescriptor(descriptor_set, i, context->active_camera_ubo);
							break;

						case EngineDescriptor::MODEL_MATRICES:
							device->WriteDescriptor(descriptor_set, i, context->model_matrices_ubo);
							break;

						default:
							Log() << "Setup2 switch failed";
							break;
					}
				}
				break;

			case Descriptor2::Set::MATERIAL:
				for (uint32_t i = 0; i < def->textures.size(); i++)
				{
					device->WriteDescriptor(descriptor_set, i, textures.at(i));
				}
				break;

			case Descriptor2::Set::OBJECT:
				break;
		}*/
	}

std::string name;

private:
	MaterialDefinition *def = nullptr;
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

	Texture	LoadKTX2(std::string_view filename, Texture::Format format = Texture::Format::SRGBA8);
	Texture LoadTexture(std::string_view filename, Texture::Format format = Texture::Format::SRGBA8);
	auto    LoadMaterial(const std::string &name) -> std::shared_ptr<IMaterial>;

	Mesh    LoadMesh(std::string_view filename);

private:
	RenderDevice *device = nullptr;
	FileSystem *fs = nullptr;

	std::map<std::string, std::shared_ptr<IMaterial>> materials;
	std::map<std::string, MaterialDefinition> material_descriptions;
};

BF_END_NAMESPACE
