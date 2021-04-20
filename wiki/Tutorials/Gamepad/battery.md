# Tutorials : Gamepads

## Get battery informations


``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{
	Inputs inputs;
	
	while (game_loop)
	{
		inputs.update():	
		
		if (inputs.Gamepads().battery_level(0) == Gamepads::LOW_BATTERY)
		{
			std::cout << "Low Battery" << std::endl;
		}
		
		...
	}
	
	return 0;
}
```

**function description :**
The First argument is the controller to check only between 0 to 3.

**Return :**
EMPTY_BATTERY (0)
LOW_BATTERY (1)
AVERAGE_BATTERY (2)
FULL_BATTERY (3)