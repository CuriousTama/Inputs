#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <Windows.h>
#include <Xinput.h>
#include <chrono>
#include <algorithm>

#include "Errors.h"

#pragma comment(lib, "Xinput.lib")		// XInput
#pragma comment(lib, "ole32.lib")		// CoInitializeEx function

#pragma warning( push )
#pragma warning(disable : 26812) // disable warning of using enum

namespace Xbox {
	enum Button {
		Cross_Up = 0x0001,
		Cross_Down = 0x0002,
		Cross_Left = 0x0004,
		Cross_Right = 0x0008,

		Start = 0x0010,
		Select = 0x0020,
		LeftStickPress = 0x0040,
		RightStickPress = 0x0080,

		LB = 0x0100,
		RB = 0x0200,

		A = 0x1000,
		B = 0x2000,
		X = 0x4000,
		Y = 0x8000
	};

	enum Trigger {
		LT = 0x0400,
		RT = 0x0800
	};

	enum Axis {
		LeftJoystick_Up = 0x0041,
		LeftJoystick_Down = 0x0042,
		LeftJoystick_Left = 0x0044,
		LeftJoystick_Right = 0x0048,

		RightJoystick_Up = 0x0081,
		RightJoystick_Down = 0x0082,
		RightJoystick_Left = 0x0084,
		RightJoystick_Right = 0x0088
	};
}

namespace PlayStation {
	enum Button {
		Cross_Up = 0x0001,
		Cross_Down = 0x0002,
		Cross_Left = 0x0004,
		Cross_Right = 0x0008,

		Start = 0x0010,
		Select = 0x0020,
		LeftStickPress = 0x0040,
		RightStickPress = 0x0080,

		LB = 0x0100,
		RB = 0x0200,

		Croix = 0x1000,
		Rond = 0x2000,
		Carre = 0x4000,
		Triangle = 0x8000
	};

	enum Trigger {
		LT = 0x0400,
		RT = 0x0800
	};

	enum Axis {
		LeftJoystick_Up = 0x0041,
		LeftJoystick_Down = 0x0042,
		LeftJoystick_Left = 0x0044,
		LeftJoystick_Right = 0x0048,

		RightJoystick_Up = 0x0081,
		RightJoystick_Down = 0x0082,
		RightJoystick_Left = 0x0084,
		RightJoystick_Right = 0x0088
	};
}

constexpr bool is_Button(unsigned short i) {
	if (i == Xbox::Cross_Up || i == Xbox::Cross_Down || i == Xbox::Cross_Left || i == Xbox::Cross_Right ||
		i == Xbox::Start || i == Xbox::Select || i == Xbox::LeftStickPress || i == Xbox::RightStickPress ||
		i == Xbox::LB || i == Xbox::RB || i == Xbox::A || i == Xbox::B || i == Xbox::X || i == Xbox::Y) {
		return true;
	}

	return false;
}

constexpr bool is_Trigger(unsigned short i) {
	if (i == Xbox::LT || i == Xbox::RT) {
		return true;
	}

	return false;
}

constexpr bool is_Axis(unsigned short i) {
	if (i == Xbox::LeftJoystick_Up || i == Xbox::LeftJoystick_Down || i == Xbox::LeftJoystick_Left || i == Xbox::LeftJoystick_Right ||
		i == Xbox::RightJoystick_Up || i == Xbox::RightJoystick_Down || i == Xbox::RightJoystick_Left || i == Xbox::RightJoystick_Right) {
		return true;
	}

	return false;
}

class Gamepads {

	struct gamepad {
		std::unique_ptr<XINPUT_VIBRATION> vibration{ std::make_unique<XINPUT_VIBRATION>() };
		float vibration_time{ 0.f };

		XINPUT_STATE previous{ 0 };
		XINPUT_STATE actual{ 0 };
		bool connected{ false };
	};

