#include "GamePad.h"
#include "PC.h"
#include <chrono>
#include <iostream>
#include "InputManager.h"

void foo(int a)
{
	std::cout << "function : " << a << std::endl;
}

int main(int argc, char** argv)
{
	//Xbox_one m;
	//PC::Computer c;

	//std::cout << (int)m.BatteryLevel(0) << std::endl;
	//std::cout << m.isConnected(0) << std::endl;

	auto start = std::chrono::steady_clock::now();
	std::chrono::duration<float> tmp;

	InputManager m;

	m.create("click", Action::KeyPressed, 
		[&m] { m.x.vibration(0, 15, 0.5f); }, 
		PC::KeyBoard::A, PC::Mouse::LEFT_BUTTON, Xbox_one_::A, Xbox_one_::Trigger::LT, Xbox_one_::Axis::LeftJoystick_Up);

	m.create("click", Action::onPress,
		std::bind(&foo, 5),
		PC::KeyBoard::G);



	//m.create("move", Action::KeyPressed, [] {std::cout << "move "; }, PC::KeyBoard::Z, PC::Mouse::LEFT_BUTTON, Xbox_one_::A);

	//m.create("change", Action::onRelease, [&m] { m.unbind("move"); }, sf::Keyboard::Escape);
	//m.create("change2", Action::onRelease, [&m] { m.bind("move"); }, sf::Keyboard::Enter);

	//m.create("test1", Action::onPress, [] { std::cout << "test 1" << std::endl; }, m.Axis::LeftJoystick_Left);
	//m.create("test2", Action::onPress, [] { std::cout << "test 2" << std::endl; }, m.Axis::LeftJoystick_Right);
	//m.create("test3", Action::onPress, [] { std::cout << "test 3" << std::endl; }, m.Axis::LeftJoystick_Up);
	//m.create("test4", Action::onPress, [] { std::cout << "test 4" << std::endl; }, m.Axis::LeftJoystick_Down);

	//m.create("test5", Action::onPress, [] { std::cout << "test 5" << std::endl; }, m.Axis::RightJoystick_Left);
	//m.create("test6", Action::onPress, [] { std::cout << "test 6" << std::endl; }, m.Axis::RightJoystick_Right);
	//m.create("test7", Action::onPress, [] { std::cout << "test 7" << std::endl; }, m.Axis::RightJoystick_Up);
	//m.create("test8", Action::onPress, [] { std::cout << "test 8" << std::endl; }, m.Axis::RightJoystick_Down);

	//m.create("test9", Action::onPress, [] { std::cout << "test 9" << std::endl; }, m.Axis::LT);
	//m.create("test10", Action::onPress, [] { std::cout << "test 10" << std::endl; }, m.Axis::RT);

	//m.create("test11", Action::onPress, [] { std::cout << "test 11" << std::endl; }, m.Axis::Cross_Left);
	//m.create("test12", Action::onPress, [] { std::cout << "test 12" << std::endl; }, m.Axis::Cross_Right);
	//m.create("test13", Action::onPress, [] { std::cout << "test 13" << std::endl; }, m.Axis::Cross_Up);
	//m.create("test14", Action::onPress, [] { std::cout << "test 14" << std::endl; }, m.Axis::Cross_Down);



	while (true)
	{

		tmp = std::chrono::steady_clock::now() - start;
		start = std::chrono::steady_clock::now();

		m.update(tmp.count());

		//m.GamePadUpdate(tmp.count());
		//c.Update();

		//if (c.isPressed(PC::KeyBoard::A))		
		//	std::cout << "is pressed : " << std::endl;
		//
		//if (c.isPressed(PC::Mouse::MIDDLE_BUTTON))		
		//	std::cout << "is pressed : " << std::endl;		

		//if (c.onPressed(PC::KeyBoard::P))		
		//	std::cout << "pressed : " << std::endl;
		//
		//if (c.onPressed(PC::Mouse::RIGHT_BUTTON))		
		//	std::cout << "pressed : " << std::endl;		
		//
		//if (c.onRelease(PC::KeyBoard::T))		
		//	std::cout << "released : " << std::endl;
		//
		//if (c.onRelease(PC::Mouse::LEFT_BUTTON))		
		//	std::cout << "released : " << std::endl;		

		//if (c.textPressed(PC::KeyBoard::M))
		//	std::cout << "text pressed : " << std::endl;

		//std::cout << c.getMousePos().x << " : " << c.getMousePos().y << std::endl;

		//if (m.isPressed(0, Xbox_one_::A))
		//	m.vibration(0, 15, 1.f);
		//if (m.isButtonPressed(0, Xbox_one_::B))
		//	std::cout << "b\n";
		//if (m.isButtonPressed(0, Xbox_one_::LT))
		//	std::cout << "lt\n";
		//if (m.isButtonPressed(0, Xbox_one_::Axis::LeftJoystick_Down))
		//	std::cout << "ldown\n";
		//if (m.isButtonPressed(0, Xbox_one_::Axis::LeftJoystick_Up))
		//	std::cout << "lup\n";
		//if (m.isButtonPressed(0, Xbox_one_::Axis::LeftJoystick_Left))
		//	std::cout << "lleft\n";
		//if (m.isButtonPressed(0, Xbox_one_::Axis::LeftJoystick_Right))
		//	std::cout << "lRight\n";

		//if (m.isButtonPressed(0, Xbox_one_::Axis::RightJoystick_Down))
		//	std::cout << "rdown\n";
		//if (m.isButtonPressed(0, Xbox_one_::Axis::RightJoystick_Up))
		//	std::cout << "rup\n";
		//if (m.isButtonPressed(0, Xbox_one_::Axis::RightJoystick_Left))
		//	std::cout << "rleft\n";
		//if (m.isButtonPressed(0, Xbox_one_::Axis::RightJoystick_Right))
		//	std::cout << "rRight\n";
		//if (m.isButtonPressed(0, XINPUT_GAMEPAD_A))
		//	m.vibration(0, 15, 1.f);
		//if (m.isButtonPressed(0, XINPUT_GAMEPAD_A))
		//	std::cout << "a\n";
		//if (m.isButtonPressed(0, XINPUT_GAMEPAD_B))
		//	std::cout << "b\n";
		//if (m.isButtonPressed(0, XINPUT_GAMEPAD_X))
		//	std::cout << "x\n";
		//if (m.isButtonPressed(0, XINPUT_GAMEPAD_Y))
		//	std::cout << "y\n";

		//if (m.isButtonPressed(0, XINPUT_GAMEPAD_DPAD_DOWN))
		//	std::cout << "down\n";
		//if (m.isButtonPressed(0, XINPUT_GAMEPAD_DPAD_UP))
		//	std::cout << "up\n";
		//if (m.isButtonPressed(0, XINPUT_GAMEPAD_DPAD_RIGHT))
		//	std::cout << "right\n";
		//if (m.isButtonPressed(0, XINPUT_GAMEPAD_DPAD_LEFT))
		//	std::cout << "left\n";

		//if (m.isButtonPressed(0, XINPUT_GAMEPAD_LEFT_SHOULDER))
		//	std::cout << "LB\n";
		//if (m.isButtonPressed(0, XINPUT_GAMEPAD_RIGHT_SHOULDER))
		//	std::cout << "RB\n";

		//if (m.isButtonPressed(0, XINPUT_GAMEPAD_LEFT_THUMB))
		//	std::cout << "LeftJButton\n";
		//if (m.isButtonPressed(0, XINPUT_GAMEPAD_RIGHT_THUMB))
		//	std::cout << "rightJButton\n";

		//if (m.isButtonPressed(0, XINPUT_GAMEPAD_BACK))
		//	std::cout << "select\n";
		//if (m.isButtonPressed(0, XINPUT_GAMEPAD_START))
		//	std::cout << "start\n";

		//if (m.TriggerPression(0,0) > 0.5)
		//	std::cout << m.TriggerPression(0, 0) << '\n';

		//if (m.TriggerPression(0,1) > 0.5)
		//	std::cout << m.TriggerPression(0, 1) << '\n';

		//if (abs(m.AxisPression(0, 0)) > 10)
		//	std::cout << m.AxisPression(0, 0) << '\n';
		//if (abs(m.AxisPression(0, 1)) > 10)
		//	std::cout << m.AxisPression(0, 1) << '\n';
		//if (abs(m.AxisPression(0, 2)) > 10)
		//	std::cout << m.AxisPression(0, 2) << '\n';
		//if (abs(m.AxisPression(0, 3)) > 10)
		//	std::cout << m.AxisPression(0, 3) << '\n';


	}

	return 0;
}

