#include "button.h"
#include <iostream>

using namespace AGL;
using namespace std;

void Button::initialize(string text, bool centerText, IntVector2 *textPos, Color *textColors, Font *font, ImageFont *ifont, Uint16 actionKey)
{
	this->text = text;
	this->textPos = new IntVector2(*position + *textPos);
	this->font = font;
	this->ifont = ifont;
	if (ifont)
	{
		Graphics g;
		texts = new Image*[6];
		if (centerText)
			for (short i = 0; i < 6; i++)
				texts[i] = ifont->writeCenteredLine(text, area.width);
		else 
			for (short i = 0; i < 6; i++)
				texts[i] = ifont->writeLine(text);
		for (short i = 0; i < 6; i++)
			g.applyColorFilter(texts[i], textColors[i]);
	}
	this->textColors = textColors;
	this->actionKey = actionKey;
	over = false;
	mouseHeldInside = false;
	down = false;
	clicked = false;
}
void Button::initialize(wstring wtext, bool centerText, IntVector2 *textPos, Color *textColors, Font *font, ImageFont *ifont, Uint16 actionKey)
{
	this->wtext = wtext;
	this->textPos = new IntVector2(*position + *textPos);
	this->font = font;
	this->ifont = ifont;
	if (ifont)
	{
		Graphics g;
		texts = new Image*[6];
		if (centerText)
			for (short i = 0; i < 6; i++)
				texts[i] = ifont->writeCenteredLine(wtext, area.width);
		else 
			for (short i = 0; i < 6; i++)
				texts[i] = ifont->writeLine(wtext);
		for (short i = 0; i < 6; i++)
			g.applyColorFilter(texts[i], textColors[i]);
	}
	this->textColors = textColors;
	this->actionKey = actionKey;
	over = false;
	mouseHeldInside = false;
	down = false;
	clicked = false;
}
void Button::createImage(Drawer *d)
{
	Graphics g;
	IntVector2 v(0, area.height);
	Image *rect1 = g.getRectangle(area.width, area.height, AGL_COLOR_WHITE),
		*rect2 = g.getCompleteRectangle(area.width, area.height, AGL_COLOR_WHITE, AGL_COLOR_BLACK, 255),
		*rect3 = g.getRectangle(area.width, area.height, AGL_COLOR_DARKGRAY),
		*rect4 = g.getCompleteRectangle(area.width, area.height, AGL_COLOR_DARKGRAY, AGL_COLOR_BLACK, 255),
		*rect5 = g.getCompleteRectangle(area.width, area.height, AGL_COLOR_GRAY, AGL_COLOR_BLACK, 255),
		*result = g.overlapImages(rect1, rect2, v); v.y += area.height;
	result = g.overlapImages(result, rect3, v); v.y += area.height;
	result = g.overlapImages(result, rect4, v); v.y += area.height;
	result = g.overlapImages(result, rect5, v); v.y += area.height;
	result = g.overlapImages(result, rect1, v);
	image = new Animation(result, d, 1, 6);
}

