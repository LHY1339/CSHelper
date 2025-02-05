#pragma once
#include <string>
#include <easyx.h>

#include "Struct.h"

class CImage
{
public:
	FRect Rect;

public:
	void Init(std::string Path);
	void Render();

private:
	IMAGE __img;
};

