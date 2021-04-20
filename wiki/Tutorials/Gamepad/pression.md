# Tutorials : Gamepads

## Get (Triggers / axis) pression


``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{
	Inputs inputs;
	
	while (game_loop)
	{
		inputs.update():
		Gamepads g;
		
		std::cout << "LStick pression : " << g.axis_pression(0, Xbox::LeftJoystick_Right) << std::endl;
		std::cout << "RT pression : " << g.trigger_pression(0, Xbox::RT) << std::endl;
		
		...
	}
	
	return 0;
}
```

**function description :**
The First argument is the controller to check only between 0 to 3.
The second argument **(Key argument)** is the key to check.

**Return :** A value between 0 to 100.