#include <cstdint>
#include "rgbapixel.h"
#include "png.h"

using namespace std;

int main()
{
   int r, g, b; //holds values temporarily while moved in array
   
   PNG picture("in.png");//opens png

   if(picture.height()!=0 && picture.width()!=0) //accounts for 0x0 picture
   {
	PNG swap(picture.width(), picture.height());
	for(size_t j = 0; j<picture.height(); j=j+1)
	{
	   for(size_t i = 0; i<picture.width(); i=i+1)
	   {
		r = picture(i,j)->red;
		swap(picture.width()-i-1, picture.height()-j-1)->red = r;
		g = picture(i,j)->green;
		swap(picture.width()-i-1, picture.height()-j-1)->green = g;
		b = picture(i,j)->blue;
		swap(picture.width()-i-1, picture.height()-j-1)->blue = b;
	   }
	}
	swap.writeToFile("out.png");
   }
return 0;
}
		
	
