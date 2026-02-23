#include "window_sdl2.hpp"
#include "core/log.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.h>

BF_BEGIN_NAMESPACE

struct WindowSDL3::Internal
{
	SDL_Window *wnd = nullptr;
	SDL_GLContext ctx = nullptr;
	bool done = false;

	//VkInstance instance = nullptr;
	//VkSurfaceKHR surface = nullptr;
};

WindowSDL3::WindowSDL3(Config *config)
{
	this->config = config;
	this->stuff = new Internal;
}

WindowSDL3::~WindowSDL3()
{
	delete stuff;
}

bool WindowSDL3::Create()
{
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
	{
		Log() << SDL_GetError();
		return false;
	}

	if (config->render.api == Config::Render::API::VK)
	{
		if (!CreateVulkan())
		{
			config->render.api = Config::Render::API::GL;
			//return false;
		}
	}

	if (config->render.api == Config::Render::API::GL)
	{
		if (!CreateOpenGL(4, 6))
			return false;
	}

	return true;
}

bool WindowSDL3::CreateOpenGL(int major, int minor)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
	//SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);

	if (config->render.debug && major > 3)
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	}
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 1);

	//int pos = SDL_WINDOWPOS_CENTERED_DISPLAY(config->window.monitor);
	stuff->wnd = SDL_CreateWindow("", /*pos, pos,*/ config->window.width, config->window.height,
								  SDL_WINDOW_OPENGL /*| SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED*/);

	if (stuff->wnd == nullptr)
	{
		Log() << "SDL_CreateWindow failed" << SDL_GetError();
		return false;
	}

	//SDL_SetWindowSize(stuff->wnd, config->width, config->height);
	//SDL_SetWindowPosition(stuff->wnd, SDL_WINDOWPOS_CENTERED_DISPLAY(0), SDL_WINDOWPOS_CENTERED_DISPLAY(0));

	stuff->ctx = SDL_GL_CreateContext(stuff->wnd);
	if (stuff->ctx == nullptr)
	{
		Log() << "SDL_GL_CreateContext failed" << SDL_GetError();
		return false;
	}

	if (!SDL_GL_MakeCurrent(stuff->wnd, stuff->ctx))
	{
		Log() << "SDL_GL_MakeCurrent failed" << SDL_GetError();
		return false;
	}

	if (!SetSwapInterval(config->window.swap_interval))
	{
		Log() << "SDL_GL_SetSwapInterval failed" << SDL_GetError();
		return false;
	}

	//SDL_StopTextInput(stuff->wnd);

	return true;
}

bool WindowSDL3::CreateVulkan()
{
	//int pos = SDL_WINDOWPOS_CENTERED_DISPLAY(config->window.monitor);
	stuff->wnd = SDL_CreateWindow("", /*pos, pos,*/ config->window.width, config->window.height,
								  SDL_WINDOW_VULKAN /*| SDL_WINDOW_ALLOW_HIGHDPI*/);

	if (stuff->wnd == nullptr)
	{
		Log() << "SDL_CreateWindow failed" << SDL_GetError();
		return false;
	}

	return true;
}

