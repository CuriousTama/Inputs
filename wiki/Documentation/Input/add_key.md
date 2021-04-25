# Documentation : Inputs

### add_key

template<class ...Args>
void add_key(std::string name, Args... keys);

### Parameters

| Name        | Description                                 |
|-------------|---------------------------------------------|
| **name**    | The name of the input you want to add keys. |
| **...keys** | The keys you want added.                    |

### Description
Add the number of key given to an input.

### How to use
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