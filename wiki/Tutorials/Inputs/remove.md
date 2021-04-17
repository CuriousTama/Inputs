# Tutorials : Input

## Remove an input

This part is about removing inputs.

``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{
	Inputs inputs;

	inputs.create("first_input", Action::on_pressed, []{ /* stuff */ }, Keyboard::ENTER);

	inputs.remove("first_input");
	
	...
	
	return 0;
}
```

**function description :**
The first argument **(Name argument)** is the name of the input you want to remove.