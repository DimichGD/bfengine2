#pragma once
#include "graphics/types.hpp"

BF_BEGIN_NAMESPACE

struct GraphicsFrameData
{
	GPUBuffer active_camera_ubo {};
	GPUBuffer model_matrices_ubo {};
	GPUBuffer colors_ubo {};
	GPUBuffer point_lights_ubo {};
	GPUBuffer camera_light_data {};
	GPUBuffer text_vbo {};

	//DescriptorSet vertex_set {};
};

struct GraphicsData
{
	std::vector<GraphicsFrameData> frame_data;
	DescriptorSet textures_set {};
};

struct GraphicsContext
{
	GPUBuffer active_camera_ubo {};
	GPUBuffer model_matrices_ubo {};
	GPUBuffer colors_ubo {};
	GPUBuffer point_lights_ubo {};
	GPUBuffer camera_light_data {};

	GPUBuffer text_vbo {};
};

BF_END_NAMESPACE
