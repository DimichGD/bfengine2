#pragma once
#include "core/defines.hpp"
#include "graphics/render_paths/graphics_context.hpp"

BF_BEGIN_NAMESPACE

class RenderPass2
{
public:
	void AddAttachment(const std::string &name, const TextureDesc &desc)
	{
		attachments[name] = desc;
	}

	void AddInput(const std::string &name);

	std::function<void()> Render();

	std::map<std::string, TextureDesc> attachments;
	std::vector<std::string> inputs;
};

class FrameGraph
{
public:
	//

	std::vector<RenderPass2> passes;
};

BF_END_NAMESPACE
