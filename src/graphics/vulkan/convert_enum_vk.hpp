#pragma once
#include "graphics/types.hpp"
#include <vulkan/vulkan.h>

BF_BEGIN_NAMESPACE
BF_BEGIN_VK_NAMESPACE

VkShaderStageFlags ConvertEnum(Shader::Type type);
VkBufferUsageFlags ConvertEnum(GPUBuffer::Type type);
VkFormat ConvertEnum(Vertex::Attrib attrib);
VkPrimitiveTopology ConvertEnum(Topology topology);
VkFormat ConvertEnum(bf::Texture::Format format);
VkImageLayout ConvertEnum(ImageLayout layout);
VkDescriptorType ConvertEnum(Descriptor2::Type type);

BF_END_VK_NAMESPACE
BF_END_NAMESPACE
