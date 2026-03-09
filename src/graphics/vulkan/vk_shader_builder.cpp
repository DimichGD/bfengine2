#include "vk_shader_builder.hpp"
#include "core/log.hpp"
#include <fmt/format.h>
#include <sstream>

BF_BEGIN_NAMESPACE
BF_BEGIN_VK_NAMESPACE

std::string VertexAttribName(Vertex::Attrib attrib)
{
	switch (attrib)
	{
		case Vertex::Attrib::POSITION: return "POSITION";
		case Vertex::Attrib::TEXCOORD_0: return "TEXCOORD_0";
		case Vertex::Attrib::TEXCOORD_1: return "TEXCOORD_1";
		case Vertex::Attrib::COLOR: return "COLOR";
		case Vertex::Attrib::NORMAL: return "NORMAL";
		case Vertex::Attrib::TANGENT: return "TANGENT";
		case Vertex::Attrib::BONES: return "BONES";
		case Vertex::Attrib::WEIGHTS: return "WEIGHTS";
	}

	return "Unknown vertex attrib";
}

std::string VertexAttribTypeName(Vertex::Attrib attrib)
{
	switch (attrib)
	{
		case Vertex::Attrib::POSITION: return "vec3";
		case Vertex::Attrib::TEXCOORD_0: return "vec2";
		case Vertex::Attrib::TEXCOORD_1: return "vec2";
		case Vertex::Attrib::COLOR: return "vec3";
		case Vertex::Attrib::NORMAL: return "vec3";
		case Vertex::Attrib::TANGENT: return "vec4";
		case Vertex::Attrib::BONES: return "ivec4";
		case Vertex::Attrib::WEIGHTS: return "vec4";
	}

	return "Unknown vertex attrib";
}

static std::string camera_matrices_text = // TODO: camera_matrices_text and ui_camera_matrix_text conflict
R"(layout(std140, set = 0, binding = 0) uniform Camera
{
	mat4 U_PROJ_MATRIX;
	mat4 U_VIEW_MATRIX;
};)";

static std::string ui_camera_matrix_text =
R"(layout(std140, set = 0, binding = 0) uniform Camera
{
	mat4 U_PROJ_MATRIX;
};
)";

static std::string model_matrices_text =
R"(layout(std430, set = 0, binding = 1) buffer readonly Matrices
{
	mat4 U_MODEL_MATRICES[];
};)";

static std::string colors_text =
R"(layout(std140, set = 0, binding = 2) uniform Colors
{
	vec4 U_COLORS[32];
};)";

static std::string camera_data_text =
R"(layout(std140, set = 0, binding = 3) uniform CameraData
{
	mat4 U_INV_PROJ_MATRIX;
	mat4 U_INV_VIEW_MATRIX;
	vec4 U_CAMERA_POS;
};)";

static std::string point_light_text =
R"(layout(std140, set = 0, binding = 4) uniform Lights
{
	vec4 U_POINT_LIGHTS[32];
};)";

std::string UniformBufferString(EngineDescriptor desc)
{
	switch (desc)
	{
		case EngineDescriptor::CAMERA_MATRICES: return camera_matrices_text;
		case EngineDescriptor::UI_CAMERA_MATRIX: return ui_camera_matrix_text;
		case EngineDescriptor::MODEL_MATRICES: return model_matrices_text;
		case EngineDescriptor::COLORS: return colors_text;
		case EngineDescriptor::TEXTURES: return "layout(set = 1, binding = 0) uniform sampler2D U_TEXTURES[32];\n";
		case EngineDescriptor::LIGHT_CAMERA_DATA: return camera_data_text;
		case EngineDescriptor::POINT_LIGHTS: return point_light_text;
		//case EngineDescriptor::SPOT_LIGHTS: return { 0, 0, "Lights", "" };
		//case EngineDescriptor::BONE_MATRICES: return { 0, 0, "Bones", "" };
	}

	throw std::runtime_error("unreachable"); // TODO: proper unreachable
	return {};
}

std::string ConstantText(EngineConstants constant)
{
	switch (constant)
	{
		case EngineConstants::OBJECT_INDEX: return "\tlayout(offset = 0) int U_OBJECT_INDEX;\n";
		case EngineConstants::MATERIAL_INDEX: return "\tlayout(offset = 4) int U_MATERIAL_INDEX;\n";
		case EngineConstants::FACTOR: return "\tlayout(offset = 8) int U_FACTOR;\n";
		case EngineConstants::TIME: return "\tlayout(offset = 12) int U_TIME;\n";
	}

	throw std::runtime_error("unreachable"); // TODO: proper unreachable
	return {};
}


bool IsPushConstant(EngineUniform uniform)
{
	switch (uniform)
	{
		case EngineUniform::CAMERA_MATRICES:
		case EngineUniform::UI_CAMERA_MATRIX:
		case EngineUniform::MODEL_MATRICES:
		case EngineUniform::COLORS:
		case EngineUniform::LIGHT_CAMERA_DATA:
		case EngineUniform::POINT_LIGHTS:
		case EngineUniform::SPOT_LIGHTS:
		case EngineUniform::BONE_MATRICES:
			return false;

		case EngineUniform::OBJECT_INDEX:
		case EngineUniform::MATERIAL_INDEX:
		case EngineUniform::FACTOR:
		case EngineUniform::TIME:
			return true;
	}
}

std::string GetShaderString(const ShaderDesc &desc)
{
	std::stringstream ss;

	ss << "#version 460\n\n";

	for (uint32_t i = 0; i < 8; i++)
		if (bool(desc.input & Vertex::Attrib(1 << i)))
			ss << fmt::format("layout(location = {}) in {} IN_{};\n", i,
							  VertexAttribTypeName(Vertex::Attrib(1 << i)),
							  VertexAttribName(Vertex::Attrib(1 << i)));

	ss << "\n";

	for (EngineDescriptor descriptor: desc.buffers)
		ss << UniformBufferString(descriptor) << "\n\n";

	if (desc.constants.size() > 0)
	{
		ss << "layout(push_constant) uniform Constants\n{\n";

		for (EngineConstants constant: desc.constants)
			ss << ConstantText(constant);

		ss << "};\n";
	}

	for (uint32_t i = 0; i < desc.textures.size(); i++)
	{
		if (desc.textures[i].samples == 1)
			ss << fmt::format("layout(set = 1, binding = {}) uniform sampler2D {};\n", i, desc.textures[i].name);

		else
			ss << fmt::format("layout(set = 1, binding = {}) uniform sampler2DMS {};\n", i, desc.textures[i].name);
	}

	ss << "\n";

	return ss.str();
}

BF_END_VK_NAMESPACE
BF_END_NAMESPACE
