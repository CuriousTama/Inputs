# Tutorials : Mouse

## Other functions

### Get Mouse position

``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{	
	Mouse mouse;
	std::cout << mouse.getMousePos().x << " : " << mouse.getMousePos().y << std::endl;

	...
	
	return 0;
}
```

**Return value :**
Coordinate based from the top left corner of the main monitor.

##
### Get Scrolling position

``` C++
#include "Inputs.h"

int main(int argc, char** argv) 
{	
	Mouse mouse;
	std::cout << mouse.getScroll() << std::endl;

	...
	
	return 0;
}
```

**Possible return values :** 
- SCROLL_UP (120)
- 0
- SCROLL_DOWN (-120)