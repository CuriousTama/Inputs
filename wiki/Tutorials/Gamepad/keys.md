# Tutorials : Gamepads

## Get (buttons / Triggers / axis) status


``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{
	Inputs inputs;
	
	while (game_loop)
	{
		inputs.update():

		if (inputs.Gamepads().on_pressed(0, Xbox::A))
		{
			std::cout << "'A' boutton pressed." << std::endl;
		}
		
		...
	}
	
	return 0;
}
```

| member Functions | Description                          |
|------------------|--------------------------------------|
| **is_pressed**   | The condition if a key is pressed    | 
| **is_released**  | The condition if a key is released   | 
| **on_pressed**   | The condition when a key is pressed  | 
| **on_release**   | The condition when a key is released | 

**function description :**
The First argument is the controller to check only between 0 to 3.
The second argument **(Key argument)** is the key to check.