/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <cmath>

/*Determines if Point a is smaller than Point b in a given dimension d.*/
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first, const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     /*tiebreaker case*/
     if(first[curDim] == second[curDim])
      return first < second;
     else if(first[curDim] < second[curDim])
      return true;
     else
      return false;
}


/*Determines if a Point is closer to the target Point than another reference Point.*/
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target, const Point<Dim>& currentBest, const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     /*if tied, use overloaded < operator*/
     if(distanceToTarget(target, potential) == distanceToTarget(target, currentBest))
      return potential < currentBest;
     else if(distanceToTarget(target, potential) < distanceToTarget(target, currentBest))
      return true;
    else
      return false;
}

/*helper function for should replace, finds distance to target for the currentBest and potential above*/
template <int Dim>
int KDTree<Dim>::distanceToTarget(const Point<Dim>& target, const Point<Dim>& currentPoint) const
{
  /* distance = sqrt((t1 - cp1)^2 + (t2 - cp2)^2 - (t3 - cp3)^2 .... (tk - cpk)^2) */
  int distanceSquared = 0;
  for(size_t i = 0; i < Dim; i++){
    distanceSquared = distanceSquared + pow((target[i] - currentPoint[i]),2);
  }
  int distance = sqrt(distanceSquared);
  return distance;

}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     points = newPoints;
     buildKDTree(0, 0, points.size() - 1);
}

template <int Dim>
void KDTree<Dim>::buildKDTree(int dim, int left, int right)
{
  /*set median*/
  int median = floor((left + right)/2);
  /*no range*/
  if(median == 0)
    return;
  /*make partitions*/
  quickSelect(median, left, right, dim);
  /*build left*/
    if (left < median)
        buildKDTree((dim + 1) % Dim, left, median-1);
  /*build right*/
    if (right > median)
        buildKDTree((dim + 1) % Dim, median + 1, right);
}

template <int Dim>
void KDTree<Dim>::quickSelect(int median, int left, int right, int dim)
{
  /*mispartition, return*/
  if(left >= right)
    return;
  /*set pivot*/
  int pivot = floor((left + right)/2);
  pivot = partition(left, right, pivot, dim); //change pivot due to partition
  if(median == pivot) //range is 0
        return;
    else if(median < pivot) //quickSelect left
        quickSelect(left, pivot - 1, dim, median);
    else  //quickSelect right
        quickSelect(pivot + 1, right, dim, median);
}

template <int Dim>
int KDTree<Dim>::partition(int left, int right, int pivot, int dim)
{
    /*swap points[right] and points[pivot]*/
   Point<Dim> pivotPoint = points[pivot];
   Point<Dim> temp = points[right];
   points[right] = points[pivot];
   points[pivot] = temp;
   int holdLeft = left; //hold left values
   for (int i = left; i < right; i++)
   {
       if (smallerDimVal(points[i], pivotPoint, dim) || points[i] == pivotPoint)
       {
           /*swap left and current point*/
           temp = points[holdLeft];
           points[holdLeft] = points[i];
           points[i] = temp;
           holdLeft++;
       }
   }
   /*swap right points and left points*/
   temp = points[right];
   points[right] = points[holdLeft];
   points[holdLeft] = temp;
   return holdLeft;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     /*initialize variables*/
     int right = points.size()-1;
     return nnHelper(0, right, 0, query, points[right/2] );

}

template <int Dim>
Point<Dim> KDTree<Dim>::nnHelper(int left, int right, int dim, const Point<Dim>& query, const Point<Dim>& currBest) const{
    Point<Dim> ret = currBest;
    bool b1 = false;
    if(left == right){
      if(shouldReplace(query, currBest, points[left])){
        ret = points[left];
        return ret;
      }
      else{
        ret = currBest;
        return ret;
      }
    }
    int mid = (left+right)/2;
    //Point<Dim> pt = points[mid];
    if(smallerDimVal(query, points[mid], dim) && left < mid){
      ret = nnHelper(left, mid - 1, (dim+1) % Dim , query, currBest);
      b1 = false;
    }
    if(!smallerDimVal(query, points[mid], dim) && mid < right){
      ret = nnHelper(mid + 1, right, (dim+1) % Dim , query, currBest);
      b1 = true;
    }
    if(shouldReplace(query, ret, points[mid])){
        ret = points[mid];
    }
    int dis = distanceToTarget(query, ret);
      if((query[dim] - points[mid][dim]) * (query[dim] - points[mid][dim]) <= dis){
          if(b1 == true && left < mid){
            ret = nnHelper(left, mid - 1, (dim+1) % Dim , query, ret);
          }
          if(b1 == false && mid < right){
            ret = nnHelper(mid + 1, right, (dim+1) % Dim , query, ret);
          }
      }


    return ret;
}
