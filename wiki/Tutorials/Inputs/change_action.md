# Tutorials : Input

##  Change action of an input

This part is about changing the action to the execution condition

``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{
	Inputs inputs;

	inputs.create("first_input", Action::on_pressed, []{ /* stuff */ }, Keyboard::ENTER);

	inputs.redefine_action("first_input", Action::on_release);

	...
	
	return 0;
}
```

**function description :**
The first argument **(Name argument)** is the name of the input you want to change action.

The second argument **(Action argument)** is the new action.


| Actions         | Description                          |
|-----------------|--------------------------------------|
| **is_pressed**  | The condition if a key is pressed    | 
| **is_released** | The condition if a key is released   | 
| **on_pressed**  | The condition when a key is pressed  | 
| **on_release**  | The condition when a key is released | 