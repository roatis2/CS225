#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H
#include <cstdint>

using namespace std;

class RGBAPixel
{
	public:

	//constructs a default RGBAPixel
	RGBAPixel();

	//constructs an opaque RGBAPixel with given red, green, and         //blue color values
	RGBAPixel(uint8_t red, uint8_t green, uint8_t blue); 

	//byte for red, green, blue, and alpha component of pixel
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;

};
#endif