bool WindowSDL3::Update(InputHandler &input)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_EVENT_QUIT:
				Close();
				break;

			/*case SDL_DISPLAYEVENT:
				// nothing interesting
				break;*/

			case SDL_EVENT_WINDOW_MINIMIZED:
				minimized = true;
				break;

			case SDL_EVENT_WINDOW_MAXIMIZED:
				minimized = false;
				break;

			case SDL_EVENT_WINDOW_FOCUS_LOST:
				break;

			case SDL_EVENT_WINDOW_FOCUS_GAINED:
				break;

			case SDL_EVENT_WINDOW_RESIZED:
				Log() << event.window.data1 << event.window.data2;
				break;

			case SDL_EVENT_WINDOW_DISPLAY_CHANGED:
				break;

			case SDL_EVENT_KEY_DOWN:
				if (event.key.repeat == 0)
					input.KeyDown(event.key.scancode);
				break;

			case SDL_EVENT_KEY_UP:
				input.KeyUp(event.key.scancode);
				break;

			case SDL_EVENT_TEXT_INPUT:
				//Log() << event.text.text;
				break;

			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				input.MouseDown(event.button.button);
				break;

			case SDL_EVENT_MOUSE_BUTTON_UP:
				//input.ProcessEvent(MouseButtonEvent { event.button.button, event.button.state, event.button.clicks });
				input.MouseUp(event.button.button);
				break;

			case SDL_EVENT_MOUSE_WHEEL:
				//input.ProcessEvent(MouseWheelEvent { event.wheel.y });
				break;

			case SDL_EVENT_MOUSE_MOTION:
				//mouse_dx += event.motion.xrel;
				//mouse_dy += event.motion.yrel;
				input.MouseMove(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
				//input.ProcessEvent(MouseMoveEvent { event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel });
				break;

			case SDL_EVENT_GAMEPAD_AXIS_MOTION:
				//Log() << (int)event.caxis.axis << event.caxis.value;
				input.GamepadAxis(event.gaxis.axis, event.gaxis.value);
				break;

			case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
				Log() << int(event.gbutton.button);
				break;

			case SDL_EVENT_GAMEPAD_BUTTON_UP:
				break;

			case SDL_EVENT_GAMEPAD_ADDED:
				/*Log() << "SDL_CONTROLLERDEVICEADDED" << event.cdevice.which;
				{
					SDL_GameController *gamepad = SDL_GameControllerOpen(event.cdevice.which);
					Log() << SDL_GameControllerName(gamepad);
					Log() << SDL_GameControllerGetType(gamepad);
				}*/
				SDL_OpenGamepad(event.gdevice.which);
				//SDL_GameControllerOpen(event.cdevice.which);
				break;

			case SDL_EVENT_GAMEPAD_REMOVED:
				//Log() << "SDL_CONTROLLERDEVICEREMOVED" << event.cdevice.which;
				break;

			case SDL_EVENT_GAMEPAD_REMAPPED:
				//Log() << "SDL_CONTROLLERDEVICEREMAPPED" << event.cdevice.which;
				break;

			case SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN:
				break;

			case SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION:
				break;

			case SDL_EVENT_GAMEPAD_TOUCHPAD_UP:
				break;
		}
	}

	return !stuff->done;
}

void WindowSDL3::Swap()
{
	SDL_GL_SwapWindow(stuff->wnd);
}

void WindowSDL3::Close()
{
	stuff->done = true;
}

void WindowSDL3::Destroy()
{
	if (stuff->ctx)
		SDL_GL_DestroyContext(stuff->ctx);

	SDL_DestroyWindow(stuff->wnd);
	SDL_Quit();
}

void WindowSDL3::CaptureMouse(bool capture)
{
	if (!SDL_SetWindowRelativeMouseMode(stuff->wnd, capture))
		Log() << "SDL_SetRelativeMouseMode failed" << SDL_GetError();
}

bool WindowSDL3::SetSwapInterval(int interval)
{
	if (stuff->ctx)
		return (SDL_GL_SetSwapInterval(interval));

	else
		return true;
}

/*std::span<const uint8_t> WindowSDL2::KeyboardState()
{
	int count = 0;
	const Uint8 *state = SDL_GetKeyboardState(&count);
	return { state, state + count };
}*/

glm::ivec2 WindowSDL3::Size()
{
	glm::ivec2 size {};

	if (stuff->ctx)
		SDL_GetWindowSizeInPixels(stuff->wnd, &size.x, &size.y);
		//SDL_GL_GetDrawableSize(stuff->wnd, &size.x, &size.y);

	else
		SDL_GetWindowSizeInPixels(stuff->wnd, &size.x, &size.y);
		//SDL_Vulkan_GetDrawableSize(stuff->wnd, &size.x, &size.y);

	return size;
}

SDL_Window *WindowSDL3::WindowHandle()
{
	return stuff->wnd;
}

BF_END_NAMESPACE
