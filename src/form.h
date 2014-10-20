#ifndef _AGL_FORM_H
#define _AGL_FORM_H

#include <vector>
#include "formcomponent.h"

namespace AGL
{
	class Form
	{
		private:
			Mouse *mouse;
			Keyboard *keyboard;
			Joystick *joystick;
			vector<FormComponent*> components;
			Drawer *drawer;
			short currentIndex;
			Uint16 prevKey, nextKey;
			bool wrap;
			
			void initialize(Mouse *m, Keyboard *k, Joystick *j, Drawer *d, Uint16 prevKey, Uint16 nextKey, bool wrap);
	
		public:
			Form(Mouse *m, Keyboard *k, Joystick *j, Drawer *d);
			Form(Mouse *m, Keyboard *k, Joystick *j, Drawer *d, bool wrap);
			Form(Mouse *m, Keyboard *k, Joystick *j, Drawer *d, Uint16 prevKey, Uint16 nextKey);
			Form(Mouse *m, Keyboard *k, Joystick *j, Drawer *d, Uint16 prevKey, Uint16 nextKey, bool wrap);
			
			void setKeys(Uint16 prevKey, Uint16 nextKey);
			void addComponent(FormComponent *comp);
			void removeComponent(FormComponent *comp);
			void removeComponent(short index);
			FormComponent *component(short index);
			void setFocus(FormComponent *comp);
			void setFocus(short index);
			void focusPrev();
			void focusNext();
			void setEnabled(short index, bool enabled);
			void update();
			void draw();
	};
}

#endif

