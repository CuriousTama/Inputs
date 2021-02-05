#include "GamePad.h"
#include <iostream>

#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")

float Xbox_one::TriggerPression(unsigned short pad, Xbox_one_::Trigger trigger)
{
	if (trigger == Xbox_one_::Trigger::LT)
		return Gamepads[pad].actual.Gamepad.bLeftTrigger / 2.55f;
	else if (trigger == Xbox_one_::Trigger::RT)
		return Gamepads[pad].actual.Gamepad.bRightTrigger / 2.55f;

	return 0.f;
}

float Xbox_one::AxisPression(unsigned short pad, Xbox_one_::Axis axis)
{
	if (axis == Xbox_one_::Axis::LeftJoystick_Left || axis == Xbox_one_::Axis::LeftJoystick_Right)
		return Gamepads[pad].actual.Gamepad.sThumbLX / 327.67f;
	else if (axis == Xbox_one_::Axis::LeftJoystick_Up || axis == Xbox_one_::Axis::LeftJoystick_Down)
		return Gamepads[pad].actual.Gamepad.sThumbLY / 327.67f;

	else if (axis == Xbox_one_::Axis::RightJoystick_Left || axis == Xbox_one_::Axis::RightJoystick_Right)
		return Gamepads[pad].actual.Gamepad.sThumbRX / 327.67f;
	else if (axis == Xbox_one_::Axis::RightJoystick_Up || axis == Xbox_one_::Axis::RightJoystick_Down)
		return Gamepads[pad].actual.Gamepad.sThumbRY / 327.67f;

	return 0.f;
}


void Xbox_one::vibration(unsigned short _pad, unsigned char power, float time)
{
	if (Gamepads[_pad].vibration == nullptr)
	{
		XINPUT_VIBRATION vibration;
		SecureZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		Gamepads[_pad].vibration = &vibration;
	}

	if (power > 100) power = 100;

	Gamepads[_pad].vibration->wLeftMotorSpeed = (unsigned short)(power * 655.35f);
	Gamepads[_pad].vibration->wRightMotorSpeed = (unsigned short)(power * 655.35f);

	XInputSetState(_pad, Gamepads[_pad].vibration);

	Gamepads[_pad].vibration_time = time;
}

void Xbox_one::vibration(unsigned short pad, bool on, unsigned char power)
{
	if (Gamepads[pad].vibration == nullptr)
	{
		XINPUT_VIBRATION vibration;
		SecureZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		Gamepads[pad].vibration = &vibration;
	}

	if (power > 100) power = 100;
	if (!on) power = 0;

	Gamepads[pad].vibration->wLeftMotorSpeed = (unsigned short)(power * 655.35f);
	Gamepads[pad].vibration->wRightMotorSpeed = (unsigned short)(power * 655.35f);

	XInputSetState(pad, Gamepads[pad].vibration);
}

bool Xbox_one::isPressed(unsigned short pad, unsigned short button)
{
	return Gamepads[pad].actual.Gamepad.wButtons & button;
}

bool Xbox_one::isPressed(unsigned short pad, Xbox_one_::Button button)
{
	return Gamepads[pad].actual.Gamepad.wButtons & button;
}

bool Xbox_one::isPressed(unsigned short pad, Xbox_one_::Trigger trigger)
{
	bool a = false, b = false;
	_Trigger(pad, trigger, a, b);
	return b;
}

bool Xbox_one::isPressed(unsigned short pad, Xbox_one_::Axis axis)
{
	bool a = false, b = false;
	_Axis(pad, axis, a, b);
	return b;
}

bool Xbox_one::onPressed(unsigned short pad, unsigned short button)
{
	bool a = Gamepads[pad].previous.Gamepad.wButtons & button;
	bool b = Gamepads[pad].actual.Gamepad.wButtons & button;
	return !a && b;
}

bool Xbox_one::onPressed(unsigned short pad, Xbox_one_::Button button)
{
	bool a = Gamepads[pad].previous.Gamepad.wButtons & button;
	bool b = Gamepads[pad].actual.Gamepad.wButtons & button;
	return !a && b;
}

bool Xbox_one::onPressed(unsigned short pad, Xbox_one_::Trigger trigger)
{
	bool a = false, b = false;
	_Trigger(pad, trigger, a, b);
	return !a && b;
}

bool Xbox_one::onPressed(unsigned short pad, Xbox_one_::Axis axis)
{
	bool a = false, b = false;
	_Axis(pad, axis, a, b);
	return !a && b;
}


bool Xbox_one::OnRelease(unsigned short pad, unsigned short button)
{
	bool a = Gamepads[pad].previous.Gamepad.wButtons & button;
	bool b = Gamepads[pad].actual.Gamepad.wButtons & button;
	return a && !b;
}

bool Xbox_one::OnRelease(unsigned short pad, Xbox_one_::Button button)
{
	bool a = Gamepads[pad].previous.Gamepad.wButtons & (int)button;
	bool b = Gamepads[pad].actual.Gamepad.wButtons & (int)button;
	return a && !b;
}

bool Xbox_one::OnRelease(unsigned short pad, Xbox_one_::Trigger trigger)
{
	bool a = false, b = false;
	_Trigger(pad, trigger, a, b);
	return a && !b;
}

