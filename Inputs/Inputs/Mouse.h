#ifndef MOUSE_H
#define MOUSE_H

#pragma comment(lib, "User32.lib") // GetAsyncKeyState Function

#pragma warning( push )
#pragma warning(disable : 26812)   // disable warning of using enum

class Mouse
{
public:
	enum Key
	{
		LEFT_BUTTON = 0x01,
		RIGHT_BUTTON = 0x02,
		MIDDLE_BUTTON = 0x04,
		BUTTON_1 = 0x05,
		BUTTON_2 = 0x06,
	};

private:
	static const int keyCount{ Mouse::Key::BUTTON_2 + 1 };

	inline static short previous[keyCount]{ 0 };
	inline static short current[keyCount]{ 0 };
	inline static POINT p;

	inline static bool m_init{ false };
public:
	Mouse() {
		if (!m_init) {
			this->eventUpdate();
			m_init = true;
		}
	}

	~Mouse() = default;

	void eventUpdate() {
		GetCursorPos(&this->p);

		for (int i = 0; i < this->keyCount; i++) {
			this->previous[i] = this->current[i];
			this->current[i] = GetAsyncKeyState(i);
		}
	}

	const bool is_pressed(Mouse::Key m) const {
		return this->current[m] & 0x8000;
	}

	const bool on_pressed(Mouse::Key m) const {
		return !(this->previous[m] & 0x8000) && this->current[m] & 0x8000;
	}

	const bool on_release(Mouse::Key m) const {
		return this->previous[m] & 0x8000 && !(this->current[m] & 0x8000);
	}

	const POINT getMousePos() const {
		return this->p;
	}
};

#pragma warning( pop )
#endif // !MOUSE_H