	inline static std::array<gamepad, 4> m_gamepad;
	inline static bool m_init{ false };
	inline static std::chrono::steady_clock::time_point m_clock{ std::chrono::steady_clock::now() };

	constexpr void _Trigger(unsigned short pad, Xbox::Trigger trigger, bool& a, bool& b) const {
		if (!checkPad(pad)) {
			return;
		}

		if (trigger == Xbox::Trigger::LT) {
			a = m_gamepad.at(pad).previous.Gamepad.bLeftTrigger > 30;
			b = m_gamepad.at(pad).actual.Gamepad.bLeftTrigger > 30;
		}
		else {
			a = m_gamepad.at(pad).previous.Gamepad.bRightTrigger > 30;
			b = m_gamepad.at(pad).actual.Gamepad.bRightTrigger > 30;
		}
	}

	constexpr void _Axis(unsigned short pad, Xbox::Axis axis, bool& a, bool& b) const {
		if (!checkPad(pad)) {
			return;
		}

		if (axis == Xbox::Axis::LeftJoystick_Left || axis == Xbox::Axis::LeftJoystick_Right) {

			if (axis == Xbox::Axis::LeftJoystick_Left) {
				a = static_cast<float>(m_gamepad.at(pad).previous.Gamepad.sThumbLX) / 327.67f < -30;
				b = static_cast<float>(m_gamepad.at(pad).actual.Gamepad.sThumbLX) / 327.67f < -30;
			}
			else {
				a = static_cast<float>(m_gamepad.at(pad).previous.Gamepad.sThumbLX) / 327.67f > 30;
				b = static_cast<float>(m_gamepad.at(pad).actual.Gamepad.sThumbLX) / 327.67f > 30;
			}

			return;
		}

		if (axis == Xbox::Axis::LeftJoystick_Up || axis == Xbox::Axis::LeftJoystick_Down) {

			if (axis == Xbox::Axis::LeftJoystick_Up) {
				a = static_cast<float>(m_gamepad.at(pad).previous.Gamepad.sThumbLY) / 327.67f > 30;
				b = static_cast<float>(m_gamepad.at(pad).actual.Gamepad.sThumbLY) / 327.67f > 30;
			}
			else {
				a = static_cast<float>(m_gamepad.at(pad).previous.Gamepad.sThumbLY) / 327.67f < -30;
				b = static_cast<float>(m_gamepad.at(pad).actual.Gamepad.sThumbLY) / 327.67f < -30;
			}

			return;
		}

		if (axis == Xbox::Axis::RightJoystick_Left || axis == Xbox::Axis::RightJoystick_Right) {

			if (axis == Xbox::Axis::RightJoystick_Left) {
				a = static_cast<float>(m_gamepad.at(pad).previous.Gamepad.sThumbRX) / 327.67f < -30;
				b = static_cast<float>(m_gamepad.at(pad).actual.Gamepad.sThumbRX) / 327.67f < -30;
			}
			else {
				a = static_cast<float>(m_gamepad.at(pad).previous.Gamepad.sThumbRX) / 327.67f > 30;
				b = static_cast<float>(m_gamepad.at(pad).actual.Gamepad.sThumbRX) / 327.67f > 30;
			}

			return;
		}

		if (axis == Xbox::Axis::RightJoystick_Up || axis == Xbox::Axis::RightJoystick_Down) {

			if (axis == Xbox::Axis::RightJoystick_Up) {
				a = static_cast<float>(m_gamepad.at(pad).previous.Gamepad.sThumbRY) / 327.67f > 30;
				b = static_cast<float>(m_gamepad.at(pad).actual.Gamepad.sThumbRY) / 327.67f > 30;
			}
			else {
				a = static_cast<float>(m_gamepad.at(pad).previous.Gamepad.sThumbRY) / 327.67f < -30;
				b = static_cast<float>(m_gamepad.at(pad).actual.Gamepad.sThumbRY) / 327.67f < -30;
			}

			return;
		}
	}

