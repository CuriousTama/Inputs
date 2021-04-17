# Tutorials : Input

## Change automatic function of an input

This part is about changing the function of an input

``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{
	Inputs inputs;

	inputs.create("first_input", Action::on_pressed, []{ /* stuff A */ }, Keyboard::ENTER);

	inputs.redefine_function("first_input", []{ /* stuff B */ });

	...
	
	return 0;
}
```

**function description :**
The first argument **(Name argument)** is the name of the input you want to change action.

The second argument **(Function argument)** is the new function.