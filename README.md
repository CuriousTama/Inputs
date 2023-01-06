# Input management with XInput

see [wiki](wiki/README.md)

### Goal :
- Make an input system (event based) base of XInput for keyboard, mouse and gamepad and bind to those action any type of function.

### Why this project ? :
- At this time I worked with the SFML library, it doesn't have an implementation for haptic feedback (Gamepad vibration).

### Problem encounters and how I have resolved them : 
- Make the program work with MSVC and Clang compilers : refactor a part of the code.
- Get mouse data from windows library : Documentation

### What I've learned :
- To use XInput.
- Reinforced my knowledge with bitwise operators
- Reinforced my knowledge with variadic templates
