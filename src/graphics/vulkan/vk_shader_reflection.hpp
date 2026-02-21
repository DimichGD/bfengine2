#pragma once
#include "core/defines.hpp"
#include "graphics/types.hpp"
#include <vulkan/vulkan_core.h>

BF_BEGIN_NAMESPACE
BF_BEGIN_VK_NAMESPACE

ShaderReflectionData GetShaderReflection(Shader::Type type, const uint32_t *spirv, size_t word_count);
std::vector<uint32_t> CompileShader(const std::string &name, const std::vector<char> &source);
VkPipelineLayout CreatePipelineLayout(VkDevice device,
									  const std::vector<ShaderReflectionData *> &reflection_data,
									  std::vector<VkDescriptorSetLayout> &decriptor_set_layouts,
									  VkPipelineLayoutCreateFlags flags);

BF_END_VK_NAMESPACE
BF_END_NAMESPACE
