/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <cmath>

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
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

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target, const Point<Dim>& currentBest, const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     if(replaceHelper(target, potential) == replaceHelper(target, currentBest))
      return potential < currentBest;
     else if(replaceHelper(target, potential) < replaceHelper(target, currentBest))
      return true;
    else
      return false;
}

template <int Dim>
int KDTree<Dim>::replaceHelper(const Point<Dim>& target, const Point<Dim>& currentPoint)const{ //calculate distance btwn pts
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
     buildHelper(0, points.size() - 1, 0);
}

template <int Dim>
void KDTree<Dim>::buildHelper(int left, int right, int dim){
  int mid = (right + left)/2;
  //if(mid == 0){
  //  return;
  //}
  quickSelect(mid, left, right, dim);
  if(left < mid){
      buildHelper(left, mid - 1, (dim+1) % Dim);
  }
  if(right > mid){
    buildHelper(mid + 1, right, (dim+1) % Dim);
  }
}

template <int Dim>
void KDTree<Dim>::quickSelect(int median, int left, int right, int dim){
  if(left >= right){
    return;
  }
  int pivot = (left + right)/2;
  pivot = partition(left, right, pivot, dim);
  if(median == pivot){
        return;
  }
  else if(median < pivot){
      quickSelect(median, left, pivot - 1, dim);
  }
  else{
      quickSelect(median, pivot + 1, right, dim);
  }
}

template <int Dim>
int KDTree<Dim>::partition(int left, int right, int pivot, int dim){
   Point<Dim> pivots = points[pivot];
   Point<Dim> temp = points[right];
   points[right] = points[pivot];
   points[pivot] = temp;
   int holdLeft = left;
   for (int i = left; i < right; i++)
   {
       if (smallerDimVal(points[i], pivots, dim) || points[i] == pivots)
       {
           Point<Dim> xtemp = points[holdLeft];
           points[holdLeft] = points[i];
           points[i] = xtemp;
           holdLeft++;
       }
   }
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
    int right = points.size()-1;
    Point<Dim> ret;
    if(points.size() != 0){
      ret = nnHelper(0, right, 0, query, ret);
    }
    return ret;
}

template <int Dim>
Point<Dim> KDTree<Dim>::nnHelper(int left, int right, int dim, const Point<Dim>& query, const Point<Dim>& currBest) const{
    Point<Dim> ret = currBest;
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

    if(smallerDimVal(query, points[mid], dim) && left < mid){
      ret = nnHelper(left, mid - 1, (dim+1) % Dim , query, currBest);
    }
    if(!smallerDimVal(query, points[mid], dim) && mid < right){
      ret = nnHelper(mid + 1, right, (dim+1) % Dim , query, currBest);
    }
    if(shouldReplace(query, ret, points[mid])){
        ret = points[mid];
    }
    int dis = replaceHelper(query, ret);
      if((query[dim] - points[mid][dim]) * (query[dim] - points[mid][dim]) <= dis){
          if(left < mid){
            ret = nnHelper(left, mid - 1, (dim+1) % Dim , query, ret);
          }
          if(mid < right){
            ret = nnHelper(mid + 1, right, (dim+1) % Dim , query, ret);
          }
      }
    return ret;
}
