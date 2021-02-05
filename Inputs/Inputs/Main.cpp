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
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

int main(int argc, char** argv)
{
	//Xbox_one m;
	//PC::Computer c;
	std::cout << RED << "TEST" << std::endl;
	std::cout << "TEST2" << std::endl;
	std::cout << BOLDBLUE << "TEST3" << std::endl;
	std::cout << RESET << "TEST4" << std::endl;
	InputManager m;

	m.create("click", Action::onPress,
		[&m] { m.x.vibration(0, 50, 0.33f); },
		PC::KeyBoard::A, PC::Mouse::MIDDLE_BUTTON, Xbox_one_::A, Xbox_one_::Trigger::LT, Xbox_one_::Axis::LeftJoystick_Up);

	m.create("click2", Action::onPress,
		std::bind(&foo, 5),
		PC::KeyBoard::G);

	m.create("click3", Action::onPress,
		foo2(),
		PC::KeyBoard::F);
	
	m.x.BatteryLevel(0);
	std::cout << "a" << std::endl;

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
changekeys("name", new keys...);	// change all keys from the input
addkey("name", new key);			// add a key to the input
removekey("name", keys);			// remove a key from the input
ispressed("name");					// return if an input is pressed
specifier game pad function
*/