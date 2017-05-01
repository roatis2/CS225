/* Your code here! */
#ifndef DSETS_H
#define DSETS_H
#include <vector>

using namespace std;

class DisjointSets
{
  public:
    /*Creates n unconnected root nodes at the end of the vector*/
    void addElem(int k);
    /*This function should compress paths and works as described in lecture. */
    int find(int elem);
    /*makes union*/
    void UBS(int num1, int num2);

  private:
    vector <int> dSets;
};

#endif
