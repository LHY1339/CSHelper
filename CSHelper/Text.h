#pragma once
#include <easyx.h>
#include <string>

#include "Struct.h"

class CText
{
public:
	FRect Rect;

	COLORREF TextColor = RGB(200, 200, 200);
	int TextSize = 20;
	std::string Text = "Button";
public:
	void Render();
};

