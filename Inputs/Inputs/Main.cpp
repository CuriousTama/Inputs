#include "GamePad.h"
#include "PC.h"
#include <chrono>
#include <iostream>
#include "InputManager.h"

void foo(int a)
{
	std::cout << "function : " << a << std::endl;
}

struct foo2
{
	void operator() () { std::cout << "foo2 " << std::endl; }
};


int main(int argc, char** argv)
{
	//Xbox_one m;
	//PC::Computer c;

	InputManager m;

	m.create("click", Action::onPress,
		[&m] { m.x.vibration(0, 50, 0.33f); },
		PC::KeyBoard::A, PC::Mouse::MIDDLE_BUTTON, Xbox_one_::A, Xbox_one_::Trigger::LT, Xbox_one_::Axis::LeftJoystick_Up);

	m.create("click2", Action::onPress,
		std::bind(&foo, 5),
		PC::KeyBoard::G);

	m.create("click", Action::onPress,
		foo2(),
		PC::KeyBoard::F);
	
	m.x.BatteryLevel(0);

	m.bind("a");
	m.unbind("a");
	m.remove("a");
	m.addkey("a", PC::KeyBoard::PAD0);
	m.addkey("click2", PC::KeyBoard::PAD0, PC::PAD1);

	while (true) // game loop
	{		
		m.update();
	}

	return 0;
}

/*
///////////// ideas
create("name", function binded, keys... variadic); // create the input
bind("name");						// can update
unbind("name");						// don't update
update();							// check for all input and do function
remove("name");						// remove an input
addkey("name", new key);			// add a key to the input
isActive("name");					// return if an input is pressed


changekeys("name", new keys...);	// change all keys from the input
removekey("name", keys);			// remove a key from the input
specifier game pad function
*/