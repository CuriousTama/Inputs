#include "InputManager.h"

void Input::eventUpdate()
{
	bool current_state = this->pressed;
	for (auto it = keys.begin(); it != keys.end(); it++)
	{
		if (this->pressed == current_state)
		{
			if (it->index() == 0) // Keyboard
			{
				if (this->type == Action::KeyPressed)
					this->pressed = c->isPressed(std::get<PC::KeyBoard>(*it));
				else if (this->type == Action::onPress)
					this->pressed = c->onPressed(std::get<PC::KeyBoard>(*it));
				else if (this->type == Action::onRelease)
					this->pressed = c->onRelease(std::get<PC::KeyBoard>(*it));
			}
			else if (it->index() == 1) // mouse
			{
				if (this->type == Action::KeyPressed)
					this->pressed = c->isPressed(std::get<PC::Mouse>(*it));
				else if (this->type == Action::onPress)
					this->pressed = c->onPressed(std::get<PC::Mouse>(*it));
				else if (this->type == Action::onRelease)
					this->pressed = c->onRelease(std::get<PC::Mouse>(*it));
			}
			else if (it->index() == 2) // gamepad button
			{
				if (this->type == Action::KeyPressed)
					this->pressed = x->isPressed(0, std::get<Xbox_one_::Button>(*it));
				else if (this->type == Action::onPress)
					this->pressed = x->onPressed(0, std::get<Xbox_one_::Button>(*it));
				else if (this->type == Action::onRelease)
					this->pressed = x->OnRelease(0, std::get<Xbox_one_::Button>(*it));
			}
			else if (it->index() == 3) // gamepad trigger
			{
				if (this->type == Action::KeyPressed)
					this->pressed = x->isPressed(0, std::get<Xbox_one_::Trigger>(*it));
				else if (this->type == Action::onPress)
					this->pressed = x->onPressed(0, std::get<Xbox_one_::Trigger>(*it));
				else if (this->type == Action::onRelease)
					this->pressed = x->OnRelease(0, std::get<Xbox_one_::Trigger>(*it));
			}
			else if (it->index() == 4) // gamepad axis
			{
				if (this->type == Action::KeyPressed)
					this->pressed = x->isPressed(0, std::get<Xbox_one_::Axis>(*it));
				else if (this->type == Action::onPress)
					this->pressed = x->onPressed(0, std::get<Xbox_one_::Axis>(*it));
				else if (this->type == Action::onRelease)
					this->pressed = x->OnRelease(0, std::get<Xbox_one_::Axis>(*it));
			}
		}
	}
}


void Input::update()
{
	if (this->pressed)
	{
		func();

		if (this->type == Action::onPress || this->type == Action::onRelease)
			this->pressed = false;
	}
}

void InputManager::eventUpdate()
{
	for (auto it = InputList.begin(); it != InputList.end(); it++)
	{
		if (it->second.second == true)
			it->second.first.eventUpdate();
	}
}

void InputManager::update()
{
	x.GamePadUpdate();
	c.Update();

	this->eventUpdate();

	for (auto it = InputList.begin(); it != InputList.end(); it++)
	{
		if (it->second.second == true)
			it->second.first.update();
	}
}

void InputManager::bind(std::string name)
{
	auto element = InputList.find(name);
	if (element != InputList.end())
	{
		element->second.second = true;
	}
}

void InputManager::unbind(std::string name)
{
	auto element = InputList.find(name);
	if (element != InputList.end())
	{
		element->second.second = false;
	}
}