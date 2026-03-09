#include "graphics/vulkan/vk_pipeline_builder.hpp"
#include "core/log.hpp"
#include "graphics/vulkan/vk_convert_enum.hpp"
#include "graphics/vulkan/vk_shader_reflection.hpp"
#include "utils/hash.hpp"
#include <glm/common.hpp>

BF_BEGIN_NAMESPACE
BF_BEGIN_VK_NAMESPACE

//std::map<uint64_t, VkPipeline> GraphicsPipelineBuilder::vertex_input_stages;

GraphicsPipelineBuilder::GraphicsPipelineBuilder(VkDevice device)
{
	this->device = device;
}

void GraphicsPipelineBuilder::SetVertexFormat(Vertex::Attrib attribs)
{	
	vertex_input.attribs.reserve(std::popcount(std::to_underlying(attribs)));

	uint32_t offset = 0;
	for (uint32_t i = 0; i < 8; i++) // FIXME: 8 is hardcoded
	{
		if (attribs & (1 << i))
		{
			VkVertexInputAttributeDescription vertex_input_attrib_desc =
			{
				.location = i,
				.binding = 0,
				.format = vk::ConvertEnum(Vertex::Attrib(1 << i)),
				.offset = offset
			};

			vertex_input.attribs.push_back(vertex_input_attrib_desc);

			offset += Vertex::sizes[i] * sizeof(float);
		}
	}

	VkVertexInputBindingDescription vertex_input_binding_desc =
	{
		.binding = 0,
		.stride = offset,
		.inputRate = VK_VERTEX_INPUT_RATE_VERTEX
	};

	vertex_input.bindings.push_back(vertex_input_binding_desc);
}

void GraphicsPipelineBuilder::SetTopology(Topology topology)
{
	this->topology = vk::ConvertEnum(topology);
}

void GraphicsPipelineBuilder::SetLayout(VkPipelineLayout layout)
{
	this->layout = layout;
}

void GraphicsPipelineBuilder::SetRasterState(Raster raster_state)
{
	depth_compare_op = vk::ConvertEnum(raster_state.depth_func);
	depth_test_enable = raster_state.depth_test ? VK_TRUE : VK_FALSE;
	depth_write_enable = raster_state.depth_write ? VK_TRUE : VK_FALSE;

	if (raster_state.blend == Blend::ALPHA)
	{
		blend_enable = VK_TRUE;
		src_color_blend_factor = VK_BLEND_FACTOR_SRC_ALPHA; // VK_BLEND_FACTOR_SRC_ALPHA; one - premultiplied
		dst_color_blend_factor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		src_alpha_blend_factor = VK_BLEND_FACTOR_SRC_ALPHA;
		dst_alpha_blend_factor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	}
}

void GraphicsPipelineBuilder::SetSwapchainFormat(VkFormat color_format, VkFormat depth_format)
{
	attachment_formats.push_back(color_format);
	this->depth_format = depth_format;
}

void GraphicsPipelineBuilder::SetFramebuffer(const Framebuffer &framebuffer)
{
	if (!framebuffer.color_textures.empty() && framebuffer.samples > 1)
		samples = VK_SAMPLE_COUNT_4_BIT;

	attachment_formats.reserve(framebuffer.color_textures.size());
	for (auto texture: framebuffer.color_textures)
		attachment_formats.push_back(vk::ConvertEnum(texture.format));

	if (framebuffer.depth_texture)
		depth_format = vk::ConvertEnum(framebuffer.depth_texture.format);
}

void GraphicsPipelineBuilder::AppendShader(VkShaderStageFlagBits stage, VkShaderModule module)
{
	VkPipelineShaderStageCreateInfo shader_stage_ci
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.stage = stage,
		.module = module,
		.pName = "main",
		.pSpecializationInfo = nullptr,
	};

	shader_stage_ci_array.push_back(shader_stage_ci);
}

