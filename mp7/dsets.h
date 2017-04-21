/* Your code here! */
#ifndef DSETS_H
#define DSETS_H
#include <vector>

using namespace std;

class DisjointSets
{
  public:
    /*Creates n unconnected root nodes at the end of the vector*/
    void addelements(int num);
    /*This function should compress paths and works as described in lecture. */
    int find(int elem);
    /*makes union*/
    void setunion(int a, int b);

  private:
    vector <int> dSets;
};

#endif
