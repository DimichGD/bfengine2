#pragma once
#include "graphics/render_device.hpp"

BF_BEGIN_NAMESPACE

class UIManager
{
public:
	UIManager(RenderDevice *device);

private:
	RenderDevice *device = nullptr;
};

BF_END_NAMESPACE
