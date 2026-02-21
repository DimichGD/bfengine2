#pragma once
#include "core/defines.hpp"
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_scancode.h>
#include <cstdint>
#include <glm/ext/vector_float2.hpp>
#include <vector>
#include <algorithm>
#include <array>

BF_BEGIN_NAMESPACE

class InputHandler
{
public:
	virtual ~InputHandler() = default;
	virtual void KeyDown(uint32_t key) = 0;
	virtual void KeyUp(uint32_t key) = 0;
	virtual void MouseDown(int button) {};
	virtual void MouseUp(int button) {};
	virtual void MouseMove(float x, float y, float dx, float dy) {};
	virtual void GamepadAxis(int axis, int value) {};
	virtual void GamepadButton() {};
};

class Input: public InputHandler
{
public:
	Input()
	{
		std::fill(keys.begin(), keys.end(), {});
	}

	void KeyDown(uint32_t key) override
	{
		kbm = true;

		keys[key].just_pressed = 1;
		//keys[key].just_released = 0;
		keys[key].pressed = 1;

		/*auto it = std::find_if(actions2.begin(), actions2.end(), [key](const Action2 &n)
		{
			return n.key == key;
		});

		if (it != actions2.end())
			it->func();*/
	}

	void KeyUp(uint32_t key) override
	{
		kbm = true;

		//keys[key].just_pressed = 0;
		keys[key].just_released = 1;
		keys[key].pressed = 0;
	}

	void MouseMove(float x, float y, float dx, float dy) override
	{
		mouse_delta.x += dx;
		mouse_delta.y += dy;
		mouse_pos.x = x;
		mouse_pos.y = y;
	}

	void GamepadAxis(int axis, int value) override
	{
		kbm = false;

		switch (axis)
		{
			case SDL_GAMEPAD_AXIS_LEFTX: left_stick.x = value / 32767.0f; break;
			case SDL_GAMEPAD_AXIS_LEFTY: left_stick.y = value / 32767.0f; break;
			case SDL_GAMEPAD_AXIS_RIGHTX: right_stick.x = value / 32767.0f; break;
			case SDL_GAMEPAD_AXIS_RIGHTY: right_stick.y = value / 32767.0f; break;
		}
	}

	void Flush()
	{
		mouse_delta = {};

		for (int i = 0; i < SDL_SCANCODE_COUNT; i++)
		{
			keys[i].just_pressed = 0;
			keys[i].just_released = 0;
		}
	}

	int8_t KeyPressed(uint32_t key)
	{
		return keys[key].pressed;
	}

	int8_t KeyJustPressed(uint32_t key)
	{
		return keys[key].just_pressed;
	}

	int8_t KeyJustReleased(uint32_t key)
	{
		return keys[key].just_released;
	}

	const glm::vec2 MousePos() const
	{
		return mouse_pos;
	}

	const glm::vec2 MouseRelativePos() const
	{
		return mouse_delta;
	}

	bool IsKBM() const
	{
		return kbm;
	}

	/*void BindAction(uint32_t key, std::function<void()> func)
	{
		actions2.push_back({ key, func });
	}*/

	const glm::vec2 LeftStick() const
	{
		return left_stick;
	}

	const glm::vec2 RightStick() const
	{
		return right_stick;
	}

private:
	struct KeyState
	{
		uint8_t pressed: 1 = 0;
		uint8_t just_pressed: 1 = 0;
		uint8_t just_released: 1 = 0;
	};

	bool kbm = true;

	glm::vec2 mouse_delta {};
	glm::vec2 mouse_pos {};
	std::array<KeyState, SDL_SCANCODE_COUNT> keys;

	glm::vec2 left_stick {};
	glm::vec2 right_stick {};

	/*struct Action2
	{
		uint32_t key;
		std::function<void()> func;
	};

	std::vector<Action2> actions2;*/
};

/*class Input
{
public:
	Input();

	void Reset();
	void ProcessKeyboardEvent(int key, int state);
	void ProcessMouseMoveEvent(int x, int y, int dx, int dy);
	void ProcessMouseButtonEvent(int button, int state, int clicks);

	int KeyDown(int key) const;
	int MouseX() const { return mouse_x; }
	int MouseY() const { return mouse_y; }
	//int MouseDX() const { return mouse_dx; }
	//int MouseDY() const { return mouse_dy; }

private:
	std::vector<int8_t> keys {};
	std::array<int8_t, 5> buttons {};

	int mouse_x = 0;
	int mouse_y = 0;
	int mouse_dx = 0;
	int mouse_dy = 0;
};*/

BF_END_NAMESPACE
