#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <Windows.h>
#include <Xinput.h>
#include <chrono>
#include <algorithm>

#include "Errors.h"

#pragma comment(lib, "Xinput9_1_0.lib") // XInput
#pragma comment(lib, "ole32.lib")		// CoInitializeEx function

#pragma warning( push )
#pragma warning(disable : 26812) // disable warning of using enum

namespace Xbox {
	enum Button {
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

	enum Trigger {
		LT,
		RT
	};

	enum Axis {
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

class Xbox_one {
	struct pad {
		XINPUT_VIBRATION* vibration{ nullptr };
		float vibration_time{ 0.f };

		XINPUT_STATE previous{ 0 };
		XINPUT_STATE actual{ 0 };
		bool connected{ false };
	} Gamepads[4];

	std::chrono::steady_clock::time_point start{ std::chrono::steady_clock::now() };

	void _Trigger(unsigned short pad, Xbox::Trigger trigger, bool& a, bool& b) {
		if (!checkPad(pad)) {
			return;
		}

		if (trigger == Xbox::Trigger::LT) {
			a = Gamepads[pad].previous.Gamepad.bLeftTrigger > 30;
			b = Gamepads[pad].actual.Gamepad.bLeftTrigger > 30;
		}
		else {
			a = Gamepads[pad].previous.Gamepad.bRightTrigger > 30;
			b = Gamepads[pad].actual.Gamepad.bRightTrigger > 30;
		}
	}

	void _Axis(unsigned short pad, Xbox::Axis axis, bool& a, bool& b) {
		if (!checkPad(pad)) {
			return;
		}

		if (axis == Xbox::Axis::LeftJoystick_Left || axis == Xbox::Axis::LeftJoystick_Right) {

			if (axis == Xbox::Axis::LeftJoystick_Left) {
				a = (float)Gamepads[pad].previous.Gamepad.sThumbLX / 327.67f < -30;
				b = (float)Gamepads[pad].actual.Gamepad.sThumbLX / 327.67f < -30;
			}
			else {
				a = (float)Gamepads[pad].previous.Gamepad.sThumbLX / 327.67f > 30;
				b = (float)Gamepads[pad].actual.Gamepad.sThumbLX / 327.67f > 30;
			}

			return;
		}

		if (axis == Xbox::Axis::LeftJoystick_Up || axis == Xbox::Axis::LeftJoystick_Down) {

			if (axis == Xbox::Axis::LeftJoystick_Up) {
				a = (float)Gamepads[pad].previous.Gamepad.sThumbLY / 327.67f > 30;
				b = (float)Gamepads[pad].actual.Gamepad.sThumbLY / 327.67f > 30;
			}
			else {
				a = (float)Gamepads[pad].previous.Gamepad.sThumbLY / 327.67f < -30;
				b = (float)Gamepads[pad].actual.Gamepad.sThumbLY / 327.67f < -30;
			}

			return;
		}

		if (axis == Xbox::Axis::RightJoystick_Left || axis == Xbox::Axis::RightJoystick_Right) {

			if (axis == Xbox::Axis::RightJoystick_Left) {
				a = (float)Gamepads[pad].previous.Gamepad.sThumbRX / 327.67f < -30;
				b = (float)Gamepads[pad].actual.Gamepad.sThumbRX / 327.67f < -30;
			}
			else {
				a = (float)Gamepads[pad].previous.Gamepad.sThumbRX / 327.67f > 30;
				b = (float)Gamepads[pad].actual.Gamepad.sThumbRX / 327.67f > 30;
			}

			return;
		}

		if (axis == Xbox::Axis::RightJoystick_Up || axis == Xbox::Axis::RightJoystick_Down) {

			if (axis == Xbox::Axis::RightJoystick_Up) {
				a = (float)Gamepads[pad].previous.Gamepad.sThumbRY / 327.67f > 30;
				b = (float)Gamepads[pad].actual.Gamepad.sThumbRY / 327.67f > 30;
			}
			else {
				a = (float)Gamepads[pad].previous.Gamepad.sThumbRY / 327.67f < -30;
				b = (float)Gamepads[pad].actual.Gamepad.sThumbRY / 327.67f < -30;
			}

			return;
		}
	}

