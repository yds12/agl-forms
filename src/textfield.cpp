#include "textfield.h"

using namespace AGL;

void TextField::setText(string text) 
{
	if (text.length() <= maxLength)
	{
		this->text = text;
		while (charNodes.size() > 1) charNodes.erase(charNodes.begin() + 1);
		for (short i = 0; i < text.length(); i++)
		{
			short lastNode = charNodes[charNodes.size() - 1];
			charNodes.push_back(lastNode + (short)(textScale * (ifont->getCharWidth(text[i]) + ifont->charSpacing) + 0.5f));
		}
		currentNode = charNodes.size() - 1;
		anchorNode1 = -1;
		anchorNode2 = -1;
		changeCursorPosition();
	}
	redrawText();
}

string TextField::getSelectedText()
{
	if (anchorNode2 == -1) return "";
	short minorNode = anchorNode1 < anchorNode2 ? anchorNode1 : anchorNode2,
	majorNode = minorNode == anchorNode1 ? anchorNode2 : anchorNode1;
	return text.substr(minorNode, majorNode - minorNode);
}

TextField::TextField(IntVector2 *position, Rectangle area, ImageFont *ifont) : FormComponent(position, area)
{
	Graphics g;
	this->image = g.getCompleteRectangle(area.width, area.height, AGL_COLOR_WHITE, AGL_COLOR_BLACK, 255);
	this->cursorPosition = new IntVector2(position->x + 1, position->y + 1);
	this->cursor = g.getVerticalLine(area.height-2, AGL_COLOR_BLACK);
	this->text = "";
	this->selectionColor = AGL_COLOR_BLACK;
	this->textPosition = new IntVector2(*cursorPosition);
	this->maxLength = 100;
	
	this->keys[0] = KEY_A;
	this->keys[1] = KEY_B;
	this->keys[2] = KEY_C;
	this->keys[3] = KEY_D;
	this->keys[4] = KEY_E;
	this->keys[5] = KEY_F;
	this->keys[6] = KEY_G;
	this->keys[7] = KEY_H;
	this->keys[8] = KEY_I;
	this->keys[9] = KEY_J;
	this->keys[10] = KEY_K;
	this->keys[11] = KEY_L;
	this->keys[12] = KEY_M;
	this->keys[13] = KEY_N;
	this->keys[14] = KEY_O;
	this->keys[15] = KEY_P;
	this->keys[16] = KEY_Q;
	this->keys[17] = KEY_R;
	this->keys[18] = KEY_S;
	this->keys[19] = KEY_T;
	this->keys[20] = KEY_U;
	this->keys[21] = KEY_V;
	this->keys[22] = KEY_W;
	this->keys[23] = KEY_X;
	this->keys[24] = KEY_Y;
	this->keys[25] = KEY_Z;
	this->keys[26] = KEY_0;
	this->keys[27] = KEY_1;
	this->keys[28] = KEY_2;
	this->keys[29] = KEY_3;
	this->keys[30] = KEY_4;
	this->keys[31] = KEY_5;
	this->keys[32] = KEY_6;
	this->keys[33] = KEY_7;
	this->keys[34] = KEY_8;
	this->keys[35] = KEY_9;
	this->keys[36] = KEY_SPACE;
	this->keys[37] = KEY_BACKSPACE;
	this->keys[38] = KEY_DELETE;
	this->keys[39] = KEY_LEFT;
	this->keys[40] = KEY_RIGHT;
	this->keys[41] = KEY_HOME;
	this->keys[42] = KEY_END;
	this->keys[43] = KEY_LEFTSHIFT;
	this->keys[44] = KEY_RIGHTSHIFT;
	
	charNodes.push_back(cursorPosition->x);
	this->currentNode = 0;
	this->anchorNode1 = -1;
	this->anchorNode2 = -1;
	this->ifont = ifont;
	this->textScale = 1;
	this->textColor = AGL_COLOR_BLACK;
	this->textHeight = (short)(textScale * ifont->charHeight + 0.5f);
	this->textImg = NULL;
	this->selection = NULL;
	this->chars = "abcdefghijklmnopqrstuvwxyz0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	this->cursorTimer = 0;
	this->cursorVisible = true;
}

