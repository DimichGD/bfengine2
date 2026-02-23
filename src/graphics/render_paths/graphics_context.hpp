#pragma once
#include "graphics/types.hpp"

BF_BEGIN_NAMESPACE

struct GraphicsContext
{
	GPUBuffer active_camera_ubo {};
	GPUBuffer model_matrices_ubo {};
	GPUBuffer colors_ubo {};
	GPUBuffer point_lights_ubo {};
	GPUBuffer camera_pos_ubo {};
};

BF_END_NAMESPACE
