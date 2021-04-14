#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <functional>
#include <variant>
#include <map>
#include <iostream>

#include "GamePad.h"
#include "PC.h"
#include "Errors.h"

class InputManager;

enum class Action { KeyPressed, onPress, onRelease };
class Input {
	friend InputManager;

	using Key = std::variant<PC::KeyBoard, PC::Mouse,
		std::pair<int, Xbox::Button>, std::pair<int, Xbox::Trigger>,
		std::pair<int, Xbox::Axis>>;

	PC::Computer* c;
	Xbox_one* x;

	std::function<void()> func;
	std::vector<Key> keys;
	bool pressed{ false };
	Action type;

	void _removeKey(PC::KeyBoard k) {
		for (auto it = std::begin(keys); it != std::end(keys); it++) {
			if (it->index() == 0) {
				if (std::get<0>(*it) == k) {
					keys.erase(it);
					return;
				}
			}
		}
	}

	void _removeKey(PC::Mouse k) {
		for (auto it = std::begin(keys); it != std::end(keys); it++) {
			if (it->index() == 1) {
				if (std::get<1>(*it) == k) {
					keys.erase(it);
					return;
				}
			}
		}
	}

	void _removeKey(std::pair<int, Xbox::Button> k) {
		for (auto it = std::begin(keys); it != std::end(keys); it++) {
			if (it->index() == 2) {
				if (std::get<2>(*it) == k) {
					keys.erase(it);
					return;
				}
			}
		}
	}

	void _removeKey(std::pair<int, Xbox::Trigger> k) {
		for (auto it = std::begin(keys); it != std::end(keys); it++) {
			if (it->index() == 3) {
				if (std::get<3>(*it) == k) {
					keys.erase(it);
					return;
				}
			}
		}
	}

	void _removeKey(std::pair<int, Xbox::Axis> k) {
		for (auto it = std::begin(keys); it != std::end(keys); it++) {
			if (it->index() == 4) {
				if (std::get<4>(*it) == k) {
					keys.erase(it);
					return;
				}
			}
		}
	}

public:
	template<class FUNC, class ...Keys>
	Input(PC::Computer* cptr, Xbox_one* xptr, Action action, FUNC f, Keys... inputs) : c(cptr), x(xptr) {
		type = action;
		func = f;
		addKey(inputs...);
	}

	~Input() = default;

	template<class K>
	void addKey(K k) {
		keys.push_back(k);
	}

	template<class K>
	void addKey(std::pair<int, K> k) {
		for (int i = 0; i < 4; i++) {
			keys.push_back(Pad(i, k.second));
		}
	}

	template<class K, class ...Keys>
	void addKey(K k, Keys... inputs) {
		addKey(k);
		addKey(inputs...);
	}

	template<class K>
	void removeKey(K k) {
		_removeKey(k);
	}

	template<class K>
	void removeKey(std::pair<int, K> k) {
		for (int i = 0; i < 4; i++) {
			_removeKey(Pad(i, k.second));
		}
	}

	template<class K, class ...Keys>
	void removeKey(K k, Keys... inputs) {
		removeKey(k);
		removeKey(inputs...);
	}

	void eventUpdate() {
		bool current_state = this->pressed;

		for (auto it = std::begin(keys); it != std::end(keys); it++) {

			if (this->pressed == current_state) {

				if (it->index() == 0) { // Keyboard 
					if (this->type == Action::KeyPressed) {
						this->pressed = c->isPressed(std::get<PC::KeyBoard>(*it));
					}

					else if (this->type == Action::onPress) {
						this->pressed = c->onPressed(std::get<PC::KeyBoard>(*it));
					}

					else if (this->type == Action::onRelease) {
						this->pressed = c->onRelease(std::get<PC::KeyBoard>(*it));
					}
				}

				else if (it->index() == 1) { // mouse	
					if (this->type == Action::KeyPressed) {
						this->pressed = c->isPressed(std::get<PC::Mouse>(*it));
					}

					else if (this->type == Action::onPress) {
						this->pressed = c->onPressed(std::get<PC::Mouse>(*it));
					}

					else if (this->type == Action::onRelease) {
						this->pressed = c->onRelease(std::get<PC::Mouse>(*it));
					}
				}

				else if (it->index() == 2) { // game pad button 
					auto p = std::get<2>(*it);

					if (this->type == Action::KeyPressed) {
						this->pressed = x->isPressed(p.first, p.second);
					}

					else if (this->type == Action::onPress) {
						this->pressed = x->onPressed(p.first, p.second);
					}

					else if (this->type == Action::onRelease) {
						this->pressed = x->OnRelease(p.first, p.second);
					}
				}

				else if (it->index() == 3) { // game pad trigger
					auto p = std::get<3>(*it);

					if (this->type == Action::KeyPressed) {
						this->pressed = x->isPressed(p.first, p.second);
					}

					else if (this->type == Action::onPress) {
						this->pressed = x->onPressed(p.first, p.second);
					}

					else if (this->type == Action::onRelease) {
						this->pressed = x->OnRelease(p.first, p.second);
					}
				}

				else if (it->index() == 4) { // game pad axis
					auto p = std::get<4>(*it);

					if (this->type == Action::KeyPressed) {
						this->pressed = x->isPressed(p.first, p.second);
					}

					else if (this->type == Action::onPress) {
						this->pressed = x->onPressed(p.first, p.second);
					}

					else if (this->type == Action::onRelease) {
						this->pressed = x->OnRelease(p.first, p.second);
					}
				}
			}
		}
	}

