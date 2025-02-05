#include "Canvas.h"

void CCanvas::Render()
{
	setfillcolor(FillColor);
	if (LineThick <= 0)
	{
		setlinestyle(PS_NULL);
	}
	else
	{
		setlinestyle(PS_SOLID);
		setlinecolor(LineColor);
	}
	fillroundrect(Rect.X1, Rect.Y1, Rect.X1 + Rect.W1, Rect.Y1 + Rect.H1, Rect.Round, Rect.Round);
}