TextField::TextField(IntVector2 *position, Rectangle area, Image *image, IntVector2 *cursorPosition, Image *cursor, Color selectionColor, 
	IntVector2 *textPosition, short maxLength, ImageFont *ifont, float textScale, Color textColor) : FormComponent(position, area)
{
	this->image = image;
	this->cursorPosition = new IntVector2(*position + *cursorPosition);
	this->cursor = cursor;
	this->text = "";
	this->selectionColor = selectionColor;
	this->textPosition = new IntVector2(*position + *textPosition);
	this->maxLength = maxLength;
	
	this->keys[0] = KEY_A;
	this->keys[1] = KEY_B;
	this->keys[2] = KEY_C;
	this->keys[3] = KEY_D;
	this->keys[4] = KEY_E;
	this->keys[5] = KEY_F;
	this->keys[6] = KEY_G;
	this->keys[7] = KEY_H;
	this->keys[8] = KEY_I;
	this->keys[9] = KEY_J;
	this->keys[10] = KEY_K;
	this->keys[11] = KEY_L;
	this->keys[12] = KEY_M;
	this->keys[13] = KEY_N;
	this->keys[14] = KEY_O;
	this->keys[15] = KEY_P;
	this->keys[16] = KEY_Q;
	this->keys[17] = KEY_R;
	this->keys[18] = KEY_S;
	this->keys[19] = KEY_T;
	this->keys[20] = KEY_U;
	this->keys[21] = KEY_V;
	this->keys[22] = KEY_W;
	this->keys[23] = KEY_X;
	this->keys[24] = KEY_Y;
	this->keys[25] = KEY_Z;
	this->keys[26] = KEY_0;
	this->keys[27] = KEY_1;
	this->keys[28] = KEY_2;
	this->keys[29] = KEY_3;
	this->keys[30] = KEY_4;
	this->keys[31] = KEY_5;
	this->keys[32] = KEY_6;
	this->keys[33] = KEY_7;
	this->keys[34] = KEY_8;
	this->keys[35] = KEY_9;
	this->keys[36] = KEY_SPACE;
	this->keys[37] = KEY_BACKSPACE;
	this->keys[38] = KEY_DELETE;
	this->keys[39] = KEY_LEFT;
	this->keys[40] = KEY_RIGHT;
	this->keys[41] = KEY_HOME;
	this->keys[42] = KEY_END;
	this->keys[43] = KEY_LEFTSHIFT;
	this->keys[44] = KEY_RIGHTSHIFT;
	
	charNodes.push_back(this->cursorPosition->x);
	this->currentNode = 0;
	this->anchorNode1 = -1;
	this->anchorNode2 = -1;
	this->ifont = ifont;
	this->textScale = textScale;
	this->textColor = textColor;
	this->textHeight = (short)(textScale * ifont->charHeight + 0.5f);
	this->textImg = NULL;
	this->selection = NULL;
	this->chars = "abcdefghijklmnopqrstuvwxyz0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	this->cursorTimer = 0;
	this->cursorVisible = true;
}

