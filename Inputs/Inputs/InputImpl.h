#ifndef INPUTIMPL_H
#define INPUTIMPL_H

#include <variant>
#include "Mouse.h"
#include "GamePad.h"
#include "KeyBoard.h"
#include <functional>

class Inputs;

enum class Action { is_pressed, is_released, on_pressed, on_release };

class InputImpl {
	friend Inputs;

	using Key = std::variant<Keyboard::Key, Mouse::Key,
		std::pair<int, Xbox::Button>, std::pair<int, Xbox::Trigger>,
		std::pair<int, Xbox::Axis>>;

	Gamepads* g;
	Keyboard* k;
	Mouse* m;

	std::function<void()> func;
	std::vector<Key> m_keys;
	bool pressed{ false };
	Action type;

	template<class ...Keys>
	InputImpl(Keyboard* kptr, Mouse* mptr, Gamepads* xptr, Action action, std::function<void()> f, Keys... inputs) : k(kptr), m(mptr), g(xptr) {
		type = action;
		func = f;
		addKey(inputs...);
	}

#pragma region convert
	constexpr Xbox::Button convert_button(unsigned short i) {
		if (is_Button(i)) {
			return static_cast<Xbox::Button>(i);
		}
		else {
			Error("Fail convert custom enum to input");
			return Xbox::Button::A;
		}
	}

	constexpr Xbox::Trigger convert_trigger(unsigned short i) {
		if (is_Trigger(i)) {
			return static_cast<Xbox::Trigger>(i);
		}
		else {
			Error("Fail convert custom enum to input");
			return Xbox::Trigger::LT;
		}
	}

	constexpr Xbox::Axis convert_axis(unsigned short i) {
		if (is_Axis(i)) {
			return static_cast<Xbox::Axis>(i);
		}
		else {
			Error("Fail convert custom enum to input");
			return Xbox::Axis::LeftJoystick_Down;
		}
	}
#pragma endregion convert

#pragma region Remove
	void _removeKey(Keyboard::Key k) {
		for (auto it = std::begin(m_keys); it != std::end(m_keys); it++) {
			if (it->index() == 0) {
				if (std::get<0>(*it) == k) {
					m_keys.erase(it);
					return;
				}
			}
		}
	}

	void _removeKey(Mouse::Key k) {
		for (auto it = std::begin(m_keys); it != std::end(m_keys); it++) {
			if (it->index() == 1) {
				if (std::get<1>(*it) == k) {
					m_keys.erase(it);
					return;
				}
			}
		}
	}

	void _removeKey(std::pair<int, Xbox::Button> k) {
		for (auto it = std::begin(m_keys); it != std::end(m_keys); it++) {
			if (it->index() == 2) {
				if (std::get<2>(*it) == k) {
					m_keys.erase(it);
					return;
				}
			}
		}
	}

	void _removeKey(std::pair<int, Xbox::Trigger> k) {
		for (auto it = std::begin(m_keys); it != std::end(m_keys); it++) {
			if (it->index() == 3) {
				if (std::get<3>(*it) == k) {
					m_keys.erase(it);
					return;
				}
			}
		}
	}

	void _removeKey(std::pair<int, Xbox::Axis> k) {
		for (auto it = std::begin(m_keys); it != std::end(m_keys); it++) {
			if (it->index() == 4) {
				if (std::get<4>(*it) == k) {
					m_keys.erase(it);
					return;
				}
			}
		}
	}

	template<class K>
	void removeKey(K k) {
		_removeKey(k);
	}

	template<class K>
	void removeKey(std::pair<int, K> k) {
		if (k.first == -1) {
			for (int i = 0; i < 4; i++) {
				_removeKey(Pad(i, k.second));
			}
			return;
		}

		_removeKey(k);
	}

	template<class K, class ...Keys>
	void removeKey(K k, Keys... inputs) {
		removeKey(k);
		removeKey(inputs...);
	}
#pragma endregion Remove

#pragma region AddKey
	template<class K>
	constexpr void addKey(K k) {
		m_keys.push_back(k);
	}

