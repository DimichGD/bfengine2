#pragma once
#include "graphics/types.hpp"

BF_BEGIN_NAMESPACE

enum class EngineUniform
{
	CAMERA_MATRICES,
	UI_CAMERA_MATRIX,
	MODEL_MATRICES,
	COLORS,
	//MATERIAL_DATA,
	//CUSTOM_DATA,
	LIGHT_CAMERA_DATA,
	POINT_LIGHTS,
	SPOT_LIGHTS,
	//AREA_LIGHTS,
	BONE_MATRICES,

	OBJECT_INDEX,
	MATERIAL_INDEX,
	FACTOR,
	TIME,
};

enum class EngineDescriptor
{
	CAMERA_MATRICES,
	UI_CAMERA_MATRIX,
	MODEL_MATRICES,
	COLOR,
	COLORS,
	TEXTURES,
	//MATERIAL_DATA,
	//CUSTOM_DATA,
	LIGHT_CAMERA_DATA,
	POINT_LIGHTS,
	SPOT_LIGHTS,
	//AREA_LIGHTS,
	BONE_MATRICES,
};

struct TextureInput
{
	std::string name;
	uint32_t samples;
};

struct ShaderDesc // change to definition?
{
	bf::Shader::Type type;
	std::string filename;
	Vertex::Attrib input {};
	std::vector<EngineUniform> uniforms;
	std::vector<EngineDescriptor> buffers;
	std::vector<EngineConstants> constants;
	std::vector<TextureInput> textures;
};

static uint32_t GetDescriptorSet(EngineDescriptor desc)
{
	switch (desc)
	{
		case EngineDescriptor::CAMERA_MATRICES: return 0;
		case EngineDescriptor::UI_CAMERA_MATRIX: return 0;
		case EngineDescriptor::MODEL_MATRICES: return 0;
		case EngineDescriptor::COLOR: return 1;
		case EngineDescriptor::COLORS: return 0;
		case EngineDescriptor::TEXTURES: return 1;
		//case EngineDescriptor::MATERIAL_DATA: return 1;
		case EngineDescriptor::LIGHT_CAMERA_DATA: return 0;
		case EngineDescriptor::POINT_LIGHTS: return 0;
		case EngineDescriptor::SPOT_LIGHTS: return 0;
		case EngineDescriptor::BONE_MATRICES: return 2;
			break;
	}
}

static uint32_t GetDescriptorBinding(EngineDescriptor desc)
{
	switch (desc)
	{
		case EngineDescriptor::CAMERA_MATRICES: return 0;
		case EngineDescriptor::UI_CAMERA_MATRIX: return 0;
		case EngineDescriptor::MODEL_MATRICES: return 1;
		case EngineDescriptor::COLOR: return 0;
		case EngineDescriptor::COLORS: return 2;
		case EngineDescriptor::TEXTURES: return 0;
		//case EngineDescriptor::MATERIAL_DATA: return 0;
		case EngineDescriptor::LIGHT_CAMERA_DATA: return 3;
		case EngineDescriptor::POINT_LIGHTS: return 4;
		case EngineDescriptor::SPOT_LIGHTS: return 4;
		case EngineDescriptor::BONE_MATRICES: return 0;
	}
}

BF_END_NAMESPACE
