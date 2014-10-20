#include "formcomponent.h"

using namespace AGL;

FormComponent::FormComponent(IntVector2 *position, Rectangle area)
{
	this->position = position;
	this->area = area;
	focused = false;
	enabled = true;
}

void FormComponent::setInput(Mouse *m, Keyboard *k, Joystick *j)
{
	mouse = m;
	keyboard = k;
	joystick = j;
}

void FormComponent::setDrawer(Drawer *d)
{
	drawer = d;
}

string FormComponent::getText()
{
	return text;
}

wstring FormComponent::getWideText()
{
	return wtext;
}

bool FormComponent::isFocused()
{
	return focused;
}

bool FormComponent::isEnabled()
{
	return enabled;
}

