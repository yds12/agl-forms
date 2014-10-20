#ifndef _AGL_BUTTON_H
#define _AGL_BUTTON_H

#include "formcomponent.h"
#include "agl/animation.h"

namespace AGL
{
	class Button : public FormComponent
	{
		private:
			Animation *image;
			Image **texts;
			IntVector2 *textPos;
			Color *textColors;
			bool over, mouseHeldInside;
			Uint16 actionKey;
			
			void initialize(string text, bool centerText, IntVector2 *textPos, Color *textColors, Font *font, ImageFont *ifont, Uint16 actionKey);
			void initialize(wstring wtext, bool centerText, IntVector2 *textPos, Color *textColors, Font *font, ImageFont *ifont, Uint16 actionKey);
			void createImage(Drawer *d);
		
		public:
			bool down, clicked;
			
			Button(IntVector2 *pos, Rectangle area, Font *font, string text, Drawer *d);
			Button(IntVector2 *pos, Rectangle area, ImageFont *ifont, string text, bool centerText, Drawer *d);
			Button(IntVector2 *pos, Rectangle area, ImageFont *ifont, wstring wtext, bool centerText, Drawer *d);
			Button(IntVector2 *pos, Rectangle area, Font *font, string text, IntVector2 *textPos, Color *textColors, 
				Uint16 actionKey, Drawer *d);
			Button(IntVector2 *pos, Rectangle area, ImageFont *ifont, string text, bool centerText, IntVector2 *textPos, Color *textColors, 
				Uint16 actionKey, Drawer *d);
			Button(IntVector2 *pos, Rectangle area, ImageFont *ifont, wstring wtext, bool centerText, IntVector2 *textPos, Color *textColors, 
				Uint16 actionKey, Drawer *d);
			Button(IntVector2 *pos, Rectangle area, Uint16 actionKey, Image *img, short cols, short lines, Drawer *d);
			Button(IntVector2 *pos, Rectangle area, Font *font, string text, IntVector2 *textPos, Color *textColors, 
				Uint16 actionKey, Image *img, short cols, short lines, Drawer *d);
			Button(IntVector2 *pos, Rectangle area, ImageFont *ifont, string text, bool centerText, IntVector2 *textPos, Color *textColors, 
				Uint16 actionKey, Image *img, short cols, short lines, Drawer *d);
			Button(IntVector2 *pos, Rectangle area, ImageFont *ifont, wstring wtext, bool centerText, IntVector2 *textPos, Color *textColors, 
				Uint16 actionKey, Image *img, short cols, short lines, Drawer *d);
			void setFocused(bool focused);
			void setEnabled(bool enabled);
			void update();
			void draw();
	};
}

#endif