void TextField::setFocused(bool focused)
{
	this->focused = focused;
	cursorVisible = focused;
	cursorTimer = 0;
}
void TextField::setEnabled(bool enabled)
{
	this->enabled = enabled;
}
void TextField::update()
{
	if (enabled)
	{
		// Mouse
		if (mouse->isCursorOver(area))
		{
			if (mouse->isLeftButtonDoubleClicked())
			{
				anchorNode1 = 0;
				anchorNode2 = charNodes.size() - 1;
				currentNode = anchorNode2;
				changeCursorPosition();
			}
			else if (mouse->isLeftButtonPressed())
			{
				if (!focused) { setFocused(true); return; }
				setNodeByMouse();
				changeCursorPosition();
				anchorNode1 = currentNode;
				anchorNode2 = -1;
			}
		}
		if (mouse->isLeftButtonHeld())
		{
			if (anchorNode1 != -1)
			{
				setNodeByMouse();
				changeCursorPosition();
				if (currentNode != anchorNode1) anchorNode2 = currentNode;
				else anchorNode2 = -1;
			}
		}
		else if (mouse->isLeftButtonReleased())
		{
			if (anchorNode1 != -1)
			{
				if (currentNode != anchorNode1) anchorNode2 = currentNode;
				else anchorNode1 = -1;
			}
		}
		if (focused)
		{
			// Keyboard
			if (keyboard->isKeyPressed(key(43)) || keyboard->isKeyPressed(key(44))) //Shift
				if (anchorNode1 == -1) anchorNode1 = currentNode;
			bool digit = false;
			for (short i = 0; i < 37; i++) //Digits
				if (keyboard->isKeyPressed(key(i)) || keyboard->isKeyHeld(key(i)))
				{
					if (anchorNode1 != -1 && anchorNode2 != -1)
						removeInterval();
					if (i < 26) //Letters
					{
						if (keyboard->isKeyDown(key(43)) || keyboard->isKeyDown(key(44)))
							insertChar(chars[i + 37]);
						else insertChar(chars[i]);
					}
					else //Numbers and space
						insertChar(chars[i]);
					digit = true;
				}
			if (!digit)
			{
				if (keyboard->isKeyPressed(key(37)) || keyboard->isKeyHeld(key(37))) //Backspace
				{
					if (anchorNode1 != -1 && anchorNode2 != -1)
						removeInterval();
					else if (currentNode > 0)
						removeChar(true);
				}
				else if (keyboard->isKeyPressed(key(38)) || keyboard->isKeyHeld(key(38))) //Delete
				{
					if (anchorNode1 != -1 && anchorNode2 != -1)
						removeInterval();
					else if (currentNode < charNodes.size() - 1)
						removeChar(false);
				}
				else if (keyboard->isKeyPressed(key(39)) || keyboard->isKeyHeld(key(39))) //Left
				{                
					if (anchorNode1 != -1)
					{
						if (keyboard->isKeyDown(key(43)) || keyboard->isKeyDown(key(44)))
						{
							if (currentNode > 0)
							{
								currentNode--;
								anchorNode2 = currentNode;
								changeCursorPosition();
							}
						}
						else if (anchorNode2 != -1)
						{
							currentNode = anchorNode1 < anchorNode2 ? anchorNode1 : anchorNode2;
							anchorNode1 = -1;
							anchorNode2 = -1;
							changeCursorPosition();
						}
					}
					else if (currentNode > 0)
					{
						currentNode--;
						changeCursorPosition();
					}
				}
				else if (keyboard->isKeyPressed(key(40)) || keyboard->isKeyHeld(key(40))) //Right
				{
					if (anchorNode1 != -1)
					{
						if (keyboard->isKeyDown(key(43)) || keyboard->isKeyDown(key(44)))
						{
							if (currentNode < charNodes.size() - 1)
							{
								currentNode++;
								anchorNode2 = currentNode;
								changeCursorPosition();
							}
						}
						else if (anchorNode2 != -1)
						{
							currentNode = anchorNode1 > anchorNode2 ? anchorNode1 : anchorNode2;
							anchorNode1 = -1;
							anchorNode2 = -1;
							changeCursorPosition();
						}
					}
					else if (currentNode < charNodes.size() - 1)
					{
						currentNode++;
						changeCursorPosition();
					}
				}
				else if (keyboard->isKeyPressed(key(41))) //Home
				{
					currentNode = 0;
					if (keyboard->isKeyDown(key(43)) || keyboard->isKeyDown(key(44)))
						anchorNode2 = currentNode;
					else
					{
						anchorNode1 = -1;
						anchorNode2 = -1;
					}
					changeCursorPosition();
				}
				else if (keyboard->isKeyPressed(key(42))) //End
				{
					currentNode = charNodes.size() - 1;
					if (keyboard->isKeyDown(key(43)) || keyboard->isKeyDown(key(44)))
						anchorNode2 = currentNode;
					else
					{
						anchorNode1 = -1;
						anchorNode2 = -1;
					}
					changeCursorPosition();
				}
			}
			cursorTimer++;
			if (cursorTimer >= 30)
			{
				cursorVisible = !cursorVisible;
				cursorTimer = 0;
			}
		}
	}
}

void TextField::draw()
{
	drawer->draw(image, *position);
	if (cursorVisible) drawer->draw(cursor, *cursorPosition);	
	if (text.length() > 0) drawer->draw(textImg, *textPosition);
	if (anchorNode1 != -1 && anchorNode2 != -1)
	{
		int x = anchorNode1 < anchorNode2 ? charNodes[anchorNode1] : charNodes[anchorNode2],
			width = abs(charNodes[anchorNode1] - charNodes[anchorNode2]);
		Graphics g;
		if (selection != NULL) delete selection;
		selection = g.getRectangle(width, textHeight, selectionColor, 128); 
		IntVector2 v(x, textPosition->y);
		drawer->draw(selection, v); 
	}
}

