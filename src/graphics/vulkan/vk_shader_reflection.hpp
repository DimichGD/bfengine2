#pragma once
#include "core/defines.hpp"
#include "graphics/types.hpp"
#include "graphics/vulkan/vk_internal.hpp"
#include <vulkan/vulkan_core.h>

BF_BEGIN_NAMESPACE

struct StageDescriptor
{
	Descriptor2 descriptor;
	VkShaderStageFlags stage_flags = 0;
};

BF_BEGIN_VK_NAMESPACE

//ShaderReflectionData GetShaderReflection(const std::string &name, Shader::Type type, const uint32_t *spirv, size_t word_count);
std::vector<uint32_t> CompileShader(const std::string &name, const std::vector<char> &source);
std::vector<uint32_t> CompileShader(const std::string &name, Shader::Type type, const std::string &source);
/*VkPipelineLayout CreatePipelineLayout(VkDevice device,
									  std::map<uint32_t, VkDescriptorSetLayout> &global_descriptor_set_layouts,
									  const std::vector<ShaderReflectionData *> &reflection_data,
									  std::array<ConstantRange, 4> &constant_ranges,
									  std::vector<VkDescriptorSetLayout> &decriptor_set_layouts,
									  VkPipelineLayoutCreateFlags flags);*/

std::array<std::vector<StageDescriptor>, 4> CombineDescriptors(const std::vector<ShaderDesc> &reflection_data);

void CreatePipelineLayout(VkDevice device, Pipeline &pipeline,
						  std::map<uint32_t, VkDescriptorSetLayout> &global_descriptor_set_layouts,
						  const std::vector<ShaderDesc> &reflection_data);

BF_END_VK_NAMESPACE
BF_END_NAMESPACE
