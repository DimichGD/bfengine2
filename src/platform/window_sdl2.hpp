#pragma once
#include "core/config.hpp"
#include "core/defines.hpp"
#include "platform/input.hpp"
#include <glm/vec2.hpp>
//#include <span>

struct SDL_Window;

BF_BEGIN_NAMESPACE

class WindowSDL3
{
public:
	WindowSDL3(Config *config);
	~WindowSDL3();

	BF_NON_COPYABLE(WindowSDL3)
	BF_NON_MOVABLE(WindowSDL3)

	bool Create();
	bool Update(InputHandler &input);
	void Swap();
	void Close();
	void Destroy();

	void CaptureMouse(bool capture);
	bool SetSwapInterval(int interval);

	bool Minimized() const { return minimized; }
	glm::ivec2 Size();
	SDL_Window *WindowHandle();

private:
	bool CreateOpenGL(int major, int minor);
	bool CreateVulkan();

private:
	struct Internal;
	Internal *stuff = nullptr;
	Config *config = nullptr;

	bool minimized = false;
};

BF_END_NAMESPACE
