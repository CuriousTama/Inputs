#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <map>
#include "InputImpl.h"

class Inputs {
	std::map<std::string, std::pair<InputImpl, bool>> InputList;

	Gamepads g;
	Keyboard k;
	Mouse m;

public:
	Inputs() = default;
	~Inputs() = default;

	Gamepads& Gamepads() { return g; }
	Keyboard& Keyboard() { return k; }
	Mouse& Mouse() { return m; }

	bool operator()(std::string name) { return this->is_triggered(name); };

	template<class ...Args>
	void create(std::string name, Action action, std::function<void()> f, Args... args) {
		if (InputList.find(name) != std::end(InputList)) {
			DebugWarning("the name : " + name + ", already exist in inputs (create function)");
		}

		InputList.insert(std::make_pair(name, std::make_pair<InputImpl, bool>(InputImpl(&k, &m, &g, action, f, args...), true)));
	}

	template<class ...Args>
	void create(std::string name, Action action, InputImpl::Key key, Args... args) {
		if (InputList.find(name) != std::end(InputList)) {
			DebugWarning("the name : " + name + ", already exist in inputs (create function)");
		}
		
		InputList.insert(std::make_pair(name, std::make_pair<InputImpl, bool>(InputImpl(&k, &m, &g, action, [] {}, key, args...), true)));
	}

	bool is_triggered(std::string name) {
		auto it = InputList.find(name);

		if (it == std::end(InputList)) {
			DebugWarning("the name : " + name + ", doesn't exist in inputs (isActive function)");
			return false;
		}

		return it->second.first.is_triggered();
	}

	bool is_bind(std::string name) {
		auto it = InputList.find(name);

		if (it == std::end(InputList)) {
			DebugWarning("the name : " + name + ", doesn't exist in inputs (isBind function)");
			return false;
		}

		return it->second.second;
	}

	void update() {
		g.update();
		k.eventUpdate();
		m.eventUpdate();

		std::for_each(std::begin(InputList), std::end(InputList), [](auto& it) {
			if (it.second.second == true) {
				it.second.first.eventUpdate();
			}}
		);
	}

	void bind(std::string name) {
		auto it = InputList.find(name);

		if (it != std::end(InputList)) {
			it->second.second = true;
		}
		else {
			DebugWarning("the input : " + name + ", doesn't exist (bind function)");
		}
	}

	void unbind(std::string name) {
		auto it = InputList.find(name);

		if (it != std::end(InputList)) {
			it->second.second = false;
		}
		else {
			DebugWarning("the input : " + name + ", doesn't exist (unbind function)");
		}
	}

	void remove(std::string name) {
		auto it = InputList.find(name);

		if (it == std::end(InputList)) {
			DebugWarning("the input : " + name + ", doesn't exist in inputs (remove function)");
		}
		else {
			InputList.erase(it);
		}
	}

	template<class ...Args>
	void add_key(std::string name, Args... keys) {
		auto it = InputList.find(name);

		if (it == std::end(InputList)) {
			DebugWarning("the input : " + name + ", doesn't exist in inputs (addKey function)");
		}
		else {
			it->second.first.addKey(keys...);
		}
	}

	template<class ...Args>
	void change_keys(std::string name, Args... keys) {
		auto it = InputList.find(name);

		if (it == std::end(InputList)) {
			DebugWarning("the input : " + name + ", doesn't exist in inputs (addKey function)");
		}
		else {
			it->second.first.m_keys.clear();
			it->second.first.addKey(keys...);
		}
	}

	template<class ...Args>
	void remove_key(std::string name, Args... keys) {
		auto it = InputList.find(name);

		if (it == std::end(InputList)) {
			DebugWarning("the input : " + name + ", doesn't exist in inputs (addKey function)");
		}
		else {
			it->second.first.removeKey(keys...);
		}
	}

	void redefine_function(std::string name, std::function<void()> f) {
		auto it = InputList.find(name);

		if (it != std::end(InputList)) {
			it->second.first.func = f;
		}
		else {
			DebugWarning("the input : " + name + ", doesn't exist (redefineAction function)");
		}
	}

	void redefine_action(std::string name, Action action) {
		auto it = InputList.find(name);

		if (it != std::end(InputList)) {
			it->second.first.type = action;
		}
		else {
			DebugWarning("the input : " + name + ", doesn't exist (redefineAction function)");
		}
	}
};

#endif // !INPUTMANAGER_H