	void update() {
		if (this->pressed) {
			func();

			if (this->type == Action::onPress || this->type == Action::onRelease) {
				this->pressed = false;
			}
		}
	}

	inline bool isActive() const {
		return pressed;
	}
};

class InputManager {
	std::map<std::string, std::pair<Input, bool>> InputList;
	void eventUpdate() {
		for (auto it = InputList.begin(); it != InputList.end(); it++) {
			if (it->second.second == true) {
				it->second.first.eventUpdate();
			}
		}
	}

public:
	InputManager() = default;
	~InputManager() = default;

	PC::Computer c;
	Xbox_one x;

	template<class FUNC, class ...Args>
	void create(std::string name, Action action, FUNC f, Args... args) {
		if (InputList.find(name) != InputList.end()) {
			DebugWarning("the name : " + name + ", already exist in inputs (create function)");
		}

		InputList.insert(std::make_pair(name, std::make_pair<Input, bool>(Input(&c, &x, action, f, args...), true)));
	}

	bool isActive(std::string name) {
		auto f = InputList.find(name);

		if (f == InputList.end()) {
			DebugWarning("the name : " + name + ", doesn't exist in inputs (isActive function)");
			return false;
		}

		return f->second.first.isActive();
	}

	bool isBind(std::string name) {
		auto element = InputList.find(name);

		if (element == InputList.end()) {
			DebugWarning("the name : " + name + ", doesn't exist in inputs (isBind function)");
			return false;
		}

		return element->second.second;
	}

	void update() {
		x.GamePadUpdate();
		c.Update();

		this->eventUpdate();

		for (auto it = InputList.begin(); it != InputList.end(); it++) {
			if (it->second.second == true) {
				it->second.first.update();
			}
		}
	}

	void bind(std::string name) {
		auto element = InputList.find(name);

		if (element != InputList.end()) {
			element->second.second = true;
		}
		else {
			DebugWarning("the input : " + name + ", doesn't exist (bind function)");
		}
	}

	void unbind(std::string name) {
		auto element = InputList.find(name);

		if (element != InputList.end()) {
			element->second.second = false;
		}
		else {
			DebugWarning("the input : " + name + ", doesn't exist (unbind function)");
		}
	}

	void remove(std::string name) {
		if (auto f = InputList.find(name); f == InputList.end()) {
			DebugWarning("the name : " + name + ", doesn't exist in inputs (remove function)");
		}
		else {
			InputList.erase(f);
		}
	}

	template<class ...Args>
	void addkey(std::string name, Args... keys) {
		if (auto f = InputList.find(name); f == InputList.end()) {
			DebugWarning("the name : " + name + ", doesn't exist in inputs (addKey function)");
		}
		else {
			f->second.first.addKey(keys...);
		}
	}

	template<class ...Args>
	void Changekeys(std::string name, Args... keys) {
		if (auto f = InputList.find(name); f == InputList.end()) {
			DebugWarning("the name : " + name + ", doesn't exist in inputs (addKey function)");
		}
		else {
			f->second.first.keys.clear();
			f->second.first.addKey(keys...);
		}
	}

	template<class ...Args>
	void removekey(std::string name, Args... keys) {
		if (auto f = InputList.find(name); f == InputList.end()) {
			DebugWarning("the name : " + name + ", doesn't exist in inputs (addKey function)");
		}
		else {
			f->second.first.removeKey(keys...);
		}
	}

	void redefineAction(std::string name, std::function<void()> f) {
		auto element = InputList.find(name);

		if (element != InputList.end()) {
			element->second.first.func = f;
		}
		else {
			DebugWarning("the input : " + name + ", doesn't exist (redefineAction function)");
		}
	}
};

#endif // !INPUTMANAGER_H