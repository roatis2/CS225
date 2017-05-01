/* Your code here! */
#include <vector>
#include "dsets.h"


/*This function should compress paths and works as described in lecture*/
int DisjointSets::find(int elem)
{
  if(dSets[elem] < 0)
    return elem;
  else
  {
    return dSets[elem] = find(dSets[elem]);
    //return dSets[elem];
  }
}

/*makes union*/
void DisjointSets::UBS(int num1, int num2)
{
  int A = find(num1);
  int B = find(num2);
  if(A == B)
    return;

  int unionSize = dSets[A] + dSets[B];

  if(dSets[A] > dSets[B])
  {
    dSets[A] = B;
    dSets[B] = unionSize;
  }

  else
  {
    dSets[B] = A;
    dSets[A] = unionSize;
  }
  return;
}

/*Creates n unconnected root nodes at the end of the vector*/
void DisjointSets::addElem(int k)
{
  for(int i = 0; i < k; i++)
    dSets.push_back(-1);
  return;
}
