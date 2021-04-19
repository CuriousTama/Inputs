# Tutorials : Mouse

## Get Buttons status

This part is about recovering Mouse button status.

``` C++
#include "Inputs.h"

void foo();

int main(int argc, char** argv) 
{
	Inputs inputs;
	
	while (game_loop)
	{
		inputs.update():

		foo();
		
		...
	}
	
	return 0;
}

void foo()
{
	Mouse m;
	
	if (m.on_pressed(Mouse::LEFT_BUTTON))
	{
		std::cout << "foo function" << std::endl;
	}
}
```

| member Functions | Description                          |
|------------------|--------------------------------------|
| **is_pressed**   | The condition if a key is pressed    | 
| **is_released**  | The condition if a key is released   | 
| **on_pressed**   | The condition when a key is pressed  | 
| **on_release**   | The condition when a key is released | 

**function description :**
The first argument **(Key argument)** is the key to check.

**Note :** for **SCROLL_UP** and **SCROLL_DOWN** keys **is_...** and **on_...** functions do the same condition