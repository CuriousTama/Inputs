# Tutorials : Keyboard

## Get keys status

This part is about recovering Keyboard key status.

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
	Keyboard k;
	
	if (k.on_pressed(Keyboard::ENTER))
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
| **text_pressed** | The condition like on a text software| 

**function description :**
The first argument **(Key argument)** is the key to check.