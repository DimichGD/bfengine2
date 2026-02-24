#pragma once
#include "graphics/types.hpp"
#include "opengl_gen.hpp"

BF_BEGIN_NAMESPACE
BF_BEGIN_GL_NAMESPACE

struct TextureFormat
{
	GLenum internal_format;
	GLenum format;
	GLenum type;
};

GLenum ConvertEnum(GPUBuffer::Type value);
GLenum ConvertEnum(Shader::Type value);
GLenum ConvertEnum(RenderPass::Clear value);
GLenum ConvertEnum(Topology value);
TextureFormat ConvertEnum(bf::Texture::Format value);
GLenum ConvertEnum(DepthFunc func);

BF_END_GL_NAMESPACE
BF_END_NAMESPACE