	constexpr bool checkPad(unsigned short pad) const {
		if (pad < 4) {
			return true;
		}

		Warning("Gamepad checked is out of range (" + std::to_string(pad) + "). Default value returned");
		return false;
	}
public:
	enum Battery { EMPTY_BATTERY, LOW_BATTERY, AVERAGE_BATTERY, FULL_BATTERY };

	Gamepads() {
		if (!m_init) {
			if (CoInitializeEx(NULL, NULL) == S_FALSE) {
				Error("CoInitializeEx Failed");
			}

			this->update();
			m_init = true;
		}
	}

	~Gamepads() = default;

	void update() {
		float elapsed = std::chrono::duration<float>(std::chrono::steady_clock::now() - m_clock).count();
		m_clock = std::chrono::steady_clock::now();

		for (int i = 0; i < 4; i++) {
			m_gamepad.at(i).previous = m_gamepad.at(i).actual;
			if (XInputGetState(i, &m_gamepad.at(i).actual) == ERROR_SUCCESS) {
				m_gamepad.at(i).connected = true;
			}
			else {
				m_gamepad.at(i).connected = false;
			}

			// vibrations
			if (m_gamepad.at(i).vibration_time > 0.f) {
				m_gamepad.at(i).vibration_time -= elapsed;

				if (m_gamepad.at(i).vibration_time <= 0.f) {
					m_gamepad.at(i).vibration_time = 0.f;
					m_gamepad.at(i).vibration->wLeftMotorSpeed = 0;
					m_gamepad.at(i).vibration->wRightMotorSpeed = 0;
					XInputSetState(i, m_gamepad.at(i).vibration.get());
				}
			}
		}
	}

	constexpr bool is_connected(unsigned short pad) const {
		if (!checkPad(pad)) {
			return false;
		}

		return m_gamepad.at(pad).connected;
	}

	constexpr Battery battery_level(unsigned short pad) const {
		if (!checkPad(pad)) {
			return static_cast<Battery>(BATTERY_LEVEL_EMPTY);
		}

		XINPUT_BATTERY_INFORMATION battery{};
		SecureZeroMemory(&battery, sizeof(XINPUT_BATTERY_INFORMATION));
		XInputGetBatteryInformation(pad, BATTERY_DEVTYPE_GAMEPAD, &battery);

		// Battery level unknown (refreshing isn't instant)
		if (battery.BatteryType == BATTERY_TYPE_DISCONNECTED && this->is_connected(pad)) {
			return static_cast<Battery>(BATTERY_LEVEL_FULL);
		}

		return static_cast<Battery>(battery.BatteryLevel);
	}

	constexpr void vibration(unsigned short pad, float time, unsigned short power_both) {
		if (!checkPad(pad)) {
			return;
		}

		power_both = std::clamp<unsigned>(power_both, 0, 100);

		m_gamepad.at(pad).vibration->wLeftMotorSpeed = (unsigned short)(power_both * 655.35f);
		m_gamepad.at(pad).vibration->wRightMotorSpeed = (unsigned short)(power_both * 655.35f);

		XInputSetState(pad, m_gamepad.at(pad).vibration.get());

		m_gamepad.at(pad).vibration_time = time;
	}

	constexpr void vibration(unsigned short pad, float time, unsigned short power_left, unsigned short power_right) {
		if (!checkPad(pad)) {
			return;
		}

		power_left = std::clamp<unsigned>(power_left, 0, 100);
		power_right = std::clamp<unsigned>(power_right, 0, 100);

		m_gamepad.at(pad).vibration->wLeftMotorSpeed = (unsigned short)(power_left * 655.35f);
		m_gamepad.at(pad).vibration->wRightMotorSpeed = (unsigned short)(power_right * 655.35f);

		XInputSetState(pad, m_gamepad.at(pad).vibration.get());

		m_gamepad.at(pad).vibration_time = time;
	}

