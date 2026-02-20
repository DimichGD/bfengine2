#include "input.hpp"
#include "core/log.hpp"
#include <SDL2/SDL_scancode.h>

BF_BEGIN_NAMESPACE

/*Input::Input()
{
	keys.resize(SDL_NUM_SCANCODES, 0);
}

void Input::Reset()
{
	std::fill(keys.begin(), keys.end(), 0);
	std::fill(buttons.begin(), buttons.end(), 0);

	mouse_x = 0;
	mouse_y = 0;
	mouse_dx = 0;
	mouse_dy = 0;
}

void Input::ProcessKeyboardEvent(int key, int state)
{
	Log() << "key" << key << (state ? "up" : "down");
}

void Input::ProcessMouseMoveEvent(int x, int y, int dx, int dy)
{
	//
}

void Input::ProcessMouseButtonEvent(int button, int state, int clicks)
{
	Log() << "mouse button" << button << (state ? "up" : "down") << clicks;
}

int Input::KeyDown(int key) const
{
	if (key < 0 || key >= SDL_NUM_SCANCODES)
		return 0;

	return keys[key];
}*/



BF_END_NAMESPACE
