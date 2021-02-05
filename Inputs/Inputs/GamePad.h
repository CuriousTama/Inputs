#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <Windows.h>
#include <Xinput.h>
#include <chrono>

#pragma warning(disable : 26812) // disable warning of using enum
#pragma warning(disable : 5105)  // disable undefined #define in winbase.h

namespace Xbox_one_
{
	enum Button
	{
		A = 0x1000,
		B = 0x2000,
		X = 0x4000,
		Y = 0x8000,
		LB = 0x0100,
		RB = 0x0200,
		Select = 0x0020,
		Start = 0x0010,
		LeftStickPress = 0x0040,
		RightStickPress = 0x0080,
		Cross_Left = 0x0004,
		Cross_Right = 0x0008,
		Cross_Up = 0x0001,
		Cross_Down = 0x0002
	};

	enum Trigger
	{
		LT,
		RT
	};

	enum Axis
	{
		LeftJoystick_Left,
		LeftJoystick_Right,
		LeftJoystick_Up,
		LeftJoystick_Down,
		RightJoystick_Left,
		RightJoystick_Right,
		RightJoystick_Up,
		RightJoystick_Down
	};

}

class Xbox_one
{
	struct pad
	{
		XINPUT_VIBRATION* vibration = nullptr;
		float vibration_time = 0.f;

		XINPUT_STATE previous{ 0 };
		XINPUT_STATE actual{ 0 };
		bool connected = false;

	} Gamepads[4];

	void _Trigger(unsigned short pad, Xbox_one_::Trigger trigger, bool& a, bool& b);
	void _Axis(unsigned short pad, Xbox_one_::Axis axis, bool& a, bool& b);

	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

public:
	Xbox_one() { this->GamePadUpdate(); };
	~Xbox_one() = default;


	void GamePadUpdate();

	bool isConnected(unsigned short pad);
	unsigned char BatteryLevel(unsigned short pad);
	void vibration(unsigned short pad, unsigned char power, float time);
	void vibration(unsigned short pad, bool on, unsigned char power = 50);

	float TriggerPression(unsigned short pad, Xbox_one_::Trigger trigger);
	float AxisPression(unsigned short pad, Xbox_one_::Axis	axis);

	bool isPressed(unsigned short pad, unsigned short		button);
	bool isPressed(unsigned short pad, Xbox_one_::Button	button);
	bool isPressed(unsigned short pad, Xbox_one_::Trigger	trigger);
	bool isPressed(unsigned short pad, Xbox_one_::Axis		axis);

	bool onPressed(unsigned short pad, unsigned short		button);
	bool onPressed(unsigned short pad, Xbox_one_::Button	button);
	bool onPressed(unsigned short pad, Xbox_one_::Trigger	trigger);
	bool onPressed(unsigned short pad, Xbox_one_::Axis		axis);

	bool OnRelease(unsigned short pad, unsigned short		button);
	bool OnRelease(unsigned short pad, Xbox_one_::Button	button);
	bool OnRelease(unsigned short pad, Xbox_one_::Trigger	trigger);
	bool OnRelease(unsigned short pad, Xbox_one_::Axis		axis);
};

#endif // !GAMEPAD_H