/*
///////////// 1 idea
manager::create("name", function binded, keys... variadic); // create the input
manager::remove("name");					// remove an input
manager::changekeys("name", new keys...);	// change all keys from the input
manager::addkey("name", new key);			// add a key to the input
manager::removekey("name", keys);			// remove a key from the input
manager::bind("name");						// can update
manager::unbind("name");					// don't update
manager::update();							// check for all input and do function
manager::ispressed("name");					// return if an input is pressed
specifier gamepad function

manager::bind("forward");
manager::bind("Right");

manager::updateAll();

manager::unbind("Rignt");
*/

/*InputManager m;

m.create("click", Action::onPress, [] {std::cout << "click "; }, sf::Mouse::Middle, sf::Mouse::Right, m.Button::B);
m.create("move", Action::KeyPressed, [] {std::cout << "move "; }, sf::Keyboard::Z, sf::Mouse::Left, m.Button::A);

m.create("change", Action::onRelease, [&m] { m.unbind("move"); }, sf::Keyboard::Escape);
m.create("change2", Action::onRelease, [&m] { m.bind("move"); }, sf::Keyboard::Enter);

m.create("test1", Action::onPress, [] { std::cout << "test 1" << std::endl; }, m.Axis::LeftJoystick_Left);
m.create("test2", Action::onPress, [] { std::cout << "test 2" << std::endl; }, m.Axis::LeftJoystick_Right);
m.create("test3", Action::onPress, [] { std::cout << "test 3" << std::endl; }, m.Axis::LeftJoystick_Up);
m.create("test4", Action::onPress, [] { std::cout << "test 4" << std::endl; }, m.Axis::LeftJoystick_Down);

m.create("test5", Action::onPress, [] { std::cout << "test 5" << std::endl; }, m.Axis::RightJoystick_Left);
m.create("test6", Action::onPress, [] { std::cout << "test 6" << std::endl; }, m.Axis::RightJoystick_Right);
m.create("test7", Action::onPress, [] { std::cout << "test 7" << std::endl; }, m.Axis::RightJoystick_Up);
m.create("test8", Action::onPress, [] { std::cout << "test 8" << std::endl; }, m.Axis::RightJoystick_Down);

m.create("test9", Action::onPress, [] { std::cout << "test 9" << std::endl; }, m.Axis::LT);
m.create("test10", Action::onPress, [] { std::cout << "test 10" << std::endl; }, m.Axis::RT);

m.create("test11", Action::onPress, [] { std::cout << "test 11" << std::endl; }, m.Axis::Cross_Left);
m.create("test12", Action::onPress, [] { std::cout << "test 12" << std::endl; }, m.Axis::Cross_Right);
m.create("test13", Action::onPress, [] { std::cout << "test 13" << std::endl; }, m.Axis::Cross_Up);
m.create("test14", Action::onPress, [] { std::cout << "test 14" << std::endl; }, m.Axis::Cross_Down);*/