#pragma once
#include <easyx.h>
#include <string>

#include "Struct.h"

enum EButtonState
{
	Normal,
	Hover,
	Press,
	Click,
};

class CButton
{
public:
	FRect Rect;

	COLORREF NormalColor;
	COLORREF HoverColor;
	COLORREF PressColor;
	COLORREF LineColor = RGB(200, 200, 200);
	COLORREF TextColor = RGB(200, 200, 200);

	int LineThick = 1;
	int TextSize = 20;
	
	std::string Text = "Button";

	EButtonState State;

public:
	void Render();
	void Logic(ExMessage* msg);
	void SetNormal();
	void SetChose(COLORREF color);

private:
	bool __Click = false;
	COLORREF __CurColor = NormalColor;
};