void TextField::setNodeByMouse()
{
	short nodeIndex = -1;
	for (short i = 0; i < charNodes.size(); i++)
	{
		if (charNodes[i] >= mouse->position->x)
		{
			nodeIndex = i;
			break;
		}
	}
	if (nodeIndex == -1) currentNode = charNodes.size() - 1;
	else if (nodeIndex == 0) currentNode = 0;
	else
	{
		short d1 = charNodes[nodeIndex] - mouse->position->x, d2 = mouse->position->x - charNodes[nodeIndex - 1];
		if (d1 <= d2) currentNode = nodeIndex;
		else currentNode = nodeIndex - 1;
	}
}

void TextField::insertChar(char ch)
{
	if (text.length() < maxLength)
	{
		text = text.insert(currentNode, 1, ch);
		short charWidth = (short)(textScale * (ifont->getCharWidth(ch) + ifont->charSpacing) + 0.5f);
		charNodes.insert(charNodes.begin() + currentNode + 1, charNodes[currentNode] + charWidth);
		for (short i = currentNode + 2; i < charNodes.size(); i++)
			charNodes[i] += charWidth;
		currentNode++;
		changeCursorPosition();
		redrawText();
	}
	anchorNode1 = -1;
	anchorNode2 = -1;
}

void TextField::removeChar(bool back)
{
	if (back)
	{
		currentNode--;
		changeCursorPosition();
	}
	short charWidth = (short)(textScale * (ifont->getCharWidth(text[currentNode]) + ifont->charSpacing) + 0.5f);
	text = text.erase(currentNode, 1);
	charNodes.erase(charNodes.begin() + currentNode + 1);
	for (short i = currentNode + 1; i < charNodes.size(); i++)
		charNodes[i] -= charWidth;
	redrawText();
	anchorNode1 = -1;
	anchorNode2 = -1;
}

void TextField::removeInterval()
{
	short minorNode = anchorNode1 < anchorNode2 ? anchorNode1 : anchorNode2,
		majorNode = minorNode == anchorNode1 ? anchorNode2 : anchorNode1,
		charCount = majorNode - minorNode;
	short intervalWidth = 0;
	for (short i = minorNode; i < majorNode; i++)
	{
		intervalWidth += (short)(textScale * (ifont->getCharWidth(text[i]) + ifont->charSpacing) + 0.5f);
		charNodes.erase(charNodes.begin() + minorNode + 1);
	}
	text = text.erase(minorNode, charCount);
	for (short i = minorNode + 1; i < charNodes.size(); i++)
		charNodes[i] -= intervalWidth;
	currentNode = minorNode;
	anchorNode1 = -1;
	anchorNode2 = -1;
	changeCursorPosition();
	redrawText();
}

void TextField::changeCursorPosition()
{
	cursorPosition->x = charNodes[currentNode];
	cursorVisible = true;
	cursorTimer = 0;
}

void TextField::selectAll()
{
	anchorNode1 = 0;
	anchorNode2 = charNodes.size() - 1;
}

void TextField::deselectAll()
{
	if (anchorNode2 != -1)
	{
		currentNode = anchorNode2;
		anchorNode2 = -1;
	}
	anchorNode1 = -1;
	changeCursorPosition();
}

Uint16 TextField::key(short index)
{
	return keyboard->getIndex(keys[index]);
}

void TextField::redrawText()
{
	if (textImg != NULL)
	{
		delete textImg;
		textImg = NULL;
	}
	if (text.length() > 0)
	{
		textImg = ifont->writeLine(text);
		Graphics g; g.applyColorFilter(textImg, textColor);
		short width = 0, i;
		for (i = 0; i < text.length() - 1; i++)
			width += (short)(textScale * (ifont->getCharWidth(text[i]) + ifont->charSpacing) + 0.5f);
		width += (short)(textScale * ifont->getCharWidth(text[i]) + 0.5f);
		g.resize(textImg, width, textHeight);
	}
}

