#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <functional>
#include <variant>
#include <map>
#include <iostream>

#include "GamePad.h"
#include "PC.h"
#include "Errors.h"

enum class Action { KeyPressed, onPress, onRelease };
class Input
{
	using Key = std::variant<PC::KeyBoard, PC::Mouse, Xbox_one_::Button, Xbox_one_::Trigger, Xbox_one_::Axis>;

	PC::Computer* c;
	Xbox_one* x;

	std::function<void()> func;
	std::vector<Key> keys;
	bool pressed = false;
	Action type;

public:
	template<class FUNC, class ...Keys>
	Input(PC::Computer* cptr, Xbox_one* xptr, Action action, FUNC f, Keys... inputs);

	template<class K>
	void addKey(K k);

	template<class K, class ...Keys>
	void addKey(K k, Keys... inputs);

	void eventUpdate();
	void update();

	bool isactive() const { return pressed; }

	~Input() {}
};

class InputManager
{
	std::map<std::string, std::pair<Input, bool>> InputList;
	void eventUpdate();

public:
	InputManager() {}
	~InputManager() {}
	
	PC::Computer c;
	Xbox_one x;

	template<class FUNC, class ...Args>
	void create(std::string name, Action action, FUNC f, Args... args);

	void bind(std::string name);
	void unbind(std::string name);

	void remove(std::string name);

	template<class ...Args>
	void addkey(std::string name, Args... keys);

	bool isActive(std::string name);

	void update();
};






template<class FUNC, class ...Args>
inline void InputManager::create(std::string name, Action action, FUNC f, Args ...args)
{
	if (InputList.find(name) != InputList.end())
		DebugWarning("the name : " + name + ", already exist in inputs (create function)");

	InputList.insert(std::make_pair(name, std::make_pair<Input, bool>(Input(&c, &x, action, f, args...), true)));
}




template<class ...Args>
void InputManager::addkey(std::string name, Args... keys)
{
	if (auto f = InputList.find(name); f == InputList.end())
		DebugWarning("the name : " + name + ", doesn't exist in inputs (addKey function)");
	else
		f->second.first.addKey(keys...);
}

template<class FUNC, class ...Keys>
inline Input::Input(PC::Computer* cptr, Xbox_one* xptr,Action action, FUNC f, Keys ...inputs)
: c(cptr), x(xptr)
{
	type = action;
	func = f;
	addKey(inputs...);
	pressed = false;
}

template<class K>
void Input::addKey(K k)
{
	keys.push_back(k);
}

template<class K, class ...Keys>
inline void Input::addKey(K k, Keys ...inputs)
{
	keys.push_back(k);
	addKey(inputs...);
}

#endif // !INPUTMANAGER_H