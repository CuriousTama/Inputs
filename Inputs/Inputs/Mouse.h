#ifndef MOUSE_H
#define MOUSE_H

#pragma comment(lib, "User32.lib") // windows inputs Function

#pragma warning( push )
#pragma warning(disable : 26812)   // disable warning of using enum
#pragma warning(disable : 6387)   // disable warning of PeekMessageW using nullptr in first arg

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

		SCROLL_UP = 0x078,
		SCROLL_DOWN = -0x078,
	};

private:
	static const int keyCount{ Mouse::Key::BUTTON_2 + 1 };

	inline static unsigned int m_instances{ 0 };
	inline static short previous[keyCount]{ 0 };
	inline static short current[keyCount]{ 0 };
	inline static POINT p;
	inline static short previous_scroll;
	inline static short current_scroll;
	inline static HHOOK mouseHook;

	static LRESULT __stdcall MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
	{
		if (wParam == WM_MOUSEWHEEL) {
			MSLLHOOKSTRUCT* info = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam);
			current_scroll = static_cast<std::make_signed_t<WORD>>(HIWORD(info->mouseData));
		}

		return CallNextHookEx(nullptr, nCode, wParam, lParam);
	}

public:
	Mouse() {
		if (m_instances++ == 0) {
			mouseHook = SetWindowsHookEx(WH_MOUSE_LL, Mouse::MouseHookProc, nullptr, 0);
			this->eventUpdate();
		}
	}

	~Mouse() {
		if (--m_instances == 0) {
			UnhookWindowsHookEx(mouseHook);
		}
	};

	void eventUpdate() {
		GetCursorPos(&this->p);

		previous_scroll = current_scroll;
		current_scroll = 0;

		while (PeekMessage(nullptr, 0, 0, 0, PM_REMOVE)) {
		}

		for (int i = 0; i < this->keyCount; i++) {
			this->previous[i] = this->current[i];
			this->current[i] = GetAsyncKeyState(i);
		}
	}

	const bool is_pressed(Mouse::Key m) const {
		if (m != SCROLL_UP && m != SCROLL_DOWN) {
			return this->current[m] & 0x8000;
		}

		return current_scroll == m;
	}

	const bool on_pressed(Mouse::Key m) const {
		if (m != SCROLL_UP && m != SCROLL_DOWN) {
			return !(this->previous[m] & 0x8000) && this->current[m] & 0x8000;
		}

		return current_scroll == m && previous_scroll != m;
	}

	const bool on_release(Mouse::Key m) const {
		if (m != SCROLL_UP && m != SCROLL_DOWN) {
			return this->previous[m] & 0x8000 && !(this->current[m] & 0x8000);
		}

		return current_scroll != m && previous_scroll == m;
	}

	const bool is_release(Mouse::Key m) const {
		if (m != SCROLL_UP && m != SCROLL_DOWN) {
			return !(this->current[m] & 0x8000);
		}

		return current_scroll != m;
	}

	const POINT getMousePos() const {
		return this->p;
	}

	const unsigned int getScroll() const {
		return this->current_scroll;
	}
};

#pragma warning( pop )
#endif // !MOUSE_H