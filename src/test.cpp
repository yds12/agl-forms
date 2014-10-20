#include <stdlib.h>
#include "agl/game.h"
#include "agl/drawer.h"

// ------------ Includes here ---------------
#include <iostream>
#include "agl/forms/form.h"
#include "agl/forms/button.h"
#include "agl/forms/textfield.h"
// ------------------------------------------

using namespace AGL;

Game *game;
Drawer *drawer;
Mouse *mouse;
Keyboard *keyboard;
Form *form;
Button *button;
Font *font;
ImageFont *ifont;
ImageFont *ifont2;
short btnIndex;

void initialize()
{
	game = new Game;
	game->showMouse(true);
	drawer = new Drawer;
	mouse = new Mouse(10, 25);
	Uint16 *keys = new Uint16[48] {
		KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R,
		KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_SPACE,
		KEY_BACKSPACE, KEY_DELETE, KEY_LEFT, KEY_RIGHT, KEY_HOME, KEY_END, KEY_LEFTSHIFT, KEY_RIGHTSHIFT, KEY_UP, KEY_DOWN, KEY_ENTER };
	keyboard = new Keyboard(keys, 48);
	form = new Form(mouse, keyboard, NULL, drawer, false);
	btnIndex = -1;
}

void loadContent()
{
	font = new Font("/usr/share/fonts/truetype/fonts-japanese-gothic.ttf", 12);
	Image *img = new Image("/home/USER/aleva/test/font1.png");
	ifont = new ImageFont(img, 2, L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáéíóúàãõâêôüçÁÉÍÓÚÀÃÕÂÊÔÜÇ012345789.,:;!?¿-_()[]{}/\\|*");
	ifont2 = new ImageFont(img, 2, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ--------------------------012345789-------------------");
	Color *c = new Color[6];
	c[0] = AGL_COLOR_BLACK; c[1] = AGL_COLOR_BLACK; c[2] = AGL_COLOR_WHITE; c[3] = AGL_COLOR_WHITE; c[4] = AGL_COLOR_DARKGRAY; c[5] = AGL_COLOR_GRAY;
	cout << "1" << endl;
	form->addComponent(new Button(new IntVector2(10, 10), {10, 10, 100, 20}, font, "¿Ações", drawer));
	form->addComponent(new Button(new IntVector2(10, 50), {10, 50, 140, 32}, ifont, L"¿Ações", true, drawer));
	form->addComponent(new Button(new IntVector2(210, 10), {210, 10, 100, 20}, font, "¿Ações", new IntVector2(3, 3), c, KEY_SPACE, drawer));
	form->addComponent(new Button(new IntVector2(210, 50), {210, 50, 140, 32}, ifont, L"¿Açõ*s", true, new IntVector2(3, 3), c, KEY_SPACE, drawer));
	form->addComponent(new Button(new IntVector2(410, 10), {410, 10, 100, 100}, KEY_SPACE, new Image("/home/USER/aleva/test/btn.png"), 3, 2, drawer));
	form->addComponent(new Button(new IntVector2(410, 120), {410, 120, 100, 100}, font, "¿Ações", new IntVector2(3, 3), c, KEY_SPACE,
		new Image("/home/USER/aleva/test/btn.png"), 3, 2, drawer));
	form->addComponent(new Button(new IntVector2(610, 10), {610, 10, 100, 100}, ifont, L"¿Ações", true, new IntVector2(3, 3), c, KEY_SPACE,
		new Image("/home/USER/aleva/test/btn.png"), 3, 2, drawer));
	form->addComponent(new TextField(new IntVector2(10, 300), {10, 300, 300, 40}, ifont2));
	cout << "2" << endl;
	/*
	button = new Button(new IntVector2(10, 210), {10, 210, 100, 20}, font, "Bigo", drawer);
	button->setInput(mouse, keyboard, NULL);
	button->setDrawer(drawer);
	*/
	//form->setEnabled(2, false);
}

void update()
{
	form->update();
	for (short i = 0; i < 7; i++)
	{
		Button *btn = (Button *)form->component(i);
		if (btn->clicked)
		{
			//btn->reset();
			btnIndex = i;
			break;
		}
	}/*
	button->update();
	if (button->clicked)
	{
		btnIndex = 5;
		shouldClear = true;
	}*/
	game->update(keyboard, mouse);
}

void draw()
{
	drawer->clearScreen(AGL_COLOR_GREEN);
	form->draw();
	//button->draw();
	IntVector2 v(400, 400);
	drawer->drawText(font, Format::stringToChar(&(Format::intToString(btnIndex))), v, AGL_COLOR_BLACK);
	//drawer->drawText(font, "áé ḉ ĸ ?", v, AGL_COLOR_BLACK); v.x += 100;
	//drawer->draw(ifont2->writeLine("Acoes"), v);
	drawer->updateScreen();
}

void unloadContent()
{
	game->end();
	delete game, drawer, mouse, keyboard, form, font;
}

/// Main method, initializes the program
int main(int argc, char *argv[])
{
	initialize();
	loadContent();
	game->runFixedFps(update, draw, 60);
	unloadContent();

	return 0;
}