	bool checkPad(unsigned short pad) {
		if (pad < 4) {
			return true;
		}

		Warning("Gamepad checked is out of range (" + std::to_string(pad) + "). Default value returned");
		return false;
	}

public:
	Xbox_one() {
		if (CoInitializeEx(NULL, NULL) == S_FALSE) {
			Error("CoInitializeEx Failed");
		}

		this->GamePadUpdate();
	}

	~Xbox_one() = default;

	void GamePadUpdate() {
		float elapsed = std::chrono::duration<float>(std::chrono::steady_clock::now() - start).count();
		start = std::chrono::steady_clock::now();

		for (int i = 0; i < 4; i++) {
			Gamepads[i].previous = Gamepads[i].actual;
			SecureZeroMemory(&Gamepads[i].actual, sizeof(XINPUT_STATE));
			if (XInputGetState(i, &Gamepads[i].actual) == ERROR_SUCCESS) {
				Gamepads[i].connected = true;
			}
			else {
				Gamepads[i].connected = false;
			}

			// vibrations
			if (Gamepads[i].vibration_time > 0) {
				Gamepads[i].vibration_time -= elapsed;

				if (Gamepads[i].vibration_time <= 0) {
					Gamepads[i].vibration->wLeftMotorSpeed = 0;
					Gamepads[i].vibration->wRightMotorSpeed = 0;
					XInputSetState(i, Gamepads[i].vibration);
				}
			}
		}
	}

	bool isConnected(unsigned short pad) {
		if (!checkPad(pad)) {
			return false;
		}

		return Gamepads[pad].connected;
	}

	unsigned short BatteryLevel(unsigned short pad) {
		if (!checkPad(pad)) {
			return BATTERY_LEVEL_EMPTY;
		}

#if INTPTR_MAX == INT32_MAX 

		XINPUT_BATTERY_INFORMATION battery;
		SecureZeroMemory(&battery, sizeof(XINPUT_BATTERY_INFORMATION));
		XInputGetBatteryInformation(pad, BATTERY_DEVTYPE_GAMEPAD, &battery);

		return battery.BatteryLevel;

#elif INTPTR_MAX == INT64_MAX 
		DebugWarning("GamePad Battery level don't work on x64.");
		return BATTERY_LEVEL_FULL;
#endif
	}

	void vibration(unsigned short pad, unsigned short power, float time) {
		if (!checkPad(pad)) {
			return;
		}

		if (Gamepads[pad].vibration == nullptr) {
			XINPUT_VIBRATION vibration;
			SecureZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
			Gamepads[pad].vibration = &vibration;
		}

		power = std::clamp<unsigned>(power, 0, 100);

		Gamepads[pad].vibration->wLeftMotorSpeed = (unsigned short)(power * 655.35f);
		Gamepads[pad].vibration->wRightMotorSpeed = (unsigned short)(power * 655.35f);

		XInputSetState(pad, Gamepads[pad].vibration);

		Gamepads[pad].vibration_time = time;
	}

	void vibration(unsigned short pad, bool on, unsigned short power = 50) {
		if (!checkPad(pad)) {
			return;
		}

		if (Gamepads[pad].vibration == nullptr) {
			XINPUT_VIBRATION vibration;
			SecureZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
			Gamepads[pad].vibration = &vibration;
		}

		power = std::clamp<unsigned>(power, 0, 100);

		if (!on) {
			power = 0;
		}

		Gamepads[pad].vibration->wLeftMotorSpeed = (unsigned short)(power * 655.35f);
		Gamepads[pad].vibration->wRightMotorSpeed = (unsigned short)(power * 655.35f);

		XInputSetState(pad, Gamepads[pad].vibration);
	}

