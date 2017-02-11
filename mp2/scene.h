#ifndef SCENE_H
#define SCENE_H
#include <cstdint>
#include <iostream>
#include "png.h"
#include "scene.h"
#include "image.h"

class Scene
{
  public:
  //initializes this scene ovject to be able to
  //hold "max" number of images with indices 0
  //through max-1
  Scene(int max);

  //Frees all space that was dynamically
  //allocated scene
  ~Scene();

  //Copy constructor makes this Scene an independent copy of the source
  Scene(const Scene &source);

  //the assignment operator for the Scene class
  const Scene& operator=(const Scene &source);

  //Modifies the size of the array of Image pointers without changing their indices
  void changemaxlayers (int newmax);

  //add a picture to the scene, by placing it in the array cell corresponding to the given index and storing its x coordinate and y coordinate
  void addpicture (const char *FileName, int index, int x, int y);

  //Moves an image from one layer to another
  void changelayer(int index, int newindex);

  //changes the x and y coordinates of the image in the specified layer
  void translate(int index, int xcoord, int ycoord);

  //Deletes the image at the given index
  void deletepicture(int index);

  //This function will return a pointer to the image at the specified index, not a copy of it
  Image* getpicture(int index)const;

  //Draws the whole scene on one image and returns that image by value
  Image drawscene() const;

  //clear helper function
  void clear();
  void copy(Scene const & other);


  private:
  int max;
  Image **imageptr;
  int *x_cord;
  int *y_cord;

};

#endif
