#pragma once
#include "graphics/types.hpp"
#include <vulkan/vulkan.h>
//#include <map>

BF_BEGIN_NAMESPACE
BF_BEGIN_VK_NAMESPACE

class GraphicsPipelineBuilder
{
public:
	GraphicsPipelineBuilder(VkDevice device);
	void SetVertexFormat(Vertex::Attrib attribs);
	void SetTopology(Topology topology);
	void SetLayout(VkPipelineLayout layout);
	void SetRasterState(Raster raster_state);
	void SetSwapchainFormat(VkFormat color_format, VkFormat depth_format);
	//void SetAttachmentFormats(std::vector<bf::Texture::Format> formats);
	void SetFramebuffer(const Framebuffer &framebuffer);
	void AppendShader(VkShaderStageFlagBits stage, VkShaderModule module);

	VkPipeline CreateVertexInputStage(Vertex::Attrib vertex_attribs, Topology topology);
	VkPipeline CreateVertexShaderStage(const std::string &name,
									   std::span<const uint32_t> binary, VkPipelineLayout layout);
	VkPipeline CreateFragmentShaderStage(const std::string &name,
						std::span<const uint32_t> binary, VkPipelineLayout layout);
	VkPipeline CreateFragmentOutputStage(Raster raster_state);

	VkPipeline Build(VkDevice device, VkPipelineCache pipeline_cache);



private:
	//static std::map<uint64_t, VkPipeline> vertex_input_stages;
	//static std::vector<VkPipeline> vertex_shader_stages;
	//static std::vector<VkPipeline> fragment_shader_stages;
	//static std::vector<VkPipeline> fragment_output_stages;

	//uint32_t vertex_input_stage_index = 0;
	/*uint32_t vertex_shader_stage_index = 0;
	uint32_t fragment_shader_stage_index = 0;
	uint32_t fragment_output_stage_index = 0;*/

	struct VertexInput
	{
		std::vector<VkVertexInputBindingDescription> bindings;
		std::vector<VkVertexInputAttributeDescription> attribs;
	};

	std::vector<VkPipelineShaderStageCreateInfo> shader_stage_ci_array;
	VertexInput vertex_input;
	VkPrimitiveTopology topology;
	std::vector<VkFormat> attachment_formats;
	VkFormat depth_format = VK_FORMAT_UNDEFINED;
	//VkFormat swapchain_format = VK_FORMAT_UNDEFINED;

	VkCompareOp depth_compare_op = VK_COMPARE_OP_LESS;
	VkBool32 depth_test_enable = VK_FALSE;
	VkBool32 depth_write_enable = VK_FALSE;

	VkBlendFactor src_color_blend_factor = VK_BLEND_FACTOR_ONE;
	VkBlendFactor dst_color_blend_factor = VK_BLEND_FACTOR_ZERO;
	VkBlendFactor src_alpha_blend_factor = VK_BLEND_FACTOR_ONE;
	VkBlendFactor dst_alpha_blend_factor = VK_BLEND_FACTOR_ZERO;
	VkBlendOp color_blend_op = VK_BLEND_OP_ADD;
	VkBlendOp alpha_blend_op = VK_BLEND_OP_ADD;
	VkBool32 blend_enable = VK_FALSE;

	VkPipelineLayout layout;

	//VkPipeline pipeline;
	VkDevice device;
};

BF_END_VK_NAMESPACE
BF_END_NAMESPACE
