# Tutorials : Gamepads

## Recover Gamepads class

This part is about recovering Gamepads class from Inputs.

``` C++
#include "Inputs.h"

void foo(...);

int main(int argc, char** argv) 
{
	Inputs inputs;
	
	while (game_loop)
	{
		inputs.update();
		
		foo(...);

		...
	}
	
	return 0;
}

// version 1
void foo(Inputs& inputs)
{
	Gamepads& gamepads = inputs.Gamepads();
}

// version 2
void foo()
{
	// every Gamepads's instance share same values
	Gamepads gamepads;
}
```

**Note :** Since that every instance of Gamepads share same values version 1 is only for readability.