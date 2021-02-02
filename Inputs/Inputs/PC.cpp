#include "PC.h"

#pragma warning(disable : 26812) // disable warning of using enum

// 0x8000 is pressed
// 0x0001 on pressed

void PC::Computer::Update()
{
	for (int i = 0; i < this->keyCount; i++)
	{
		this->previous[i] = this->current[i];
		this->current[i] = GetAsyncKeyState(i);
	}
}

bool PC::Computer::isPressed(PC::KeyBoard k)
{
	return this->current[k] & 0x8000;
}

bool PC::Computer::isPressed(PC::Mouse m)
{
	return this->current[m] & 0x8000;
}

bool PC::Computer::textPressed(PC::KeyBoard k)
{
	return this->current[k] & 0x0001;
}

bool PC::Computer::onPressed(PC::KeyBoard k)
{
	return !(this->previous[k] & 0x8000) && this->current[k] & 0x8000;
}

bool PC::Computer::onPressed(PC::Mouse m)
{
	return !(this->previous[m] & 0x8000) && this->current[m] & 0x8000;
}

bool PC::Computer::onRelease(PC::KeyBoard k)
{
	return this->previous[k] & 0x8000 && !(this->current[k] & 0x8000);
}

bool PC::Computer::onRelease(PC::Mouse m)
{
	return this->previous[m] & 0x8000 && !(this->current[m] & 0x8000);
}

POINT PC::Computer::getMousePos()
{
	GetCursorPos(&this->p);
	return this->p;
}