	constexpr void vibration(unsigned short pad, bool on, unsigned short power_both) {
		if (!checkPad(pad)) {
			return;
		}

		power_both = std::clamp<unsigned>(power_both, 0, 100);

		if (!on) {
			power_both = 0;
		}

		m_gamepad.at(pad).vibration->wLeftMotorSpeed = (unsigned short)(power_both * 655.35f);
		m_gamepad.at(pad).vibration->wRightMotorSpeed = (unsigned short)(power_both * 655.35f);

		XInputSetState(pad, m_gamepad.at(pad).vibration.get());
	}

	constexpr void vibration(unsigned short pad, bool on, unsigned short power_left, unsigned short power_right) {
		if (!checkPad(pad)) {
			return;
		}

		power_left = std::clamp<unsigned>(power_left, 0, 100);
		power_right = std::clamp<unsigned>(power_right, 0, 100);

		if (!on) {
			power_left = 0;
			power_right = 0;
		}

		m_gamepad.at(pad).vibration->wLeftMotorSpeed = (unsigned short)(power_left * 655.35f);
		m_gamepad.at(pad).vibration->wRightMotorSpeed = (unsigned short)(power_right * 655.35f);

		XInputSetState(pad, m_gamepad.at(pad).vibration.get());
	}

	constexpr float trigger_pression(unsigned short pad, Xbox::Trigger trigger) const {
		if (!checkPad(pad)) {
			return 0.f;
		}

		if (trigger == Xbox::Trigger::LT) {
			return m_gamepad.at(pad).actual.Gamepad.bLeftTrigger / 2.55f;
		}

		if (trigger == Xbox::Trigger::RT) {
			return m_gamepad.at(pad).actual.Gamepad.bRightTrigger / 2.55f;
		}

		return 0.f;
	}

	constexpr float axis_pression(unsigned short pad, Xbox::Axis axis) const {
		if (!checkPad(pad)) {
			return 0.f;
		}

		if (axis == Xbox::Axis::LeftJoystick_Left || axis == Xbox::Axis::LeftJoystick_Right) {
			return m_gamepad.at(pad).actual.Gamepad.sThumbLX / 327.67f;
		}

		if (axis == Xbox::Axis::LeftJoystick_Up || axis == Xbox::Axis::LeftJoystick_Down) {
			return m_gamepad.at(pad).actual.Gamepad.sThumbLY / 327.67f;
		}

		if (axis == Xbox::Axis::RightJoystick_Left || axis == Xbox::Axis::RightJoystick_Right) {
			return m_gamepad.at(pad).actual.Gamepad.sThumbRX / 327.67f;
		}

		if (axis == Xbox::Axis::RightJoystick_Up || axis == Xbox::Axis::RightJoystick_Down) {
			return m_gamepad.at(pad).actual.Gamepad.sThumbRY / 327.67f;
		}

		return 0.f;
	}

#pragma region is_pressed
	constexpr bool is_pressed(unsigned short pad, unsigned short button) const {
		if (!checkPad(pad)) {
			return false;
		}

		if (is_Button(button)) {
			return is_pressed(pad, static_cast<Xbox::Button>(button));
		}

		else if (is_Trigger(button)) {
			return is_pressed(pad, static_cast<Xbox::Trigger>(button));
		}

		else if (is_Axis(button)) {
			return is_pressed(pad, static_cast<Xbox::Axis>(button));
		}
	}

	constexpr bool is_pressed(unsigned short pad, Xbox::Button button) const {
		if (!checkPad(pad)) {
			return false;
		}

		return m_gamepad.at(pad).actual.Gamepad.wButtons & button;
	}

	constexpr bool is_pressed(unsigned short pad, Xbox::Trigger trigger) const {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = false, b = false;
		_Trigger(pad, trigger, a, b);
		return b;
	}

