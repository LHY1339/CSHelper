#pragma once
#include <easyx.h>

#include "Struct.h"

class CCanvas
{
public:
	FRect Rect;

	COLORREF FillColor = RGB(40, 40, 40);
	COLORREF LineColor = RGB(200, 200, 200);

	int LineThick = 1;
public:
	void Render();
};

