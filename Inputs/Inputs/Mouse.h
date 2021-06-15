#ifndef MOUSE_H
#define MOUSE_H

#include <thread>
#include <Windows.h>
#include <array>

#pragma comment(lib, "User32.lib")

#pragma warning(push)
#pragma warning(disable : 26812)   // disable warning of using enum
#pragma warning(disable : 6387)    // disable warning of PeekMessageW using nullptr in first arg

constexpr POINT& operator+=(POINT& p1, const POINT& p2) {
	p1.x += p2.x;
	p1.y += p2.y;
	return p1;
}

constexpr POINT operator-(POINT& m_position) {
	return POINT{ -m_position.x, -m_position.y };
}

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
	inline static std::array<std::pair<short, short>, keyCount> m_keys{};	// <previous, current>
	inline static std::pair<short, short> m_scroll{};	// <previous, current>
	inline static POINT m_position{};
	inline static POINT m_moveDelta{};
	inline static std::thread m_th{};

	inline static std::atomic<short> m_th_scroll{ 0 };
	inline static std::atomic<bool> m_end{ false };

	constexpr static LRESULT __stdcall MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
	{
		if (nCode >= 0) {
			if (wParam == WM_MOUSEWHEEL) {
				MSLLHOOKSTRUCT* info = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam);
				m_th_scroll = static_cast<std::make_signed_t<WORD>>(HIWORD(info->mouseData));
			}

			return CallNextHookEx(nullptr, nCode, wParam, lParam);
		}
		else {
			return 0;
		}
	}

public:
	Mouse() {
		if (m_instances++ == 0) {

			m_th = std::thread([] {
				HHOOK mouseHook = SetWindowsHookEx(WH_MOUSE_LL, Mouse::MouseHookProc, GetModuleHandle(0), 0);
				std::chrono::steady_clock::time_point clock;

				while (!m_end) {
					clock = std::chrono::steady_clock::now();

					while (PeekMessage(nullptr, 0, 0, 0, PM_REMOVE)) {
					}

					std::chrono::duration<double> operationTime = clock - std::chrono::steady_clock::now();
					if (operationTime < std::chrono::milliseconds(1)) {
						std::this_thread::sleep_for(std::chrono::milliseconds(1) - operationTime); // 1000 update per second
					}
				}

				UnhookWindowsHookEx(mouseHook);
				});

			this->eventUpdate();
		}
	}

	~Mouse() {
		if (--m_instances == 0) {
			m_end = true;

			if (m_th.joinable()) {
				m_th.join();
			}
		}
	};

	void eventUpdate() {

		m_moveDelta = -m_position;
		GetCursorPos(&this->m_position);
		m_moveDelta += m_position;

		m_scroll.first = m_scroll.second;
		m_scroll.second = m_th_scroll;
		m_th_scroll = 0;

		for (int i = 0; i < this->keyCount; i++) {
			m_keys.at(i).first = m_keys.at(i).second;
			m_keys.at(i).second = GetAsyncKeyState(i);
		}
	}

	const bool is_pressed(Mouse::Key m) const {
		if (m != SCROLL_UP && m != SCROLL_DOWN) {
			return m_keys.at(m).second & 0x8000;
		}

		return m_scroll.second == m;
	}

	const bool on_pressed(Mouse::Key m) const {
		if (m != SCROLL_UP && m != SCROLL_DOWN) {
			return !(m_keys.at(m).first & 0x8000) && m_keys.at(m).second & 0x8000;
		}

		return m_scroll.second == m && m_scroll.first != m;
	}

	const bool on_release(Mouse::Key m) const {
		if (m != SCROLL_UP && m != SCROLL_DOWN) {
			return m_keys.at(m).first & 0x8000 && !(m_keys.at(m).second & 0x8000);
		}

		return m_scroll.second != m && m_scroll.first == m;
	}

	const bool is_release(Mouse::Key m) const {
		if (m != SCROLL_UP && m != SCROLL_DOWN) {
			return !(m_keys.at(m).second & 0x8000);
		}

		return m_scroll.second != m;
	}

	const POINT getMousePos() const {
		return this->m_position;
	}

	const POINT getMouseDelta() const {
		return this->m_moveDelta;
	}

	const unsigned int getScroll() const {
		return this->m_scroll.second;
	}
};

#pragma warning(pop)
#endif // !MOUSE_H