	template<class K>
	constexpr void addKey(std::pair<int, K> k) {
		if (k.first == -1) {
			for (int i = 0; i < 4; i++) {
				if (is_Button(k.second)) {
					m_keys.push_back(Pad(i, convert_button(k.second)));
				}
				else if (is_Trigger(k.second)) {
					m_keys.push_back(Pad(i, convert_trigger(k.second)));
				}
				else if (is_Axis(k.second)) {
					m_keys.push_back(Pad(i, convert_axis(k.second)));
				}
			}
			return;
		}

		if (is_Button(k.second)) {
			m_keys.push_back(Pad(k.first, convert_button(k.second)));
		}
		else if (is_Trigger(k.second)) {
			m_keys.push_back(Pad(k.first, convert_trigger(k.second)));
		}
		else if (is_Axis(k.second)) {
			m_keys.push_back(Pad(k.first, convert_axis(k.second)));
		}
	}

	template<class K, class ...Keys>
	constexpr void addKey(K k, Keys... inputs) {
		addKey(k);
		addKey(inputs...);
	}
#pragma endregion AddKey

	void eventUpdate() {
		int release_count = 0;
		this->pressed = false;

		std::for_each(std::begin(m_keys), std::end(m_keys), [this, &release_count](auto& it) {
			if (this->pressed == false) {

				if (it.index() == 0) { // Keyboard 
					if (this->type == Action::is_pressed) {
						this->pressed = k->is_pressed(std::get<Keyboard::Key>(it));
					}

					else if (this->type == Action::is_released) {
						release_count += !k->is_pressed(std::get<Keyboard::Key>(it));
					}

					else if (this->type == Action::on_pressed) {
						this->pressed = k->on_pressed(std::get<Keyboard::Key>(it));
					}

					else if (this->type == Action::on_release) {
						this->pressed = k->on_release(std::get<Keyboard::Key>(it));
					}
				}

				else if (it.index() == 1) { // mouse	
					if (this->type == Action::is_pressed) {
						this->pressed = m->is_pressed(std::get<Mouse::Key>(it));
					}

					else if (this->type == Action::is_released) {
						release_count += !m->is_pressed(std::get<Mouse::Key>(it));
					}

					else if (this->type == Action::on_pressed) {
						this->pressed = m->on_pressed(std::get<Mouse::Key>(it));
					}

					else if (this->type == Action::on_release) {
						this->pressed = m->on_release(std::get<Mouse::Key>(it));
					}
				}

				else if (it.index() == 2) { // game pad button 
					auto p = std::get<2>(it);

					if (this->type == Action::is_pressed) {
						this->pressed = g->is_pressed(p.first, p.second);
					}

					else if (this->type == Action::is_released) {
						release_count += !g->is_pressed(p.first, p.second);
					}

					else if (this->type == Action::on_pressed) {
						this->pressed = g->on_pressed(p.first, p.second);
					}

					else if (this->type == Action::on_release) {
						this->pressed = g->on_release(p.first, p.second);
					}
				}

				else if (it.index() == 3) { // game pad trigger
					auto p = std::get<3>(it);

					if (this->type == Action::is_pressed) {
						this->pressed = g->is_pressed(p.first, p.second);
					}

					else if (this->type == Action::is_released) {
						release_count += !g->is_pressed(p.first, p.second);
					}

					else if (this->type == Action::on_pressed) {
						this->pressed = g->on_pressed(p.first, p.second);
					}

					else if (this->type == Action::on_release) {
						this->pressed = g->on_release(p.first, p.second);
					}
				}

				else if (it.index() == 4) { // game pad axis
					auto p = std::get<4>(it);

					if (this->type == Action::is_pressed) {
						this->pressed = g->is_pressed(p.first, p.second);
					}

					else if (this->type == Action::is_released) {
						release_count += !g->is_pressed(p.first, p.second);
					}

					else if (this->type == Action::on_pressed) {
						this->pressed = g->on_pressed(p.first, p.second);
					}

					else if (this->type == Action::on_release) {
						this->pressed = g->on_release(p.first, p.second);
					}
				}
			}
			}
		);

		if (this->type == Action::is_released && release_count == this->m_keys.size()) {
			this->pressed = true;
		}

		if (this->pressed) {
			func();
		}
	}

	constexpr inline bool is_triggered() const {
		return pressed;
	}

public:
	~InputImpl() = default;
};

#endif // INPUTIMPL_H