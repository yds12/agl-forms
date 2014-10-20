#include "form.h"

using namespace AGL;

void Form::initialize(Mouse *m, Keyboard *k, Joystick *j, Drawer *d, Uint16 prevKey, Uint16 nextKey, bool wrap)
{
	mouse = m;
	keyboard = k;
	joystick = j;
	drawer = d;
	this->prevKey = keyboard->getIndex(prevKey);
	this->nextKey = keyboard->getIndex(nextKey);
	this->wrap = wrap;
	currentIndex = 0;
}

Form::Form(Mouse *m, Keyboard *k, Joystick *j, Drawer *d)
{
	initialize(m, k, j, d, KEY_UP, KEY_DOWN, true);
}

Form::Form(Mouse *m, Keyboard *k, Joystick *j, Drawer *d, bool wrap)
{
	initialize(m, k, j, d, KEY_UP, KEY_DOWN, wrap);
}

Form::Form(Mouse *m, Keyboard *k, Joystick *j, Drawer *d, Uint16 prevKey, Uint16 nextKey)
{
	initialize(m, k, j, d, prevKey, nextKey, true);
}

Form::Form(Mouse *m, Keyboard *k, Joystick *j, Drawer *d, Uint16 prevKey, Uint16 nextKey, bool wrap)
{
	initialize(m, k, j, d, prevKey, nextKey, wrap);
}

void Form::setKeys(Uint16 prevKey, Uint16 nextKey)
{
	this->prevKey = prevKey;
	this->nextKey = nextKey;
}

void Form::addComponent(FormComponent *comp)
{
	components.push_back(comp);
	comp->setInput(mouse, keyboard, joystick);
	comp->setDrawer(drawer);
	if (components.size() == 1) comp->setFocused(true);
}

void Form::removeComponent(FormComponent *comp)
{
	short size = components.size();
	for (short i = 0; i < size; i++)
		if (components[i] == comp)
		{
			components.erase(components.begin() + i);
			break;
		}
}

void Form::removeComponent(short index)
{
	components.erase(components.begin() + index);
}

FormComponent *Form::component(short index)
{
	return components[index];
}

void Form::setFocus(FormComponent *comp)
{
	comp->setFocused(true);
	short size = components.size();
	for (short i = 0; i < size; i++)
		if (components[i] != comp) currentIndex = i;
		else components[i]->setFocused(false);
}

void Form::setFocus(short index)
{
	components[index]->setFocused(true);
	currentIndex = index;
	short size = components.size();
	for (short i = 0; i < size; i++)
		if (i != index)
			components[i]->setFocused(false);
}

void Form::focusPrev()
{
	bool found = false;
	short size = components.size(), prevIndex = currentIndex;
	for (short i = currentIndex - 1; i != currentIndex; i--)
	{
		if (i == -1)
		{
			if (currentIndex == size - 1) break;
			else if (wrap) i = size - 1;
			else break;
		}
		if (components[i]->isEnabled())
		{
			components[i]->setFocused(true);
			currentIndex = i;
			found = true;
			break;
		}
	}
	if (found) components[prevIndex]->setFocused(false);
}

void Form::focusNext()
{
	bool found = false;
	short size = components.size(), prevIndex = currentIndex;
	for (short i = currentIndex + 1; i != currentIndex; i++)
	{
		if (i == size)
		{
			if (currentIndex == 0) break;
			else if (wrap) i = 0;
			else break;
		}
		if (components[i]->isEnabled())
		{
			components[i]->setFocused(true);
			currentIndex = i;
			found = true;
			break;
		}
	}
	if (found) components[prevIndex]->setFocused(false);
}

void Form::setEnabled(short index, bool enabled)
{
	components[index]->setEnabled(enabled);
}
	
void Form::update()
{
	if (keyboard->isKeyPressed(prevKey) || keyboard->isKeyHeld(prevKey)) focusPrev();
	if (keyboard->isKeyPressed(nextKey) || keyboard->isKeyHeld(nextKey)) focusNext();
	
	short size = components.size();
	for (short i = 0; i < size; i++)
	{
		FormComponent *comp = components[i];
		comp->update();
	}
}

void Form::draw()
{
	short size = components.size();
	for (short i = 0; i < size; i++)
		components[i]->draw();
}

