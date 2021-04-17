# Tutorials : Input

## Disactivate / Reactivate an input

This part is about activating or disactivate an input for not have to remove and recreate one.

``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{
	Inputs inputs;

	inputs.create("first_input", Action::on_pressed, []{ /* stuff */ }, Keyboard::ENTER);

	// disactivate first_input
	inputs.unbind("first_input");
	
	// reactivate first_input
	inputs.bind("first_input");
	
	...
	
	return 0;
}
```

**function description :**
The first argument **(Name argument)** is the name of the input you want to activate or disactivate.

**Note :** you can check is an input is bind with is_bind function.