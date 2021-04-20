# Tutorials : Gamepads

## Get if a gamepad is connected

``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{
	Inputs inputs;

	if (inputs.Gamepads().is_connected(0))
	{
		std::cout << "Controller number 1 is connected" << std::endl;
	}	

	while (game_loop)
	{
		...
	}
	
	return 0;
}
```

**Note :** Argument value is only between 0 to 3.