#pragma once
#include "engine/resource_manager.hpp"
#include "graphics/vulkan/render_device_vk.hpp"

BF_BEGIN_NAMESPACE

struct GraphicsContext
{
	GPUBuffer active_camera_ubo {};
	GPUBuffer model_matrices_ubo {};
	GPUBuffer colors_ubo {};
};

BF_END_NAMESPACE
