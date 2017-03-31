/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */
#include <cmath>
#include "quadtree.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////Constructors/////////////
/*default constructor*/
Quadtree::Quadtree(){
  root = NULL;
}

/*2 parameter constructor*/
Quadtree::Quadtree(PNG const & source, int resolution){
  buildTree(source, resolution);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////Big Three///////////
/*copy constructor*/
Quadtree::Quadtree(Quadtree const & other){
  if(other.root == NULL){ //case where we copy a null tree
    root = NULL;
    return;
  }
  root = copy(other.root);
}

/*copy constructor helper*/
Quadtree::QuadtreeNode * Quadtree::copy(QuadtreeNode * other){
  if(other == NULL) //root is null, we have an empty tree
    return NULL;
  QuadtreeNode * treeCopy = new QuadtreeNode::QuadtreeNode(other); //make new tree starting with other's root
  /*recursilvey copy other's children*/
  treeCopy->nwChild = copy(other->nwChild);
  treeCopy->neChild = copy(other->neChild);
  treeCopy->swChild = copy(other->swChild);
  treeCopy->seChild = copy(other->seChild);
  return treeCopy;//copy is now a finished copy
}

/*destructor*/
Quadtree::~Quadtree(){
  clear(root); //helper
}

/*destructor helper*/
void Quadtree::clear(QuadtreeNode * &subRoot){
  if(subRoot == NULL) //if empty tree, we don't need to do anything
    return;
  /*case where tree isn't empty*/
  /*recursively clear children*/
  clear(subRoot->nwChild);
  clear(subRoot->neChild);
  clear(subRoot->swChild);
  clear(subRoot->seChild);
  delete subRoot;
  subRoot = NULL;
}
/*operator overloader*/
Quadtree const & Quadtree::operator=(Quadtree const & other){
  if(root == other.root) //check if they are referring to same object
    return *this; //return current object
  //copy(other.root); //copy new tree
  clear(root); //delete original tree
  root = copy(other.root);//copy other tree
  return *this; //return current object
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////Build Tree/////////////
/*Deletes the current contents of this Quadtree object, then turns it into a Quadtree object representing the upper-left d by d block of source.*/
void Quadtree::buildTree(PNG const & source, int resolution){
  /* first create root*/
  root = new QuadtreeNode(0,0,resolution);
  /* using root, we can now build tree. create children down tree, then find average color coming back up */
  buildTreeHelper(source, resolution, root);
}

/*helper for buildTree*/
void Quadtree::buildTreeHelper (PNG const & source, int resolution, QuadtreeNode * subRoot){
  /*base case. we can assume resolution with be a number divisible by 2 but still need base case*/
  if(resolution == 1){
    subRoot->element = *(source(subRoot->x, subRoot->y));
    return;
  }
  /*build children
  (x,y) = (0,0) -> top left corner
  each child will have resolution which is half of parent*/
  subRoot->nwChild = new QuadtreeNode(subRoot->x,subRoot->y, resolution/2);
  subRoot->neChild = new QuadtreeNode(subRoot->x + resolution/2, subRoot->y, resolution/2);
  subRoot->swChild = new QuadtreeNode(subRoot->x, subRoot->y + resolution/2, resolution/2);
  subRoot->seChild = new QuadtreeNode(subRoot->x + resolution/2, subRoot->y + resolution/2, resolution/2);
  /* recursively build upwards the rest of children in tree*/
  buildTreeHelper(source, resolution/2, subRoot->nwChild);
  buildTreeHelper(source, resolution/2, subRoot->neChild);
  buildTreeHelper(source, resolution/2, subRoot->swChild);
  buildTreeHelper(source, resolution/2, subRoot->seChild);
  /* get average color of children to be used for parent */
  subRoot->element.red = (subRoot->nwChild->element.red + subRoot->neChild->element.red + subRoot->swChild->element.red+subRoot->seChild->element.red)/4;
  subRoot->element.green = (subRoot->nwChild->element.green + subRoot->neChild->element.green + subRoot->swChild->element.green + subRoot->seChild->element.green)/4;
  subRoot->element.blue = (subRoot->nwChild->element.blue + subRoot->neChild->element.blue + subRoot->swChild->element.blue + subRoot->seChild->element.blue)/4;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////Get Pixel//////////////
/*Gets the RGBAPixel corresponding to the pixel at coordinates (x, y) in the bitmap image which the Quadtree represents.*/
RGBAPixel Quadtree::getPixel(int x, int y) const{
  return getPixelhelper(x,y,root);
}

/*helper function for getPixel*/
RGBAPixel Quadtree::getPixelhelper(int x, int y, QuadtreeNode * subRoot) const{
  /*base case: reached leaf or cant go smaller*/
  if((subRoot->x == x && subRoot->y == y && subRoot->res == 1) || (subRoot->neChild == NULL))
    return subRoot->element;
  /*recursively check each child*/
  if(inBounds(x,y,subRoot->nwChild))
    return getPixelhelper(x,y,subRoot->nwChild);
  else if(inBounds(x,y,subRoot->neChild))
      return getPixelhelper(x,y,subRoot->neChild);
  else if(inBounds(x,y,subRoot->swChild))
        return getPixelhelper(x,y,subRoot->swChild);
  else
      return getPixelhelper(x,y,subRoot->seChild);

}

/*helper for helper above. Returns true if a (x,y) coordinate is within bounds given by resolution of subroot*/
bool Quadtree::inBounds(int x, int y, QuadtreeNode * subRoot) const{
  /*establish bounds*/
  int width = subRoot->x + subRoot->res;
  int height = subRoot->y + subRoot->res;
  /*bounds are in between x & width and y and height*/
  return(x >= subRoot->x && x < width) && (y >= subRoot->y && y < height);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////Decompress/////////////////
/*Returns the underlying PNG object represented by the Quadtree.*/
PNG Quadtree::decompress() const{
  /* if empty quad tree, return default PNG */
  if(root == NULL){
    PNG defaultPNG;
    return defaultPNG;
  }
  /*decompress PNG
  create different PNG and fill it with getPixel of original PNG*/
  else{
    PNG tempPNG(root->res,root->res);
    for(int i = 0; i < root->res; i++){
      for(int j = 0; j < root->res; j++){
        *tempPNG(i,j) = getPixel(i,j);
      }
    }
    return tempPNG;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////Clockwise Rotate//////////////////
/*Rotates the Quadtree object's underlying image clockwise by 90 degrees.*/
void Quadtree::clockwiseRotate(){
  /*empty tree case*/
  if(root == NULL)
    return; //do nothing

  clockwiseRotateHelper(root);
  return;
}

/*helper function for clockwiseRotate*/
void Quadtree::clockwiseRotateHelper(QuadtreeNode * subRoot){
  /*point to original node values*/
  QuadtreeNode * neVal = subRoot->neChild;
  QuadtreeNode * nwVal = subRoot->nwChild;
  QuadtreeNode * swVal = subRoot->swChild;
  QuadtreeNode * seVal = subRoot->seChild;
  /*move pointers 90 degrees. ne->nw nw->sw sw->se se->ne*/
  subRoot->neChild = nwVal;
  subRoot->nwChild = swVal;
  subRoot->swChild = seVal;
  subRoot->seChild = neVal;
  /*recursively call until we reach leaves*/
  if(subRoot->nwChild != NULL){
    clockwiseRotateHelper(subRoot->neChild);
    clockwiseRotateHelper(subRoot->nwChild);
    clockwiseRotateHelper(subRoot->swChild);
    clockwiseRotateHelper(subRoot->seChild);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////Prune/////////////////////
void Quadtree::prune(int tolerance){
    /*case of empty quadtree or impossible tolerance*/
    if(root == NULL || tolerance < 0)
        return; //do nothing

    pruneHelper(root, tolerance);
    return;
}

void Quadtree::pruneHelper(QuadtreeNode * subRoot, int tolerance){
  /*base case, reached leaf, can't prune so end function*/
  if(subRoot->nwChild == NULL)
    return;
  /*if its pruneable clear children*/
  if(checkPrune(subRoot, subRoot, tolerance))
    {
    	clear(subRoot->neChild);
    	subRoot->neChild = NULL;
    	clear(subRoot->nwChild);
    	subRoot->nwChild = NULL;
    	clear(subRoot->swChild);
    	subRoot->swChild = NULL;
    	clear(subRoot->seChild);
    	subRoot->seChild = NULL;
    	return;
    }
  /*find pruneable children*/
  else
    {
    	pruneHelper(subRoot->neChild, tolerance);
    	pruneHelper(subRoot->nwChild, tolerance);
    	pruneHelper(subRoot->swChild, tolerance);
    	pruneHelper(subRoot->seChild, tolerance);
    	return;
    }
}

bool Quadtree::checkPrune(QuadtreeNode * start, QuadtreeNode * current, int tolerance){
  /*check if this is pruneable*/
  if(current->neChild == NULL)
  	return pruneable(start, current, tolerance);

  /*check is any of children are prubeable*/
  if(!checkPrune(start, current->nwChild, tolerance))
  	return false;
  else if(!checkPrune(start, current->neChild, tolerance))
  	return false;
  else if(!checkPrune(start, current->swChild, tolerance))
  	return false;
  else if(!checkPrune(start, current->seChild, tolerance))
  	return false;
  else
  	return true;
}

bool Quadtree::pruneable(QuadtreeNode * node1, QuadtreeNode * node2, int tolerance){
  /* variables to make latter calculation easier to read*/
  int dR = node1->element.red - node2->element.red;
  int dG = node1->element.green - node2->element.green;
  int dB = node1->element.blue - node2->element.blue;

  /*determine if difference in colors is within tolerance aka if we will prune*/
  if(pow(dR,2) + pow(dG,2) + pow(dB,2) <= tolerance)
    return true;
  else
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////Prune Size///////////////
int Quadtree::pruneSize(int tolerance) const{
  /*tree isn't pruneable at all, return 0*/
  if(root == NULL || tolerance < 0)
    return 0;

  /*make copy of tree, prune copy tree, count resultant leaves, this while be the prune size*/
  Quadtree treeCopy = Quadtree(*this); //this way we do not prune the original tree
  treeCopy.prune(tolerance);//prune according to tolerance parameter
  int prunedTreeSize = numleaves(treeCopy.root);
  return prunedTreeSize;

}
/*helper function that counts the number of leaves*/
int Quadtree::numleaves(QuadtreeNode * subRoot) const{
  /*base case, found leaf*/
  if(subRoot->nwChild == NULL)
    return 1;

  /*recursively count the rest of leaves*/
  int total = numleaves(subRoot->nwChild) + numleaves(subRoot->neChild) + numleaves(subRoot->swChild) + numleaves(subRoot->seChild);
  return total;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////Ideal Prune//////////
int Quadtree::idealPrune(int numLeaves) const{
  /*no tree, can't prune*/
  if(root == NULL)
  		return 0;
  /*can't have negative tolerance*/
  if(numLeaves >= numleaves(root))
  		return 0;
  /*find maxTolerance*/
  int maxLeaves = numleaves(root);
  int maxTolerance = 10000; //set to large number
  /*will return something around max tolerance*/
  if(numLeaves <= 1)
  		return findBestTolerance(maxTolerance - 10000, maxTolerance, 1);
  /*refine upperTolerance*/
  while(pruneSize(maxTolerance) > numLeaves)
  		maxTolerance = maxTolerance + 10000;
  /*recursively repeat until we find the ideal tolerance*/
  return findBestTolerance(maxTolerance - 10000, maxTolerance, numLeaves);
}

int Quadtree::findBestTolerance(int lowerTolerance, int upperTolerance, int numLeaves) const {
  /*trim down range between upper and lower tolerance until we find tolerance down to nearest integer*/
  int idealTolerance = (upperTolerance + lowerTolerance)/2;
  int idealLeaves = pruneSize(idealTolerance);
  int forPrecision = pruneSize(idealTolerance - 1);
  /*found ideal tolerance*/
  if(idealLeaves <= numLeaves && forPrecision > numLeaves)
    return idealTolerance;
  /*range too small*/
  if(idealTolerance == upperTolerance)
    return idealTolerance - 1;
  /*ideal tolerance is in lower half of range*/
  if(idealLeaves >= numLeaves)
    return findBestTolerance(idealTolerance + 1, upperTolerance, numLeaves);
  /*ideal tolerance is in upper half of tange*/
  else
    return findBestTolerance(lowerTolerance, idealTolerance - 1, numLeaves);
}
