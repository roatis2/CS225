/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:
  /*main functions*/
  Quadtree(); //default constructor
  Quadtree(const PNG & source, int resolution); //2 parameter constructor
  Quadtree(Quadtree const & other); //copy constructor
  ~Quadtree();  //Destructor
  Quadtree const & operator=(Quadtree const & other); //operator overloader
  /*Deletes the current contents of this Quadtree object, then turns it into a Quadtree object representing the upper-left d by d block of source.*/
  void buildTree(PNG const & source, int resolution);
  /*Gets the RGBAPixel corresponding to the pixel at coordinates (x, y) in the bitmap image which the Quadtree represents.*/
  RGBAPixel getPixel(int x, int y) const;
  /*Returns the underlying PNG object represented by the Quadtree.*/
  PNG decompress() const;
  /*Rotates the Quadtree object's underlying image clockwise by 90 degrees.*/
  void clockwiseRotate();
  /*check doxygen, basically reduce image quality of image*/
  void prune(int tolerance);
  /*returns a count of the total number of leaves the Quadtree would have if it were pruned as in the prune function.*/
  int pruneSize(int tolerance) const;
  /*Calculates and returns the minimum tolerance necessary to guarantee that upon pruning the tree, no more than numLeaves leaves remain in the Quadtree.*/
  int idealPrune(int numLeaves) const;

  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class QuadtreeNode
    {
      public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */
        RGBAPixel element; /**< the pixel stored as this node's "data" */
        /*parameters for QuadtreeNode constructor*/
        int x;
        int y;
        int res;
        /*non-leaf QuadtreeNode constructor*/
        QuadtreeNode(int xc, int yc, int resolution)
        {
          this->x = xc;
          this->y = yc;
          this->res = resolution;
          nwChild = NULL;
          neChild = NULL;
          swChild = NULL;
          seChild = NULL;
        }
        /*leaf QuadtreeNode constructor*/
        QuadtreeNode(int xc, int yc, int resolution, PNG & source)
        {
          this->x = xc;
          this->y = yc;
          this->res = resolution;
          nwChild = NULL;
          neChild = NULL;
          swChild = NULL;
          seChild = NULL;
          this->element = *(source(x,y));
        }
        /*QuadtreeNode copy constructor*/
        QuadtreeNode(QuadtreeNode const * other)
        {
          this->x = other->x;
          this->y = other->y;
          this->res = other->res;
          nwChild = NULL;
          neChild = NULL;
          swChild = NULL;
          seChild = NULL;
          this->element = other->element;
        }
    };
    QuadtreeNode* root; /**< pointer to root of quadtree */

    /* helper functions */
    void clear(QuadtreeNode * &subRoot); //destructor helper function, pbr bc we need to save changes made
    QuadtreeNode * copy(QuadtreeNode * other); //copy constructor helper function. doesn't need pbr bc we arent changing old one
    void buildTreeHelper (PNG const & source, int resolution, QuadtreeNode * subRoot); //buildtree helper fn
    RGBAPixel getPixelhelper(int x, int y, QuadtreeNode * subRoot) const; //getpixel helper fn
    bool inBounds(int x, int y, QuadtreeNode * subRoot) const; //helper for getPixelHelper
    void clockwiseRotateHelper(QuadtreeNode * subRoot); //helper for clockwiseRotateHelper
    void pruneHelper(QuadtreeNode * subRoot, int tolerance);//helper for prune
    bool checkPrune(QuadtreeNode * start, QuadtreeNode * current, int tolerance); //checks children to see if node can be pruned
    bool pruneable(QuadtreeNode * node1, QuadtreeNode * node2, int tolerance); //checks tolerance to seee if node can be pruned
    int numleaves(QuadtreeNode * subroot) const; //helper for pruneSize
    int findBestTolerance(int lowerTolerance, int upperTolerance, int numLeaves) const; //helper for idealprune

/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif
