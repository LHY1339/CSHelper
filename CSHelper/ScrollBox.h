#pragma once
#include <easyx.h>
#include <string>
#include <vector>

#include "Struct.h"

enum EScrollBoxState
{
	ScrollNormal,
	ScrollHover,
	ScrollPress,
	ScrollClick,
};

class CScrollBox
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
	int ShowIndex = 5;
	int StartIndex = 0;

	std::string FocusText = "";
	std::vector<std::string> ArrayText = { "Button1","Button2" ,"Button3","Button4","Button5" ,"Button6" ,"Button7" ,"Button8" };

	EScrollBoxState State;

public:
	void Render();
	void Logic(ExMessage* msg);

private:
	bool __Click = false;
	COLORREF __CurColor = NormalColor;
};

