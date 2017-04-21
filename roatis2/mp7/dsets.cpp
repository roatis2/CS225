/* Your code here! */
#include <vector>
#include "dsets.h"

/*Creates n unconnected root nodes at the end of the vector*/
void DisjointSets::addelements(int num)
{
  for(int i = 0; i < num; i++)
    dSets.push_back(-1);
  return;
}
/*This function should compress paths and works as described in lecture*/
int DisjointSets::find(int elem)
{
  if(dSets[elem] < 0)
    return elem;
  else
  {
    dSets[elem] = find(dSets[elem]);
    return dSets[elem];
  }
}
/*makes union*/
void DisjointSets::setunion(int a, int b)
{
  int rootA = find(a);
  int rootB = find(b);
  if(rootA == rootB)
    return;

  int unionSize = dSets[rootA] + dSets[rootB];

  if(dSets[rootA] > dSets[rootB])
  {
    dSets[rootA] = rootB;
    dSets[rootB] = unionSize;
  }

  else
  {
    dSets[rootB] = rootA;
    dSets[rootA] = unionSize;
  }
  return;
}
