#include "convert_enum_vk.hpp"
#include "core/log.hpp"

BF_BEGIN_NAMESPACE
BF_BEGIN_VK_NAMESPACE

VkShaderStageFlagBits ConvertEnum(Shader::Type type)
{
	switch (type)
	{
		case Shader::Type::VERTEX:   return VK_SHADER_STAGE_VERTEX_BIT;
		case Shader::Type::FRAGMENT: return VK_SHADER_STAGE_FRAGMENT_BIT;
		case Shader::Type::GEOMETRY: return VK_SHADER_STAGE_GEOMETRY_BIT;
		case Shader::Type::COMPUTE:  return VK_SHADER_STAGE_COMPUTE_BIT;
	}

	return {};
}

VkBufferUsageFlags ConvertEnum(GPUBuffer::Type type)
{
	switch (type)
	{
		case GPUBuffer::Type::VERTEX:  return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		case GPUBuffer::Type::INDEX:   return VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
		case GPUBuffer::Type::UNIFORM: return VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
		case GPUBuffer::Type::STAGING: return VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
	}

	return {};
}

VkFormat ConvertEnum(Vertex::Attrib attrib)
{
	switch (attrib)
	{
		case Vertex::Attrib::POSITION:   return VK_FORMAT_R32G32B32_SFLOAT;
		case Vertex::Attrib::TEXCOORD_0: return VK_FORMAT_R32G32_SFLOAT;
		case Vertex::Attrib::TEXCOORD_1: return VK_FORMAT_R32G32_SFLOAT;
		case Vertex::Attrib::COLOR:      return VK_FORMAT_R32G32B32_SFLOAT;
		case Vertex::Attrib::NORMAL:     return VK_FORMAT_R32G32B32_SFLOAT;
		case Vertex::Attrib::TANGENT:    return VK_FORMAT_R32G32B32A32_SFLOAT;
		case Vertex::Attrib::BONES:      return VK_FORMAT_R32G32B32A32_SFLOAT;
		case Vertex::Attrib::WEIGHTS:    return VK_FORMAT_R32G32B32A32_SFLOAT;
	}

	return {};
}

VkPrimitiveTopology ConvertEnum(Topology topology)
{
	switch (topology)
	{
		case Topology::TRIANGLES:      return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		case Topology::TRIANGLE_STRIP: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
		case Topology::LINES:          return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
		case Topology::LINE_STRIP:     return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
	}

	return {};
}

VkFormat ConvertEnum(Texture::Format format)
{
	if (format == Texture::Format::D24)
		Log("ConvertEnum") << "Vulkan does not support D24 format";

	switch (format)
	{
		case Texture::Format::BGR8:       return VK_FORMAT_B8G8R8_UNORM;
		case Texture::Format::BGRA8:      return VK_FORMAT_B8G8R8A8_UNORM;
		case Texture::Format::R8:         return VK_FORMAT_R8_UNORM;
		case Texture::Format::RG8:        return VK_FORMAT_R8G8_UNORM;
		case Texture::Format::RGB8:       return VK_FORMAT_R8G8B8_UNORM;
		case Texture::Format::RGBA8:      return VK_FORMAT_R8G8B8A8_UNORM;
		case Texture::Format::SBGRA8:     return VK_FORMAT_B8G8R8A8_SRGB;
		case Texture::Format::SRGBA8:     return VK_FORMAT_R8G8B8A8_SRGB;
		case Texture::Format::RGBA16F:    return VK_FORMAT_R16G16B16A16_SFLOAT;
		case Texture::Format::D24:        return VK_FORMAT_D24_UNORM_S8_UINT;
		case Texture::Format::D24S8:      return VK_FORMAT_D24_UNORM_S8_UINT;
		case Texture::Format::D32F:       return VK_FORMAT_D32_SFLOAT;
		case Texture::Format::BC1:        return VK_FORMAT_BC1_RGBA_UNORM_BLOCK; // FIXME: srgb?
	}

	return {};
}

VkImageLayout ConvertEnum(ImageLayout layout)
{
	switch (layout)
	{
		case ImageLayout::UNDEFINED:                return VK_IMAGE_LAYOUT_UNDEFINED;
		case ImageLayout::COLOR_ATTACHMENT:         return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		case ImageLayout::DEPTH:                    return VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;
		case ImageLayout::DEPTH_STENCIL_ATTACHMENT: return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		case ImageLayout::SHADER_READ_ONLY:         return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		case ImageLayout::PRESENT:                  return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	}

	return {};
}

VkDescriptorType ConvertEnum(Descriptor2::Type type)
{
	switch (type)
	{
		case Descriptor2::Type::UNIFORM_BUFFER: return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		case Descriptor2::Type::STORAGE_BUFFER: return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		case Descriptor2::Type::TEXTURE:        return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	}

	return {};
}

BF_END_VK_NAMESPACE
BF_END_NAMESPACE