Button::Button(IntVector2 *position, Rectangle area, Font *font, string text, Drawer *d) : FormComponent(position, area)
{
	Color *colors = new Color[6];
	colors[0] = colors[1] = colors[2] = colors[3] = colors[4] = AGL_COLOR_BLACK; colors[5] = AGL_COLOR_GRAY;
	initialize(text, false, new IntVector2(0, 0), colors, font, NULL, KEY_ENTER);
	createImage(d);
}
Button::Button(IntVector2 *position, Rectangle area, ImageFont *ifont, string text, bool centerText, Drawer *d) : FormComponent(position, area)
{
	IntVector2 v(0, 0);
	Color *colors = new Color[6];
	colors[0] = colors[1] = colors[2] = colors[3] = colors[4] = AGL_COLOR_BLACK; colors[5] = AGL_COLOR_GRAY;
	initialize(text, centerText, new IntVector2(0, 0), colors, NULL, ifont, KEY_ENTER);
	createImage(d);
}
Button::Button(IntVector2 *position, Rectangle area, ImageFont *ifont, wstring wtext, bool centerText, Drawer *d) : FormComponent(position, area)
{
	IntVector2 v(0, 0);
	Color *colors = new Color[6];
	colors[0] = colors[1] = colors[2] = colors[3] = colors[4] = AGL_COLOR_BLACK; colors[5] = AGL_COLOR_GRAY;
	initialize(wtext, centerText, new IntVector2(0, 0), colors, NULL, ifont, KEY_ENTER);
	createImage(d);
}
Button::Button(IntVector2 *position, Rectangle area, Font *font, string text, IntVector2 *textPos, Color *textColors, 
	Uint16 actionKey, Drawer *d) : FormComponent(position, area)
{
	initialize(text, false, textPos, textColors, font, NULL, actionKey);
	createImage(d);
}
Button::Button(IntVector2 *position, Rectangle area, ImageFont *ifont, string text, bool centerText, IntVector2 *textPos, Color *textColors, 
	Uint16 actionKey, Drawer *d) : FormComponent(position, area)
{
	initialize(text, centerText, textPos, textColors, NULL, ifont, actionKey);
	createImage(d);
}
Button::Button(IntVector2 *position, Rectangle area, ImageFont *ifont, wstring wtext, bool centerText, IntVector2 *textPos, Color *textColors, 
	Uint16 actionKey, Drawer *d) : FormComponent(position, area)
{
	initialize(wtext, centerText, textPos, textColors, NULL, ifont, actionKey);
	createImage(d);
}
Button::Button(IntVector2 *position, Rectangle area, Uint16 actionKey, Image *img, short cols, short lines, Drawer *d) 
	: FormComponent(position, area)
{
	initialize("", false, new IntVector2(0, 0), NULL, NULL, NULL, actionKey);
	image = new Animation(img, d, cols, lines);
}
Button::Button(IntVector2 *position, Rectangle area, Font *font, string text, IntVector2 *textPos, Color *textColors, 
	Uint16 actionKey, Image *img, short cols, short lines, Drawer *d) : FormComponent(position, area)
{
	initialize(text, false, textPos, textColors, font, NULL, actionKey);
	image = new Animation(img, d, cols, lines);
}
Button::Button(IntVector2 *position, Rectangle area, ImageFont *ifont, string text, bool centerText, IntVector2 *textPos, Color *textColors, 
	Uint16 actionKey, Image *img, short cols, short lines, Drawer *d) : FormComponent(position, area)
{
	initialize(text, centerText, textPos, textColors, NULL, ifont, actionKey);
	image = new Animation(img, d, cols, lines);
}
Button::Button(IntVector2 *position, Rectangle area, ImageFont *ifont, wstring wtext, bool centerText, IntVector2 *textPos, Color *textColors, 
	Uint16 actionKey, Image *img, short cols, short lines, Drawer *d) : FormComponent(position, area)
{
	initialize(wtext, centerText, textPos, textColors, NULL, ifont, actionKey);
	image = new Animation(img, d, cols, lines);
}

void Button::setFocused(bool focused)
{
	this->focused = focused;
	image->index = focused ? (over ? 3 : 1) : (over ? 2 : 0);
}

void Button::setEnabled(bool enabled)
{
	this->enabled = enabled;
	image->index = enabled ? (over ? 2 : 0) : 5;
}
		
void Button::update()
{
	if (enabled)
	{
		if (clicked) clicked = false;
		if (mouse->isCursorOver(area))
		{
			if (!over)
			{
				if (mouse->isLeftButtonHeld() && mouseHeldInside)
				{
					down = true;
					mouseHeldInside = false;
					image->index = 4;
				}
				else image->index = focused ? 3 : 2;
				over = true;
			}
		}
		else if (over)
		{
			down = false;
			if (mouse->isLeftButtonHeld()) mouseHeldInside = true;
			over = false;
			image->index = focused ? 1 : 0;
		}
		if (mouse->isLeftButtonPressed())
		{
			if (over)
			{
				down = true;
				image->index = 4;
			}
		}
		else if (mouse->isLeftButtonReleased())
		{
			mouseHeldInside = false;
			if (down)
			{
				clicked = true;
				image->index = focused ? 3 : 2;
			}
			down = false;
		}
	}
	if (focused)
	{
		if (keyboard->isKeyPressed(keyboard->getIndex(actionKey)))
		{
			image->index = 4;
			clicked = true;
		}
	}
}

void Button::draw()
{
	image->draw(*position);
	if (font)
		drawer->drawText(font, Format::stringToChar(&text), *textPos, textColors[image->index]);
	else if (ifont)
		drawer->draw(texts[image->index], *textPos);
}