	constexpr bool is_pressed(unsigned short pad, Xbox::Axis axis) const {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = false, b = false;
		_Axis(pad, axis, a, b);
		return b;
	}
#pragma endregion is_pressed

#pragma region is_released
	constexpr bool is_released(unsigned short pad, unsigned short button) const {
		if (!checkPad(pad)) {
			return false;
		}

		if (is_Button(button)) {
			return is_released(pad, static_cast<Xbox::Button>(button));
		}

		else if (is_Trigger(button)) {
			return is_released(pad, static_cast<Xbox::Trigger>(button));
		}

		else if (is_Axis(button)) {
			return is_released(pad, static_cast<Xbox::Axis>(button));
		}
	}

	constexpr bool is_released(unsigned short pad, Xbox::Button button) const {
		if (!checkPad(pad)) {
			return false;
		}

		return !(m_gamepad.at(pad).actual.Gamepad.wButtons & button);
	}

	constexpr bool is_released(unsigned short pad, Xbox::Trigger trigger) const {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = false, b = false;
		_Trigger(pad, trigger, a, b);
		return !b;
	}

	constexpr bool is_released(unsigned short pad, Xbox::Axis axis) const {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = false, b = false;
		_Axis(pad, axis, a, b);
		return !b;
	}
#pragma endregion is_released

#pragma region on_pressed
	constexpr bool on_pressed(unsigned short pad, unsigned short button) const {
		if (!checkPad(pad)) {
			return false;
		}

		if (is_Button(button)) {
			return on_pressed(pad, static_cast<Xbox::Button>(button));
		}

		else if (is_Trigger(button)) {
			return on_pressed(pad, static_cast<Xbox::Trigger>(button));
		}

		else if (is_Axis(button)) {
			return on_pressed(pad, static_cast<Xbox::Axis>(button));
		}
	}

	constexpr bool on_pressed(unsigned short pad, Xbox::Button button) const {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = m_gamepad.at(pad).previous.Gamepad.wButtons & button;
		bool b = m_gamepad.at(pad).actual.Gamepad.wButtons & button;
		return !a && b;
	}

	constexpr bool on_pressed(unsigned short pad, Xbox::Trigger trigger) const {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = false, b = false;
		_Trigger(pad, trigger, a, b);
		return !a && b;
	}

	constexpr bool on_pressed(unsigned short pad, Xbox::Axis axis) const {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = false, b = false;
		_Axis(pad, axis, a, b);
		return !a && b;
	}
#pragma endregion on_pressed

#pragma region on_release
	constexpr bool on_release(unsigned short pad, unsigned short button) const {
		if (!checkPad(pad)) {
			return false;
		}

		if (is_Button(button)) {
			return on_release(pad, static_cast<Xbox::Button>(button));
		}

		else if (is_Trigger(button)) {
			return on_release(pad, static_cast<Xbox::Trigger>(button));
		}

		else if (is_Axis(button)) {
			return on_release(pad, static_cast<Xbox::Axis>(button));
		}
	}

	constexpr bool on_release(unsigned short pad, Xbox::Button button) const {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = m_gamepad.at(pad).previous.Gamepad.wButtons & (int)button;
		bool b = m_gamepad.at(pad).actual.Gamepad.wButtons & (int)button;
		return a && !b;
	}

	constexpr bool on_release(unsigned short pad, Xbox::Trigger trigger) const {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = false, b = false;
		_Trigger(pad, trigger, a, b);
		return a && !b;
	}

	constexpr bool on_release(unsigned short pad, Xbox::Axis axis) const {
		if (!checkPad(pad)) {
			return false;
		}

		bool a = false, b = false;
		_Axis(pad, axis, a, b);
		return a && !b;
	}
#pragma endregion on_release
};

template <typename T>
constexpr std::pair<int, T> Pad(int pad, T action) {
	if (pad >= -1 && pad < 4) {
		return std::make_pair(pad, action);
	}

	Warning("Gamepad chosen is out of range (" + std::to_string(pad) + "). chosen pad by default : 0");
	return std::make_pair(0, action);
}

#pragma warning( pop )
#endif // !GAMEPAD_H