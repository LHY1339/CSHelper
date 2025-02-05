#include "Image.h"

void CImage::Init(std::string Path)
{
	loadimage(&__img, Path.c_str(), Rect.W1, Rect.H1);
}

void CImage::Render()
{
	putimage(Rect.X1, Rect.Y1, &__img);
}
