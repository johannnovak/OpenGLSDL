#pragma once

#include <string>

#include "LogManager.h"

enum KeyId
{
	IM_KEY_A = 0x00,
	IM_KEY_B = 0x01,
	IM_KEY_C = 0x02,
	IM_KEY_D = 0x03,
	IM_KEY_E = 0x04,
	IM_KEY_F = 0x05,
	IM_KEY_G = 0x06,
	IM_KEY_H = 0x07,
	IM_KEY_I = 0x08,
	IM_KEY_J = 0x09,
	IM_KEY_K = 0x0A,
	IM_KEY_L = 0x0B,
	IM_KEY_M = 0x0C,
	IM_KEY_N = 0x0D,
	IM_KEY_O = 0x0E,
	IM_KEY_P = 0x0F,
	IM_KEY_Q = 0x10,
	IM_KEY_R = 0x11,
	IM_KEY_S = 0x12,
	IM_KEY_T = 0x13,
	IM_KEY_U = 0x14,
	IM_KEY_V = 0x15,
	IM_KEY_W = 0x16,
	IM_KEY_X = 0x17,
	IM_KEY_Y = 0x18,
	IM_KEY_Z = 0x19,

	IM_KEY_1 = 0x1A,
	IM_KEY_2 = 0x1B,
	IM_KEY_3 = 0x1C,
	IM_KEY_4 = 0x1D,
	IM_KEY_5 = 0x1E,
	IM_KEY_6 = 0x1F,
	IM_KEY_7 = 0x20,
	IM_KEY_8 = 0x21,
	IM_KEY_9 = 0x22,
	IM_KEY_0 = 0x23,

	IM_KEY_UP = 0x24,
	IM_KEY_DOWN = 0x25,
	IM_KEY_LEFT = 0x26,
	IM_KEY_RIGHT = 0x27,

	IM_KEY_ESCAPE = 0x28,

	IM_KEY_LAST

};

enum MouseButtonId
{
	IM_MOUSE_LEFT = 0x0,
	IM_MOUSE_RIGHT = 0x1,
	IM_MOUSE_MIDDLE = 0x2,

	IM_MOUSE_LAST
};

enum InputManagerType
{
	IM_TYPE_SDL = 0,

	IM_TYPE_LAST
};

class MouseMotion
{
public:
	MouseMotion();

	int x;
	int y;

	int dx;
	int dy;
};

class InputManager
{
public:
	InputManager();
	virtual ~InputManager();

public:
	static InputManager* getInstance();

	static std::string IMTypeToStr(InputManagerType _type);

public:
	virtual bool isKeyDown(KeyId _keyId) = 0;
	virtual bool isKeyUp(KeyId _keyId) = 0;

	virtual bool isMouseButtonDown(MouseButtonId _mouseId) = 0;
	virtual bool isMouseButtonUp(MouseButtonId _mouseId) = 0;

	virtual MouseMotion& getMouseMotion() = 0;
	virtual void resetMouseMotion() = 0;

protected:
	static InputManager* s_instance;
};