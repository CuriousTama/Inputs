#ifndef ERROR_H
#define ERROR_H

#include <iostream>

#define FOREGROUND_DEFAULT		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE		// default color of console text
#define FOREGROUND_ORANGE		FOREGROUND_RED | FOREGROUND_GREEN						// red + green = orange
#define FOREGROUND_LIGHT_RED	FOREGROUND_RED | FOREGROUND_INTENSITY					// red + Intensity = light red

template <class _Elem>
constexpr void DebugWarning(_Elem str) {
#if !NDEBUG
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_ORANGE);
	std::cerr << "DEBUG WARNING >> " << str << std::endl;
	SetConsoleTextAttribute(hConsole, FOREGROUND_DEFAULT);
#endif
}

template <class _Elem>
constexpr void Warning(_Elem str) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_ORANGE);
	std::cerr << "WARNING >> " << str << std::endl;
	SetConsoleTextAttribute(hConsole, FOREGROUND_DEFAULT);
}

template <class _Elem>
constexpr void DebugError(_Elem str) {
#if !NDEBUG
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_LIGHT_RED);
	std::cerr << "DEBUG ERROR >> " << str << std::endl;
	SetConsoleTextAttribute(hConsole, FOREGROUND_DEFAULT);
#endif
}

template <class _Elem>
constexpr void Error(_Elem str) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_LIGHT_RED);
	std::cerr << "ERROR >> " << str << std::endl;
	SetConsoleTextAttribute(hConsole, FOREGROUND_DEFAULT);
}

#endif // !ERROR_H