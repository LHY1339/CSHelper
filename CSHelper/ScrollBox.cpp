#include "ScrollBox.h"
#include <iostream>

void CScrollBox::Render()
{
	if (LineThick <= 0)
	{
		setlinestyle(PS_NULL);
	}
	else
	{
		setlinestyle(PS_SOLID);
		setlinecolor(LineColor);
	}

	for (int i = 0; i < ShowIndex; i++)
	{
		if (ArrayText.size() > StartIndex + i)
		{
			std::string curText = ArrayText[StartIndex + i];
			if (curText == FocusText)
			{
				setfillcolor(HoverColor);
			}
			else
			{
				setfillcolor(NormalColor);
			}
			fillroundrect(Rect.X1, Rect.Y1 + Rect.H1 * i, Rect.X1 + Rect.W1, Rect.Y1 + Rect.H1 * (i + 1), Rect.Round, Rect.Round);
			if (curText != "")
			{
				settextcolor(TextColor);
				settextstyle(TextSize, 0, "¼«Ó°»ÙÆ¬Ó«Ô²");
				int TextX = (Rect.X1 + Rect.W1 / 2) - (textwidth(curText.c_str()) / 2);
				int TextY = (Rect.Y1 + Rect.H1 * i + Rect.H1 / 2) - (textheight(curText.c_str()) / 2);
				outtextxy(TextX, TextY, curText.c_str());
			}
		}
	}
}

void CScrollBox::Logic(ExMessage* msg)
{
	if (
		msg->x > Rect.X1 &&
		msg->x < Rect.X1 + Rect.W1 &&
		msg->y>Rect.Y1 &&
		msg->y < Rect.Y1 + Rect.H1 * ShowIndex
		)
	{
		if (msg->wheel != 0)
		{
			if (msg->wheel != 0)
			{
				if (msg->wheel > 0)
				{
					if (StartIndex - 1 > 0)
					{
						StartIndex -= 1;
						msg->wheel = 0;
					}
				}
				else
				{
					if (ArrayText.size() > StartIndex + ShowIndex)
					{
						StartIndex -= -1;
						msg->wheel = 0;
					}
				}

			}
		}
		float height = Rect.H1 * ShowIndex;
		float delta = msg->y - Rect.Y1;
		float perc = delta / height;
		std::cout << perc << std::endl;
		int focbtn = ShowIndex * perc;
		if (ArrayText.size() > StartIndex + focbtn)
		{
			FocusText = ArrayText[StartIndex + focbtn];
			if (msg->lbutton)
			{
				if (!__Click)
				{
					__Click = true;
					State = EScrollBoxState::ScrollClick;
					return;
				}
				State = EScrollBoxState::ScrollPress;
				return;
			}
			__Click = false;
			State = EScrollBoxState::ScrollHover;
			return;
		}
		__Click = false;
		State = EScrollBoxState::ScrollHover;
		FocusText = "";
		return;
	}
	__Click = false;
	State = EScrollBoxState::ScrollNormal;
	FocusText = "";
	return;
}
