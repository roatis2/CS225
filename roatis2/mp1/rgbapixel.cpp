#include "rgbapixel.h"
#include <cstdint>
//create opaque white pixel
RGBAPixel::RGBAPixel(){
	red = 255; //set to 255 to make white
	blue = 255; //set to 255 to make white
	green = 255; //set to 255 to make white
	alpha = 255; //set to 255 to make opaque
}

//create opaque pixel with given red green and blue values
RGBAPixel::RGBAPixel(uint8_t red, uint8_t green, uint8_t blue){
	this -> red = red; 
	this -> blue = blue;
	this -> green = green;
	this -> alpha = 255;
}