bool Xbox_one::OnRelease(unsigned short pad, Xbox_one_::Axis axis)
{
	bool a = false, b = false;
	_Axis(pad, axis, a, b);
	return a && !b;
}

bool Xbox_one::isConnected(unsigned short pad)
{
	return Gamepads[pad].connected;
}

unsigned char Xbox_one::BatteryLevel(unsigned short pad)
{
#if INTPTR_MAX == INT32_MAX 

	XINPUT_BATTERY_INFORMATION battery;
	SecureZeroMemory(&battery, sizeof(XINPUT_BATTERY_INFORMATION));
	XInputGetBatteryInformation(pad, BATTERY_DEVTYPE_GAMEPAD, &battery);

	return battery.BatteryLevel;

#elif INTPTR_MAX == INT64_MAX 

#if NDEBUG
	return BATTERY_LEVEL_FULL;
#else
	std::cerr << "\033[33m" << "DEBUG >> " << "GamePad Battery level don't work on x64." << "\033[0m" << std::endl;
	return BATTERY_LEVEL_FULL;
#endif
#endif
}


void Xbox_one::GamePadUpdate()
{
	float elapsed = std::chrono::duration<float>(std::chrono::steady_clock::now() - start).count();
	start = std::chrono::steady_clock::now();

	for (int i = 0; i < 4; i++)
	{
		// check new
		Gamepads[i].previous = Gamepads[i].actual;
		if (XInputGetState(i, &Gamepads[i].actual) == ERROR_SUCCESS)
			Gamepads[i].connected = true;
		else
			Gamepads[i].connected = false;

		// vibrations
		if (Gamepads[i].vibration_time > 0)
		{
			Gamepads[i].vibration_time -= elapsed;

			if (Gamepads[i].vibration_time <= 0)
			{
				Gamepads[i].vibration->wLeftMotorSpeed = 0;
				Gamepads[i].vibration->wRightMotorSpeed = 0;
				XInputSetState(i, Gamepads[i].vibration);
			}
		}
	}
}


void Xbox_one::_Trigger(unsigned short pad, Xbox_one_::Trigger trigger, bool& a, bool& b)
{
	if (trigger == Xbox_one_::Trigger::LT)
	{
		a = Gamepads[pad].previous.Gamepad.bLeftTrigger > 30;
		b = Gamepads[pad].actual.Gamepad.bLeftTrigger > 30;
	}
	else
	{
		a = Gamepads[pad].previous.Gamepad.bRightTrigger > 30;
		b = Gamepads[pad].actual.Gamepad.bRightTrigger > 30;
	}
}

void Xbox_one::_Axis(unsigned short pad, Xbox_one_::Axis axis, bool& a, bool& b)
{
	if (axis == Xbox_one_::Axis::LeftJoystick_Left || axis == Xbox_one_::Axis::LeftJoystick_Right)
	{
		if (axis == Xbox_one_::Axis::LeftJoystick_Left)
		{
			a = (float)Gamepads[pad].previous.Gamepad.sThumbLX / 327.67f < -30;
			b = (float)Gamepads[pad].actual.Gamepad.sThumbLX / 327.67f < -30;
		}
		else
		{
			a = (float)Gamepads[pad].previous.Gamepad.sThumbLX / 327.67f > 30;
			b = (float)Gamepads[pad].actual.Gamepad.sThumbLX / 327.67f > 30;
		}
	}

	else if (axis == Xbox_one_::Axis::LeftJoystick_Up || axis == Xbox_one_::Axis::LeftJoystick_Down)
	{
		if (axis == Xbox_one_::Axis::LeftJoystick_Up)
		{
			a = (float)Gamepads[pad].previous.Gamepad.sThumbLY / 327.67f > 30;
			b = (float)Gamepads[pad].actual.Gamepad.sThumbLY / 327.67f > 30;
		}
		else
		{
			a = (float)Gamepads[pad].previous.Gamepad.sThumbLY / 327.67f < -30;
			b = (float)Gamepads[pad].actual.Gamepad.sThumbLY / 327.67f < -30;
		}
	}

	else if (axis == Xbox_one_::Axis::RightJoystick_Left || axis == Xbox_one_::Axis::RightJoystick_Right)
	{
		if (axis == Xbox_one_::Axis::RightJoystick_Left)
		{
			a = (float)Gamepads[pad].previous.Gamepad.sThumbRX / 327.67f < -30;
			b = (float)Gamepads[pad].actual.Gamepad.sThumbRX / 327.67f < -30;
		}
		else
		{
			a = (float)Gamepads[pad].previous.Gamepad.sThumbRX / 327.67f > 30;
			b = (float)Gamepads[pad].actual.Gamepad.sThumbRX / 327.67f > 30;
		}
	}

	else if (axis == Xbox_one_::Axis::RightJoystick_Up || axis == Xbox_one_::Axis::RightJoystick_Down)
	{
		if (axis == Xbox_one_::Axis::RightJoystick_Up)
		{
			a = (float)Gamepads[pad].previous.Gamepad.sThumbRY / 327.67f > 30;
			b = (float)Gamepads[pad].actual.Gamepad.sThumbRY / 327.67f > 30;
		}
		else
		{
			a = (float)Gamepads[pad].previous.Gamepad.sThumbRY / 327.67f < -30;
			b = (float)Gamepads[pad].actual.Gamepad.sThumbRY / 327.67f < -30;
		}
	}
}
