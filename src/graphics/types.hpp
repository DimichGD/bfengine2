#pragma once
#include "utils/enum_operators.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <map>
#include <span>
#include <string>
#include <utility>
#include <vector>
#include <array>

BF_BEGIN_NAMESPACE

enum class Blend
{
	NONE, ADD, MULTIPLY, ALPHA,
};

enum class Depth
{
	LESS,
};

struct RenderPass
{
	enum class Clear
	{
		COLOR,
		DEPTH,
		STENCIL,
		COLOR_DEPTH,
	};

	/*glm::vec4 color { 0.0f, 0.0f, 0.0f, 1.0f };
	float depth = 1.0f;
	Clear clear_flags;*/
};

struct Vertex
{
	enum class Attrib: uint32_t
	{
		POSITION   = 1 << 0,
		TEXCOORD_0 = 1 << 1,
		TEXCOORD_1 = 1 << 2,
		COLOR      = 1 << 3,
		NORMAL     = 1 << 4,
		TANGENT    = 1 << 5,
		BONES      = 1 << 6,
		WEIGHTS    = 1 << 7,
	};

	enum class Format: uint32_t
	{
		DEBUG_LINES,
		STATIC,
		SKELETAL,
		UI,
	};

	static constexpr std::array<uint32_t, 8> sizes { 3, 2, 2, 3, 3, 4, 4, 4 };

	enum class Type
	{
		FLOAT, VEC2, VEC3, VEC4,
	};
};



template<>
struct IsEnumFlag<Vertex::Attrib>: std::true_type {};



/*inline constexpr Vertex::Attrib operator|(Vertex::Attrib lhs, Vertex::Attrib rhs)
{
	return static_cast<Vertex::Attrib>(std::to_underlying(lhs) | std::to_underlying(rhs));
}

inline constexpr Vertex::Attrib operator|=(Vertex::Attrib lhs, Vertex::Attrib rhs)
{
	return static_cast<Vertex::Attrib>(std::to_underlying(lhs) | std::to_underlying(rhs));
}

inline constexpr std::underlying_type_t<Vertex::Attrib> operator&(Vertex::Attrib lhs, uint32_t rhs)
{
	return std::to_underlying(lhs) & rhs;
}

inline constexpr Vertex::Attrib operator&(Vertex::Attrib lhs, Vertex::Attrib rhs)
{
	return static_cast<Vertex::Attrib>(std::to_underlying(lhs) & std::to_underlying(rhs));
}*/

struct Range
{
	uint32_t start = 0;
	uint32_t count = 0;
};

struct Handle
{
	enum class Type
	{
		MATERIAL,
		SHADER,
		TEXTURE,
	};

	uint32_t handle = UINT32_MAX;

	explicit operator bool() const
	{
		return handle != UINT32_MAX;
	}

	bool operator<(const Handle &other) const
	{
		return handle < other.handle;
	}

	bool operator==(const Handle &other) const
	{
		return handle == other.handle;
	}
};

struct GPUBuffer: Handle
{
	enum class Type
	{
		VERTEX,
		INDEX,
		UNIFORM,
		STORAGE,
		STAGING,
	};

	enum class Flags
	{
		STATIC_READ,
	};

	using enum Type;
	using enum Flags;

	uint32_t size = 0;
	Type type = {};
};

struct Shader: Handle
{
	enum class Type: uint8_t
	{
		VERTEX,
		FRAGMENT,
		GEOMETRY,
		COMPUTE,
	};

	Shader(uint32_t handle, Type type)
	{
		this->handle = handle;
		this->type = type;
	}

	Shader()
	{
		this->handle = 0;
		this->type = {};
	}

	Type type;
};

struct Descriptor2
{
	enum class Set: uint8_t
	{
		SCENE,
		MATERIAL,
		OBJECT,
	};

	enum class Type: uint8_t
	{
		UNIFORM_BUFFER,
		STORAGE_BUFFER,
		TEXTURE,
	};

	Descriptor2() = delete;
	Descriptor2(uint8_t set, uint8_t binding, Type type, uint8_t array_size/*, Shader::Type stage*/)
	{
		this->set = set;
		this->binding = binding;
		this->type = type;
		this->array_size = array_size;
		//this->stage = stage;
	}

	/*bool CompareWithoutStage(const Descriptor2 &other) const // FIXME: better naming
	{
		return
			set == other.set &&
			binding == other.binding &&
			type == other.type &&
			array_size == other.array_size;
	}*/

	bool operator==(const Descriptor2 &other) const
	{
		return
			set == other.set &&
			binding == other.binding &&
			type == other.type &&
			array_size == other.array_size;
	}

	uint32_t Hash() const
	{
		return set | (binding << 8) | (uint8_t(type) << 16) | (array_size << 24);
	}

	uint8_t set = 0;
	uint8_t binding = 0;
	Type type = Type::UNIFORM_BUFFER;
	uint8_t array_size = 0;
	//Shader::Type stage = Shader::Type::VERTEX;
};

struct Constant
{
	enum class Type: uint8_t
	{
		INT,
		FLOAT,
		VEC4,
	};

	bool operator==(const Constant &other) const
	{
		return
			offset == other.offset &&
			size == other.size &&
			type == other.type;
	}

	uint8_t offset = 0;
	uint8_t size = 0;
	Type type;
};

struct DescriptorSet: Handle {};

