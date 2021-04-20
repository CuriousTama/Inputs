# Tutorials : Gamepads

## Set vibration


### Function 1 :	
``` C++ 
void vibration(unsigned short pad, float time, unsigned short power_both);
```

This function is for make a controller vibrate with both motor at the same power and stop after a given time. 

``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{
	Inputs inputs;

	inputs.Gamepads().vibration(0, 0.5f, 50);

	...
	
	return 0;
}
```
This line gonna make the gamepad with the id '0' vibrate with a power of 50% for 0.5 second. 


##
### Function 2 :
``` C++ 
void vibration(unsigned short pad, float time, unsigned short power_left, unsigned short power_right);
```

This function is for make a controller vibrate with motors at an given power and stop after a given time. 

``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{
	Inputs inputs;

	inputs.Gamepads().vibration(0, 0.5f, 10, 75);

	...
	
	return 0;
}
```
This line gonna make the gamepad with the id '0' vibrate for 0.5 second with left motor to 10% and right motor to 75 %. 


##
### Function 3 :
``` C++ 
void vibration(unsigned short pad, bool on, unsigned short power_both);
```

This function is for make a controller vibrate with both motors at an given power for an undefined time. 
If the second argument is false it stop vibrations regardless the power argument. 

``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{
	Inputs inputs;

	inputs.Gamepads().vibration(0, true, 50);

	...
	
	return 0;
}
```
This line gonna make the gamepad with the id '0' vibrate for an undefined time at a power of 50%. 


##
### Function 4 :
``` C++ 
void vibration(unsigned short pad, bool on, unsigned short power_left, unsigned short power_right);
```

This function is for make a controller vibrate with motors at an given power for an undefined time. 
If the second argument is false it stop vibrations regardless the power argument. 

``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{
	Inputs inputs;

	inputs.Gamepads().vibration(0, true, 10, 75);

	...
	
	return 0;
}
```
This line gonna make the gamepad with the id '0' vibrate for an undefined time at a power of 10% for the left motor and 75% for the right motor. 