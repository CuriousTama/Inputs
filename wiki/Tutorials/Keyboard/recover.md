# Tutorials : Keyboard

## Recover Keyboard class

This part is about recovering Keyboard class from Inputs.

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
	Keyboard& k = inputs.Keyboard();
}

// version 2
void foo()
{
	// every Keyboard instance share same values
	Keyboard k;
}
```

**Note :** Since that every instance of keyboard share same values version 1 is only for readability.