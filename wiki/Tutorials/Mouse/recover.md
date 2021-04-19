# Tutorials : Mouse

## Recover Mouse class

This part is about recovering Mouse class from Inputs.

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
	Mouse& m = inputs.Mouse();
}

// version 2
void foo()
{
	// every Keyboard instance share same values
	Mouse m;
}
```

**Note :** Since that every instance of Mouse share same values version 1 is only for readability.