struct ShaderReflectionData
{
	std::string name;
	uint32_t max_set = 0;
	Shader::Type stage;

	std::vector<Constant> constants;
	std::array<std::vector<Descriptor2>, 4> sets {};
};

struct Uniform
{
	enum class Name
	{
		/*MODEL_MATRIX,
		VIEW_MATRIX,
		PROJ_MATRIX,*/
		INDEX,
		COLOR,
	};

	enum class Texture
	{
		DIFFUSE,
		NORMAL,
		SPECULAR,
	};

	enum class Buffer
	{
		CAMERA,
		MATRICES,
		SKINNING,
	};
};

struct Program: Handle
{
	//
};

struct VertexLayout: Handle
{
	uint32_t stride = 0;
};

enum class Topology
{
	TRIANGLES,
	TRIANGLE_STRIP,
	LINES,
	LINE_STRIP,
};

enum class DepthFunc
{
	NEVER,
	ALWAYS,
	LESS,
	GREATER,
	EQUAL,
	NOT_EQUAL,
	LESS_OR_EQUAL,
	GREATER_OR_EQUAL,
};

struct Raster
{
	Blend blend = Blend::NONE;
	bool depth_test = true;
	bool depth_write = true;
	DepthFunc depth_func = DepthFunc::LESS;
};

/*struct Descriptor
{
	enum class Set
	{
		SCENE,
		MATERIAL,
		OBJECT,
	};

	enum class Type
	{
		BUFFER,
		TEXTURE,
		CONSTANT,
	};

	enum class ConstantType
	{
		NONE,
		INT,
		VEC4,
	};

	Descriptor() = delete;
	Descriptor(Shader::Type stage, Type type, ConstantType constant_type = ConstantType::NONE)
	{
		this->stage = stage;
		this->type = type;
		this->constant_type = constant_type;
	}

	Shader::Type stage;
	Type type;
	ConstantType constant_type;
};*/

struct DrawCommand
{
	uint32_t first = 0;
	uint32_t count = 0;
};

struct Sampler: Handle
{
	enum class Type
	{
		NEAREST, LINEAR, MIPMAP_LINEAR, ANISOTROPY,
	};
};

enum class ImageLayout
{
	UNDEFINED,
	COLOR_ATTACHMENT,
	DEPTH_ATTACHMENT,
	DEPTH_STENCIL_ATTACHMENT,
	COLOR_READ_ONLY,
	DEPTH_STENCIL_READ_ONLY,
	PRESENT,
};

struct Texture: Handle
{
	enum class Format
	{
		BGR8, BGRA8,
		R8, RG8, RGB8, RGBA8,
		SBGRA8, SRGBA8,
		RGBA16F,
		D24, D24S8, D32F,
		BC1,
	};

	enum class Usage
	{
		SHADER_READ      = 1 << 0,
		COLOR_ATTACHMENT = 1 << 1,
		DEPTH_ATTACHMENT = 1 << 2, // TODO: rename to depth_stencil?
	};

	Format format;

	static bool IsDepth(Format format)
	{
		switch (format)
		{
			case Format::BGR8:
			case Format::BGRA8:
			case Format::R8:
			case Format::RG8:
			case Format::RGB8:
			case Format::RGBA8:
			case Format::SBGRA8:
			case Format::SRGBA8:
			case Format::RGBA16F:
			case Format::BC1:
				return false;

			case Format::D24:
			case Format::D24S8:
			case Format::D32F:
				return true;
		}
	}
};

template<>
struct IsEnumFlag<Texture::Usage>: std::true_type {};

/*inline constexpr Texture::Usage operator|(Texture::Usage lhs, Texture::Usage rhs)
{
	return static_cast<Texture::Usage>(std::to_underlying(lhs) | std::to_underlying(rhs));
}

inline constexpr std::underlying_type_t<Texture::Usage> operator&(Texture::Usage lhs, uint32_t rhs)
{
	return std::to_underlying(lhs) & rhs;
}

inline constexpr Texture::Usage operator&(Texture::Usage lhs, Texture::Usage rhs)
{
	return static_cast<Texture::Usage>(std::to_underlying(lhs) & std::to_underlying(rhs));
}*/

struct TextureDesc
{
	uint32_t width = 0;
	uint32_t height = 0;
	Texture::Format format {};
	Texture::Usage usage {};
	uint32_t levels = 0;
	uint32_t samples = 1;
	//void *pixels = nullptr;
	std::vector<char> pixels {};
	bool generate_mipmaps = false;
};

struct Framebuffer
{
	std::vector<Texture> color_textures;
	//std::vector<Texture::Format> color_formats;
	Texture depth_texture {};
	uint32_t samples = 1;
	uint32_t width = 0;
	uint32_t height = 0;
};

struct FramebufferID: Handle {};

struct FramebufferDesc
{
	uint32_t width = 0;
	uint32_t height = 0;
	uint32_t samples = 1;
	std::vector<Texture> color_textures {};
	Texture depth_texture {};
};

struct PipelineDesc
{
	std::vector<Shader> shaders;
	Topology topology;
	Vertex::Attrib vertex_attribs;
	Raster raster;
	FramebufferID framebuffer_id;
};

struct Pipeline
{
	Program prog {};
	VertexLayout vao {};
	uint32_t topology = 0;
	Raster raster {};
};

struct PipelineID: Handle {};



BF_END_NAMESPACE
