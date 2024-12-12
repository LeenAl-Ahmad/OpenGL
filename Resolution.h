#ifndef RESOLUTION_H
#define RESOLUTION_H

struct Resolution
{
	int width = 1280;
	int height = 768;
	float FoV = 45.0f;

	Resolution(int _width, int _height)
	{
		width = _width;
		height = _height;
	}
};

#endif // !RESOLUTION_H