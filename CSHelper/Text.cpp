#include "Text.h"

void CText::Render()
{
	settextcolor(TextColor);
	settextstyle(TextSize, 0, "��Ӱ��ƬӫԲ");
	RECT prect = { Rect.X1, Rect.Y1, Rect.X1 + Rect.W1, Rect.Y1 + Rect.H1 };
	drawtext(Text.c_str(), &prect, DT_WORDBREAK);
}
