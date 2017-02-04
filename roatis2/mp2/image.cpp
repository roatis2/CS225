#include "image.h"

//Flips the image about a vertical line through its center by swapping pixels
void Image::flipleft()
{
   int width = this->width();
   int height = this->height();

   for(int j = 0; j<height; j++)
   {
      for(int i = 0; i<(width/2); i++)
      {
	RGBAPixel temp = *(*this)(i,j);
	*(*this)(i,j)=*(*this)(width-i-1, j);
	*(*this)(width-i-1, j) = temp;
      }
   }
}

//adds to the red, green, and blue parts of each pixel in the image
void Image::adjustbrightness(int r, int g, int b)
{
   int width = this->width();
   int height = this->height();

   for(int j = 0; j<height; j++)
   {
      for(int i = 0; j<width; i++)
      {
	int checkred = ((*this)(i,j)->red) + r; 
	int checkgreen = ((*this)(i,j)->green) + g;
	int checkblue = ((*this)(i,j)->blue) +b;

	if(checkred>=255){
 	      (*this)(i,j)->red = 255;}
	   else if(checkred<=0){
	      (*this)(i,j)->red = 0;}
	   else(*this)(i,j)->red =((*this)(i,j)->red) + r;

	if(checkgreen>=255){
	      (*this)(i,j)->green = 255;}
	   else if(checkgreen<=0){
   	      (*this)(i,j)->green = 0;}
	   else(*this)(i,j)->green = ((*this)(i,j)->green) + g;

	if(checkblue>=255){
	      (*this)(i,j)->blue = 255;}
	   else if(checkblue<=0){
	      (*this)(i,j)->blue = 0;}
	   else(*this)(i,j)->blue = ((*this)(i,j)->blue) + b;
      }
   }
}


//Makes each RGB component of each pixel equal to 255 minus its original value

void Image::invertcolors()
{
   int width = this->width();
   int height = this->height();

   for(int j = 0; j<height; j++)
      {
      for(int i = 0; i<width; i++)
	{
	   (*this)(i,j)->red = 255 - (*this)(i,j)->red;
	   (*this)(i,j)->blue = 255 - (*this)(i,j)->blue;
	   (*this)(i,j)->green = 255 - (*this)(i,j)->green;
	}
      }
}