	float TriggerPression(unsigned short pad, Xbox::Trigger trigger) {
		if (!checkPad(pad)) {
			return 0.f;
		}

		if (trigger == Xbox::Trigger::LT) {
			return Gamepads[pad].actual.Gamepad.bLeftTrigger / 2.55f;
		}

		if (trigger == Xbox::Trigger::RT) {
			return Gamepads[pad].actual.Gamepad.bRightTrigger / 2.55f;
		}

		return 0.f;
	}

	float AxisPression(unsigned short pad, Xbox::Axis axis) {
		if (!checkPad(pad)) {
			return 0.f;
		}

		if (axis == Xbox::Axis::LeftJoystick_Left || axis == Xbox::Axis::LeftJoystick_Right) {
			return Gamepads[pad].actual.Gamepad.sThumbLX / 327.67f;
		}

		if (axis == Xbox::Axis::LeftJoystick_Up || axis == Xbox::Axis::LeftJoystick_Down) {
			return Gamepads[pad].actual.Gamepad.sThumbLY / 327.67f;
		}

		if (axis == Xbox::Axis::RightJoystick_Left || axis == Xbox::Axis::RightJoystick_Right) {
			return Gamepads[pad].actual.Gamepad.sThumbRX / 327.67f;
		}

		if (axis == Xbox::Axis::RightJoystick_Up || axis == Xbox::Axis::RightJoystick_Down) {
			return Gamepads[pad].actual.Gamepad.sThumbRY / 327.67f;
		}

		return 0.f;
	}

	bool isPressed(unsigned short pad, unsigned short button) {
		if (!checkPad(pad)) {
			return false;
		}

		return Gamepads[pad].actual.Gamepad.wButtons & button;
	}

	bool isPressed(unsigned short pad, Xbox::Button	button) {
		if (!checkPad(pad)) {
			return false;
		}

		return Gamepads[pad].actual.Gamepad.wButtons & button;
	}

	bool isPressed(unsigned short pad, Xbox::Trigger trigger) {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = false, b = false;
		_Trigger(pad, trigger, a, b);
		return b;
	}

	bool isPressed(unsigned short pad, Xbox::Axis axis) {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = false, b = false;
		_Axis(pad, axis, a, b);
		return b;
	}

	bool onPressed(unsigned short pad, unsigned short button) {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = Gamepads[pad].previous.Gamepad.wButtons & button;
		bool b = Gamepads[pad].actual.Gamepad.wButtons & button;
		return !a && b;
	}

	bool onPressed(unsigned short pad, Xbox::Button	button) {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = Gamepads[pad].previous.Gamepad.wButtons & button;
		bool b = Gamepads[pad].actual.Gamepad.wButtons & button;
		return !a && b;
	}

	bool onPressed(unsigned short pad, Xbox::Trigger trigger) {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = false, b = false;
		_Trigger(pad, trigger, a, b);
		return !a && b;
	}

	bool onPressed(unsigned short pad, Xbox::Axis axis) {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = false, b = false;
		_Axis(pad, axis, a, b);
		return !a && b;
	}

	bool OnRelease(unsigned short pad, unsigned short button) {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = Gamepads[pad].previous.Gamepad.wButtons & button;
		bool b = Gamepads[pad].actual.Gamepad.wButtons & button;
		return a && !b;
	}

	bool OnRelease(unsigned short pad, Xbox::Button	button) {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = Gamepads[pad].previous.Gamepad.wButtons & (int)button;
		bool b = Gamepads[pad].actual.Gamepad.wButtons & (int)button;
		return a && !b;
	}

	bool OnRelease(unsigned short pad, Xbox::Trigger trigger) {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = false, b = false;
		_Trigger(pad, trigger, a, b);
		return a && !b;
	}

	bool OnRelease(unsigned short pad, Xbox::Axis axis) {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = false, b = false;
		_Axis(pad, axis, a, b);
		return a && !b;
	}
};

template <typename T>
std::pair<int, T> Pad(int pad, T action) {
	if (pad >= -1 && pad < 4) {
		return std::make_pair(pad, action);
	}

	Warning("Gamepad chosen is out of range (" + std::to_string(pad) + "). chosen pad by default : 0");
	return std::make_pair(0, action);
}

#pragma warning( pop )
#endif // !GAMEPAD_H