#include "InputManager.h"

void foo(int a) {
	std::cout << "function : " << a << std::endl;
}

struct foo2 {
	void operator() () { std::cout << "foo2 " << std::endl; }
};


int main(int argc, char** argv) {
	InputManager m;
	
	m.create("click", Action::onPress,
		[&m] {
			m.x.vibration(0, 50, 0.33f);
		},
		PC::KeyBoard::A, PC::Mouse::MIDDLE_BUTTON,
			Pad(0, Xbox::A), Pad(-1, Xbox::B), Pad(0, Xbox::Trigger::LT), Pad(0, Xbox::Axis::LeftJoystick_Up));

	m.removekey("click", Pad(-1, Xbox::A));
	m.removekey("click", PC::KeyBoard::A);
	//m.Changekeys("click", Pad(0, Xbox::B), Pad(0, Xbox::Trigger::RT));

	m.create("click2", Action::onPress,
		std::bind(&foo, 5),
		PC::KeyBoard::G);

	m.create("click", Action::onPress,
		foo2(),
		PC::KeyBoard::F);
	
	m.x.BatteryLevel(0);

	m.addkey("click", Pad(-1, Xbox::Axis::LeftJoystick_Down));

	m.bind("a");
	m.unbind("a");
	m.remove("a");
	m.addkey("a", PC::KeyBoard::PAD0);
	m.addkey("click2", PC::KeyBoard::PAD0, PC::PAD1);

	m.x.isConnected(0);
	m.x.isConnected(1);
	m.x.isConnected(2);
	m.x.isConnected(3);
	m.x.isConnected(4);

	m.redefineAction("click", [&m] {
		std::cout << "brrrr" << std::endl;
		m.x.vibration(0, 50, 0.33f);
		});



	//std::shared_ptr<int> a;

	//if (!a)
	//{
	//	a = std::make_shared<decltype(std::remove_reference<decltype(*a)>::type(*a))>(10);
	//	std::cout << *a << std::endl;
	//}
	//else
	//	std::cout << *a << std::endl;

	std::cout << m.isBind("click") << std::endl;
	m.unbind("click");
	std::cout << m.isBind("click") << std::endl;
	m.bind("click");
	std::cout << m.isBind("click") << std::endl;

	while (true) { // game loop
		m.update();
	}

	return 0;
}

/*
done : 
create("name", function binded, keys... variadic); // create the input
bind("name");						// can update
unbind("name");						// don't update
update();							// check for all input and do function
remove("name");						// remove an input
addkey("name", new key);			// add a key to the input
isActive("name");					// return if an input is pressed
isBind("name");						// return if an input is binded
removekey("name", keys);			// remove a key from the input
specifier game pad function
changekeys("name", new keys...);	// change all keys from the input
specifier -1 for selecting all GamePad
redefine action

todo : 
rename some functions, class
rework acces to gamepads & pc::computer

*/