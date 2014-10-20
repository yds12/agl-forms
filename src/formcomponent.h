#ifndef _AGL_FORMCOMPONENT_H
#define _AGL_FORMCOMPONENT_H

#include "agl/mouse.h"
#include "agl/keyboard.h"
#include "agl/joystick.h"
#include "agl/drawer.h"
#include "agl/text/imagefont.h"
#include "agl/format.h"
#include "agl/graphics/graphics.h"
#include "agl/color.h"

namespace AGL
{
	class FormComponent
	{
		protected:
			Mouse *mouse;
			Keyboard *keyboard;
			Joystick *joystick;
			Drawer *drawer;
			IntVector2 *position;
			Rectangle area;
			Font *font;
			ImageFont *ifont;
			bool focused, enabled;
			string text;
			wstring wtext;
			
		public:			
			FormComponent(IntVector2 *position, Rectangle area);
		
			void setInput(Mouse *m, Keyboard *k, Joystick *j);
			void setDrawer(Drawer *d);
			string getText();
			wstring getWideText();	
			bool isFocused();
			bool isEnabled();
			virtual void setFocused(bool focused) = 0;
			virtual void setEnabled(bool enabled) = 0;
			virtual void update() = 0;
			virtual void draw() = 0;
	};
}

#endif

