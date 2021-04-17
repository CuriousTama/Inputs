# Tutorials : Input

##  Create Input class and keep it updated



``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{
	Inputs inputs;

	while (game_loop) 
	{
		inputs.update();
		
		...
	}
	
	return 0;
}
```

 the update function gonna keep updated keyboard, mouse and gamepad and check if an input we gave him is triggered and do the function we want if we give him one.