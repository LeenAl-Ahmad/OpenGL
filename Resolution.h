#ifndef RESOLUTION_H
#define RESOLUTION_H

struct Resolution
{
	int width = 1280;
	int height = 768;
	float FoV = 45.0f;

	Resolution(int _width, int _height, float foV)
	{
		width = _width;
		height = _height;
		FoV = foV;
	}
};

#endif // !RESOLUTION_H

