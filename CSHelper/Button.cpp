#include "Button.h"

void CButton::Render()
{
	switch (State)
	{
	case Normal:
		__CurColor = NormalColor;
		break;
	case Hover:
		__CurColor = HoverColor;
		break;
	case Press:
		__CurColor = PressColor;
		break;
	case Click:
		__CurColor = PressColor;
		break;
	}
	setfillcolor(__CurColor);
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

	if (Text != "")
	{
		settextcolor(TextColor);
		settextstyle(TextSize, 0, "¼«Ó°»ÙÆ¬Ó«Ô²");
		int TextX = (Rect.X1 + Rect.W1 / 2) - (textwidth(Text.c_str()) / 2);
		int TextY = (Rect.Y1 + Rect.H1 / 2) - (textheight(Text.c_str()) / 2);
		outtextxy(TextX, TextY, Text.c_str());
	}
}

void CButton::Logic(ExMessage* msg)
{
	if (
		msg->x > Rect.X1 &&
		msg->x < Rect.X1 + Rect.W1 &&
		msg->y>Rect.Y1 &&
		msg->y < Rect.Y1 + Rect.H1
		)
	{
		if (msg->lbutton || msg->rbutton)
		{
			if (!__Click)
			{
				State = EButtonState::Click;
				__Click = true;
				return;
			}
			State = EButtonState::Press;
			return;
		}
		State = EButtonState::Hover;
		__Click = false;
		return;
	}
	State = EButtonState::Normal;
	__Click = false;
	return;
}

void CButton::SetNormal()
{
	NormalColor = RGB(40, 40, 40);
	HoverColor = RGB(50, 50, 50);
	PressColor = RGB(60, 60, 60);
}

void CButton::SetChose(COLORREF color)
{
	NormalColor = color;
	HoverColor = color;
	PressColor = color;
}
