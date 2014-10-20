#ifndef _AGL_TEXTFIELD_H
#define _AGL_TEXTFIELD_H

#include "formcomponent.h"
#include <vector>
#include <cmath>

namespace AGL
{
	class TextField : public FormComponent
	{
		private:
			Color selectionColor, textColor;
			float textScale;
			IntVector2 *textPosition, *cursorPosition;
			Image *image, *cursor, *textImg, *selection;
			string chars;
			Uint16 keys[45];
			vector<short> charNodes;
			bool cursorVisible;
			short currentNode, anchorNode1, anchorNode2, maxLength, textHeight, cursorTimer;
			
			void setNodeByMouse();
			void insertChar(char ch);
			void removeChar(bool back);
			void removeInterval();
			void changeCursorPosition();
			Uint16 key(short index);
			void redrawText();
		
		public:
			TextField(IntVector2 *position, Rectangle area, ImageFont *ifont);
			TextField(IntVector2 *position, Rectangle area, Image *image, IntVector2 *cursorPosition, Image *cursor, Color selectionColor, 
				IntVector2 *textPosition, short maxLength, ImageFont *ifont, float textScale, Color textColor);
			
			void setText(string text);
			string getSelectedText();
			void selectAll();
			void deselectAll();
			
			void setFocused(bool focused);
			void setEnabled(bool enabled);
			void update();
			void draw();
	};
}

#endif

