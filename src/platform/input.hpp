#pragma once
#include "core/defines.hpp"
#include <cstdint>
#include <vector>
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
