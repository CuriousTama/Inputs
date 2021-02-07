#pragma once
#include <iostream>

template <class _Elem>
constexpr void DebugWarning(_Elem str)
{
#if !NDEBUG
	std::cerr << "\033[33m" << "DEBUG WARNING >> " << str << "\033[0m" << std::endl;
#endif
}

template <class _Elem>
constexpr void Warning(_Elem str)
{
	std::cerr << "\033[33m" << "WARNING >> " << str << "\033[0m" << std::endl;
}

template <class _Elem>
constexpr void DebugError(_Elem str)
{
#if !NDEBUG
	std::cerr << "\033[91m" << "DEBUG ERROR >> " << str << "\033[0m" << std::endl;
#endif
}

template <class _Elem>
constexpr void Error(_Elem str)
{
	std::cerr << "\033[91m" << "ERROR >> " << str << "\033[0m" << std::endl;
}