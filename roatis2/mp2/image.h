#ifndef IMAGE_H
#define IMAGE_H
#include <cstdint>
#include <iostream>
#include "png.h"
#include "rgbapixel.h"


class Image : public PNG
{
   public:

	void flipleft();
	void adjustbrightness(int r, int g, int b);
	void invertcolors();
};

#endif
