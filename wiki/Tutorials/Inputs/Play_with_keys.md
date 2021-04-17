# Tutorials : Input

##  Play with keys after an input is created

This part is about modification on keys that can be make after the creation.


### Add key

with the function add_key you can add keys to an input

``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{
	Inputs inputs;

	inputs.create("first_input", Action::on_pressed, []{ /* stuff */ }, Keyboard::ENTER);

	inputs.add_key("first_input", Keyboard::SPACE, ...);

	...
	
	return 0;
}
```

**function description :**
The first argument **(Name argument)** is the name of the input you want to add keys.

Every other arguments **(Key arguments)** are keys you want to add.






##
### Remove key

with the function remove_key you can remove keys of an input

``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{
	Inputs inputs;

	inputs.create("first_input", Action::on_pressed, []{ /* stuff */ }, Keyboard::ENTER, Keyboard::SPACE);

	inputs.remove_key("first_input", Keyboard::SPACE, ...);

	...
	
	
	return 0;
}
```

**function description :**
The first argument **(Name argument)** is the name of the input you want to remove keys.

Every other arguments **(Key arguments)** are keys you want to remove.





##
### Change keys

with the function change_keys you can change all keys of an input (remove all key and set new ones)

``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{
	Inputs inputs;

	inputs.create("first_input", Action::on_pressed, []{ /* stuff */ }, Keyboard::ENTER);

	inputs.change_keys("first_input", Keyboard::SPACE, ...);

	...
	
	return 0;
}
```

**function description :**
The first argument **(Name argument)** is the name of the input you want to remove keys.

Every other arguments **(Key arguments)** are keys you want to set.