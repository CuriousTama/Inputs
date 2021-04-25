# Tutorials : Input

##  Make your first input and work with it (Option 2)

The second option is to not give a function and only get when the condition is completed


``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{
	Inputs inputs;

	inputs.create("first_input", Action::on_pressed, 
	Keyboard::ENTER, Mouse::LEFT_BUTTON, Pad(0, Xbox::A), ...);

	while (game_loop) 
	{
		inputs.update();

		if (inputs.is_triggered("first_input"))
		{
			std::cout << "First input fuction. \n";
		}		

		...
	}
	
	return 0;
}
```

**function create :**
The first argument **(Name argument)** is the name of the input, we gonna use it when we want to do a thing to a specific input.

The second argument **(Action argument)** it's one of our execution condition :

| Actions         | Description                          |
|-----------------|--------------------------------------|
| **is_pressed**  | The condition if a key is pressed    | 
| **is_released** | The condition if a key is released   | 
| **on_pressed**  | The condition when a key is pressed  | 
| **on_release**  | The condition when a key is released | 

Every other arguments **(Key arguments)** are there for the execution condition for limited the execution to some keys **(minimum one needed)**

| Material    | How to add it                                       |
|-------------|-----------------------------------------------------|
| Keyboard    | Keyboard::**Key_you_want**                          | 
| Mouse		  | Mouse::**Key_you_want**                             | 
| Gamepad     | Pad(**Number_of_the_pad**, xbox::**Key_you_want**)  | 

See enumeration here :
[Keyboard]()
[Mouse]()
[Xbox and Playstation]()

**Note for gamepad :** 
- **Number_of_the_pad** can't be greater than 3  (0,1,2,3)
- You can put -1 on **Number_of_the_pad** to make for all gamepads
- You can do your own enumeration for gamepad.