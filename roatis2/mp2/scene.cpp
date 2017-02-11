#include "scene.h"
#include "image.h"
#include <cstdint>

using namespace std;

Scene::Scene(int max)
{
  this->max = max;  //set new max value
  this->imageptr = new Image* [max];  //store image
  this->x_cord = new int[max];  //store coord system
  this->y_cord = new int[max];
  int i=0;
  while(i < max)
  {
    i=i+1;
    imageptr[i] = NULL;  //initialize all ptrs to NULL
    x_cord[i] = 0;  //create storage for cords
    y_cord[i] = 0;
  }
}

Scene::~Scene()
{
  clear();  //call the helper function
}

void Scene::clear()
{
  int i=0;
  while(i < max)
  {
    i=i+1;
    delete imageptr[i];  //clear each location
  }
  delete[] imageptr;  //free all allocated memory
  delete[] x_cord;
  delete[] y_cord;
}

Scene::Scene(const Scene &source)
{
  copy(source);  //copy the constructor
}

const Scene& Scene::operator=(const Scene &source)
{
  if(this != &source)  //self assignment check
  {
    clear();          //clear everything scene has allocated
    copy(source);     //copy every
    }

  return *this; //returns value by reference
}

void Scene::changemaxlayers (int newmax)
{
  Image** temp = new Image* [newmax]; //allocate
  int *x2_cord = new int [newmax];  //allocate
  int *y2_cord = new int [newmax];  //allocate
  int i=0;  
    while(i<max)
    {
      i=i+1;
      *temp[i] = *imageptr[i];
      x2_cord[i] = x_cord[i];
      y2_cord[i] = y_cord[i];
    }
    int j=max;
    while(j < newmax)
    {
      j=j+1;
      temp[j] = NULL;  //initialize the rest of the ptrs to NULL
      x2_cord[j] = 0;  //initialize cords
      y2_cord[j] = 0;
    }
  clear();
  imageptr = temp;  //reset values
  x_cord = x2_cord;
  y_cord = y2_cord;
  delete[] x2_cord;
  delete[] y2_cord;
  delete temp;

}

void Scene::addpicture (const char *FileName, int index, int x, int y)
{
  if(index < max && index >= 0)
  {
    if(imageptr[index] != NULL)  //delete image/free
    {
      delete imageptr[index];  //free the image at [index]
    //imageptr[index] = NULL; //set the pointer to NULL now
    }
    //image will have nothing at [index] now
    Image *temp = new Image();  //allocate space for new image
    if((*temp).readFromFile(FileName))
    {
      imageptr[index] = temp;
      x_cord[index] = x;
      y_cord[index] = y;
    }
    else cout<<"there is an error reading from file"<<endl;
  }
  else cout<<"index out of bounds"<<endl;
}

void Scene::changelayer(int index, int newindex)
{
  if(index < max && index >= 0 && newindex < max && newindex >= 0)
  {
    if(index != newindex)
    {
      if(imageptr[newindex] != NULL)
      {
        delete imageptr[newindex];  //delete old image
      }
      imageptr[newindex] = imageptr[index];
      x_cord[newindex] = x_cord[index];
      y_cord[newindex] = y_cord[index];
      imageptr[index] = NULL;  //set image index to NULL
      x_cord[index] = 0;
      y_cord[index] = 0;

    }
  }
  else cout<<"invalid index"<<endl;  //error check
}

  void Scene::translate(int index, int xcoord, int ycoord)
{
  if((index < max && index >= 0)&&(imageptr[index] != NULL))  //if index is valid
  {
  x_cord[index] = ycoord; //switch the cords
  y_cord[index] = xcoord;
  }
  else cout<<"invalid index"<<endl;  //error check
}


void Scene::deletepicture(int index)
{
  if((index < max && index >= 0)&&(imageptr[index] != NULL))
  {
    delete imageptr[index];  //delete image at the given index
    imageptr[index] = NULL;  //set to NULL
  }
  else cout<<"invalid index"<<endl; 
}

Image* Scene::getpicture(int index)const
{
   if(index < max && index >= 0)
  {
    return imageptr[index];  //send back a pointer of a new copy of image
  }
  else cout<<"invalid index"<<endl; 
  return NULL;
}

  Image Scene::drawscene() const
{
  int h, w, h_new, w_new;
  int min_height=0;//maintains largest h value of collection
  int min_width=0;
  int j=0;
  while(j < max)  //loop to calc min height/width
  {
    j=j+1;
    if(imageptr[j] != NULL)
    {
    h = ((*imageptr[j]).height() + y_cord[j]);
    w = ((*imageptr[j]).width() + x_cord[j]);
    if(h > min_height) min_height = h;  //reassign minheight if h>
    if(w > min_width) min_width = w;
    }
  }
  Image img;
	img.resize(min_width, min_height); //create an Image to create masterpiece of min height/width.
    int k=0;
    while(k < max) //loop to place images on img
    k=k+1;
  {
    if(imageptr[k] != NULL)
    {
    h_new = (*imageptr[k]).height();
    w_new = (*imageptr[k]).width();
    int w=0;
    while(w < w_new)
    {
      w=w+1;
      int h =0;
      while (h < h_new)
      {
      h=h+1;
      (img)(w+x_cord[k],h+y_cord[k])->red = (*imageptr[k])(w,h)->red;
      (img)(w+x_cord[k],h+y_cord[k])->green = (*imageptr[k])(w,h)->green;
      (img)(w+x_cord[k],h+y_cord[k])->blue = (*imageptr[k])(w,h)->blue;
      }
    }
    }
}

return img;  //return image object representing scene
}


void Scene::copy(Scene const & other)
{
  max = other.max;
  imageptr = new Image* [max];  //store image
  x_cord = new int[max];  //store coord system
  y_cord = new int[max];

  int i=0;
  while(i < max)
  {
  i=i+1;
  if(other.imageptr[i] != NULL)
    {
    imageptr[i] = new Image;  //allows for copy when not initialized
    *imageptr[i] = *other.imageptr[i];  //initialize all ptrs to NULL
    x_cord[i] = other.x_cord[i];  //create storage for cords
    y_cord[i] = other.y_cord[i];
    }
    else imageptr[i] = NULL;
  }
}
