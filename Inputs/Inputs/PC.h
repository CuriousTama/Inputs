#ifndef PC_H
#define PC_H

#include <Windows.h>
#include "Mouse.h"
#include "KeyBoard.h"

#pragma comment(lib, "User32.lib") // GetAsyncKeyState Function

#pragma warning( push )
#pragma warning(disable : 26812)   // disable warning of using enum

namespace PC
{
	class Computer
	{
		// 0x8000 is pressed
		// 0x0001 on pressed

		static const int keyCount = RMENU + 1;

		short previous[keyCount]{ 0 };
		short current[keyCount]{ 0 };
		POINT p;

	public:
		Computer() {
			this->Update();
		};

		~Computer() = default;

		void Update() {
			for (int i = 0; i < this->keyCount; i++) {
				this->previous[i] = this->current[i];
				this->current[i] = GetAsyncKeyState(i);
			}
		}

		bool isPressed(PC::KeyBoard k) {
			return this->current[k] & 0x8000;
		}

		bool isPressed(PC::Mouse m) {
			return this->current[m] & 0x8000;
		}

		bool textPressed(PC::KeyBoard k) {
			return this->current[k] & 0x0001;
		}

		bool onPressed(PC::KeyBoard k) {
			return !(this->previous[k] & 0x8000) && this->current[k] & 0x8000;
		}

		bool onPressed(PC::Mouse m) {
			return !(this->previous[m] & 0x8000) && this->current[m] & 0x8000;
		}

		bool onRelease(PC::KeyBoard k) {
			return this->previous[k] & 0x8000 && !(this->current[k] & 0x8000);
		}

		bool onRelease(PC::Mouse m) {
			return this->previous[m] & 0x8000 && !(this->current[m] & 0x8000);
		}

		POINT getMousePos() {
			GetCursorPos(&this->p);
			return this->p;
		}
	};
}
#pragma warning( pop )
#endif // !PC_H
