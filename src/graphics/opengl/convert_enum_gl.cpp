#include "convert_enum_gl.hpp"
#include "core/log.hpp"

BF_BEGIN_NAMESPACE
BF_BEGIN_GL_NAMESPACE

GLenum ConvertEnum(GPUBuffer::Type value)
{
	switch (value)
	{
		case GPUBuffer::Type::VERTEX: return GL_ARRAY_BUFFER;
		case GPUBuffer::Type::INDEX: return GL_ELEMENT_ARRAY_BUFFER;
		case GPUBuffer::Type::UNIFORM: return GL_UNIFORM_BUFFER;
		case GPUBuffer::Type::STAGING: return {}; // TODO: report error?
	}

	return {};
}

GLenum ConvertEnum(Shader::Type value)
{
	switch (value)
	{
		case Shader::Type::VERTEX: return GL_VERTEX_SHADER;
		case Shader::Type::FRAGMENT: return GL_FRAGMENT_SHADER;
		case Shader::Type::GEOMETRY: return GL_GEOMETRY_SHADER;
		case Shader::Type::COMPUTE: return GL_COMPUTE_SHADER;
	}

	return {};
}

GLenum ConvertEnum(RenderPass::Clear value)
{
	switch (value)
	{
		case RenderPass::Clear::COLOR: return GL_COLOR_BUFFER_BIT;
		case RenderPass::Clear::DEPTH: return GL_DEPTH_BUFFER_BIT;
		case RenderPass::Clear::STENCIL: return GL_STENCIL_BUFFER_BIT;
		case RenderPass::Clear::COLOR_DEPTH: return GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
	}

	return {};
}

GLenum ConvertEnum(Topology value)
{
	switch (value)
	{
		case Topology::TRIANGLES: return GL_TRIANGLES;
		case Topology::TRIANGLE_STRIP: return GL_TRIANGLE_STRIP;
		case Topology::LINES: return GL_LINES;
		case Topology::LINE_STRIP: return GL_LINE_STRIP;
	}

	return {};
}

TextureFormat ConvertEnum(bf::Texture::Format value)
{
	switch (value)
	{
		case Texture::Format::BGR8: return { GL_RGBA8, GL_BGR, GL_UNSIGNED_BYTE };
		case Texture::Format::BGRA8: return { GL_RGBA8, GL_BGRA, GL_UNSIGNED_BYTE };
		case Texture::Format::R8: return { GL_R8, GL_RED, GL_UNSIGNED_BYTE };
		case Texture::Format::RG8: return { GL_RG8, GL_RG, GL_UNSIGNED_BYTE };
		case Texture::Format::RGB8: return { GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE };
		case Texture::Format::RGBA8: return { GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE };
		case Texture::Format::SRGBA8: return { GL_SRGB8_ALPHA8, GL_RGBA, GL_UNSIGNED_BYTE };
		case Texture::Format::SBGRA8: Warn() << "OpenGL SBGRA8 not implemented"; return {};
		case Texture::Format::RGBA16F: return { GL_RGBA16F, GL_RGBA, GL_HALF_FLOAT };
		case Texture::Format::D24: return { GL_DEPTH_COMPONENT24, GL_DEPTH, GL_FLOAT }; // FIXME: float?
		case Texture::Format::D24S8: return { GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8 };
		case Texture::Format::D32F: return { GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT };
		case Texture::Format::BC1: return { GL_RGBA8, GL_BGR, GL_UNSIGNED_BYTE };
	}

	return {};
}

BF_END_GL_NAMESPACE
BF_END_NAMESPACE
