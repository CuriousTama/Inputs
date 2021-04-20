#include "Inputs.h"

void foo(int a) {
	std::cout << "function : " << a << std::endl;
}
//
//void foo() {
//	std::cout << "function : c" << std::endl;
//}

struct foo2 {
	void operator() () { std::cout << "foo2 " << std::endl; }
};

int main(int argc, char** argv) {
	Inputs m;

	m.create("click", Action::on_pressed,
		[&m] {
			m.Gamepads().vibration(0, 0.33f, 50);
		},
		Keyboard::Key::A, Mouse::Key::MIDDLE_BUTTON,
			Pad(0, Xbox::A), Pad(-1, Xbox::B), Pad(0, Xbox::Trigger::LT), Pad(0, Xbox::Axis::LeftJoystick_Up));

	m.remove_key("click", Pad(-1, Xbox::A));
	m.remove_key("click", Keyboard::Key::A);
	//m.change_keys("click", Pad(0, Xbox::B), Pad(0, Xbox::Trigger::RT));

	m.create("click2", Action::on_pressed,
		std::bind(&foo, 5),
		Keyboard::Key::G, Mouse::SCROLL_UP);

	m.create("click", Action::on_pressed,
		foo2(),
		Keyboard::Key::F);

	std::cout << m.Gamepads().is_connected(0) << std::endl;
	std::cout << m.Gamepads().battery_level(0) << std::endl;

	m.add_key("click", Pad(-1, Xbox::Axis::LeftJoystick_Down));

	m.bind("a");
	m.unbind("a");
	m.remove("a");
	m.add_key("a", Keyboard::Key::PAD0);
	m.add_key("click2", Keyboard::Key::PAD0, Keyboard::PAD1);

	m.Gamepads().is_connected(0);
	m.Gamepads().is_connected(1);
	m.Gamepads().is_connected(2);
	m.Gamepads().is_connected(3);

	m.redefine_function("click", [&m] {
		std::cout << "brrrr" << std::endl;
		m.Gamepads().vibration(0, 1.f, 50);
		m.redefine_action("click", Action::on_pressed);
		});

	Gamepads g;
	Mouse mouse;
	Keyboard k;


	while (true) { // game loop
		m.update();

		if (m.Gamepads().battery_level(0) <= Gamepads::LOW_BATTERY)
		{
			std::cout << "Low Battery" << std::endl;
		}

		//std::cout << mouse.getMouseDelta().x << " : " << mouse.getMouseDelta().y << std::endl;

		if (mouse.getScroll() == Mouse::SCROLL_UP)
		{
			std::cout << "^^ m" << std::endl;
		}
		if (mouse.getScroll() == Mouse::SCROLL_DOWN)
		{
			std::cout << "^^ m2" << std::endl;
		}

		//if (m("click2")) {
		//	std::cout << "clicked" << std::endl;
		//}
		std::cout << "LStick pression : " << g.axis_pression(0, Xbox::LeftJoystick_Right) << std::endl;
		std::cout << "RT pression : " << g.trigger_pression(0, Xbox::RT) << std::endl;

		if (m.Gamepads().on_pressed(0, Xbox::X))
		{
			std::cout << "'A' boutton pressed." << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 20));
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
rename some functions, class
rework acces to gamepads & pc::computer

todo :
exist("name")
*/