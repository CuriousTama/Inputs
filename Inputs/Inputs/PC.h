#ifndef PC_H
#define PC_H

#include "Mouse.h"
#include "KeyBoard.h"
#include <Windows.h>

#pragma comment(lib, "User32.lib")

namespace PC
{
	class Computer
	{
		static const int keyCount = RMENU + 1;

		SHORT previous[keyCount] {0};
		SHORT current[keyCount] {0};
		POINT p;

	public:
		Computer() { this->Update(); };
		~Computer() = default;

		void Update();

		bool isPressed(PC::KeyBoard);
		bool isPressed(PC::Mouse);

		bool textPressed(PC::KeyBoard);

		bool onPressed(PC::KeyBoard);
		bool onPressed(PC::Mouse);

		bool onRelease(PC::KeyBoard);
		bool onRelease(PC::Mouse);

		POINT getMousePos();
	};
}

#endif // !PC_H