VkPipeline GraphicsPipelineBuilder::Build(VkDevice device, VkPipelineCache pipeline_cache)
{
	VkPipelineVertexInputStateCreateInfo vertex_input_ci
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.vertexBindingDescriptionCount = uint32_t(vertex_input.bindings.size()),
		.pVertexBindingDescriptions = vertex_input.bindings.data(),
		.vertexAttributeDescriptionCount = uint32_t(vertex_input.attribs.size()),
		.pVertexAttributeDescriptions = vertex_input.attribs.data(),
	};

	VkPipelineInputAssemblyStateCreateInfo input_assembly_ci =
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.topology = topology,
		.primitiveRestartEnable = false
	};

	VkPipelineViewportStateCreateInfo viewport_ci =
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.viewportCount = 1,
		.pViewports = nullptr, //&viewport,
		.scissorCount = 1,
		.pScissors = nullptr, //&scissor
	};

	VkPipelineRasterizationStateCreateInfo rasterization_ci =
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.depthClampEnable = VK_FALSE,
		.rasterizerDiscardEnable = VK_FALSE,
		.polygonMode = VK_POLYGON_MODE_FILL,
		.cullMode = VK_CULL_MODE_NONE, //VK_CULL_MODE_BACK_BIT,
		.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
		.depthBiasEnable = VK_FALSE,
		.depthBiasConstantFactor = 0.0f,
		.depthBiasClamp = 0.0f,
		.depthBiasSlopeFactor = 0.0f,
		.lineWidth = 1.0f
	};

	uint32_t sample_mask = UINT32_MAX;
	VkPipelineMultisampleStateCreateInfo multisample_ci =
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.rasterizationSamples = samples,
		.sampleShadingEnable = VK_FALSE,
		.minSampleShading = 1.0f,
		.pSampleMask = &sample_mask, // TODO: is it correct?
		.alphaToCoverageEnable = VK_FALSE,
		.alphaToOneEnable = VK_FALSE
	};

	VkPipelineDepthStencilStateCreateInfo depth_stencil_ci =
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.depthTestEnable = depth_test_enable,
		.depthWriteEnable = depth_write_enable,
		.depthCompareOp = depth_compare_op, //VK_COMPARE_OP_LESS_OR_EQUAL,
		.depthBoundsTestEnable = VK_FALSE,
		.stencilTestEnable = VK_FALSE,
		.front = {},
		.back = {},
		.minDepthBounds = 0.0f,
		.maxDepthBounds = 1.0f
	};



	/*VkPipelineColorBlendAttachmentState colorBlendAttachment
	{
		.blendEnable = VK_FALSE,
		.srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
		.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
		.colorBlendOp = VK_BLEND_OP_ADD,
		.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
		.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
		.alphaBlendOp = VK_BLEND_OP_ADD,
		.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
	};*/

	std::vector<VkPipelineColorBlendAttachmentState> color_blend_attachments(attachment_formats.size());
	for (size_t i = 0; i < attachment_formats.size(); i++)
	{
		VkPipelineColorBlendAttachmentState color_blend_attachment
		{
			.blendEnable = blend_enable,
			.srcColorBlendFactor = src_color_blend_factor,
			.dstColorBlendFactor = dst_color_blend_factor,
			.colorBlendOp = color_blend_op,
			.srcAlphaBlendFactor = src_alpha_blend_factor,
			.dstAlphaBlendFactor = dst_alpha_blend_factor,
			.alphaBlendOp = alpha_blend_op,
			.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
		};

		color_blend_attachments[i] = color_blend_attachment;
	}

	VkPipelineColorBlendStateCreateInfo color_blend_ci =
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.logicOpEnable = VK_FALSE,
		.logicOp = VK_LOGIC_OP_CLEAR,
		.attachmentCount = uint32_t(color_blend_attachments.size()),
		.pAttachments = color_blend_attachments.data(),
		.blendConstants = {}
	};

	//VkFormat attachment_formats[1] { swapchain_format };
	const VkPipelineRenderingCreateInfo pipeline_rendering_ci
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO,
		.pNext = nullptr,
		.viewMask = 0,
		.colorAttachmentCount = uint32_t(attachment_formats.size()),
		.pColorAttachmentFormats = attachment_formats.data(),
		.depthAttachmentFormat = depth_format,
		.stencilAttachmentFormat = VK_FORMAT_UNDEFINED,
	};

	std::array dynamic_states { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR, VK_DYNAMIC_STATE_CULL_MODE };

	VkPipelineDynamicStateCreateInfo dynamic_state_ci
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.dynamicStateCount = uint32_t(dynamic_states.size()),
		.pDynamicStates = dynamic_states.data(),
	};

	/*std::vector<VkPipeline> libraries {};

	VkPipelineLibraryCreateInfoKHR library_ci
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LIBRARY_CREATE_INFO_KHR,
		.pNext = &pipeline_rendering_ci,
		.libraryCount = uint32_t(libraries.size()),
		.pLibraries = libraries.data(),
	};*/

	VkGraphicsPipelineCreateInfo pipeline_ci =
	{
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.pNext = &pipeline_rendering_ci,
		.flags = 0,
		.stageCount = uint32_t(shader_stage_ci_array.size()),
		.pStages = shader_stage_ci_array.data(),
		.pVertexInputState = &vertex_input_ci,
		.pInputAssemblyState = &input_assembly_ci,
		.pTessellationState = nullptr,
		.pViewportState = &viewport_ci,
		.pRasterizationState = &rasterization_ci,
		.pMultisampleState = &multisample_ci,
		.pDepthStencilState = &depth_stencil_ci,
		.pColorBlendState = &color_blend_ci,
		.pDynamicState = &dynamic_state_ci,
		.layout = layout,
		.renderPass = VK_NULL_HANDLE,
		.subpass = 0,
		.basePipelineHandle = VK_NULL_HANDLE,
		.basePipelineIndex = -1
	};

	VkPipeline pipeline;
	VkResult result = vkCreateGraphicsPipelines(device, pipeline_cache, 1, &pipeline_ci, nullptr, &pipeline);
	if (result != VK_SUCCESS)
	{
		Log() << "vkCreateGraphicsPipelines failed";
		return VK_NULL_HANDLE;
	}

	return pipeline;
}

/*VkPipeline GraphicsPipelineBuilder::Result()
{
	return pipeline;
}*/



BF_END_VK_NAMESPACE
BF_END_NAMESPACE
