/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include "png.h"
#include "rgbapixel.h"
#include "dsets.h"
#include <vector>

using namespace std;

class SquareMaze
{
public:
  SquareMaze();
  ~SquareMaze();
  void makeMaze(int width, int height);
  bool canTravel(int x, int y, int dir) const;
  void setWall(int x, int y, int dir, bool exists);
  vector<int> solveMaze();
  PNG * drawMaze() const;
  PNG * drawMazeWithSolution();

private:
  int h;
  int w;
  int max;
  void travel_maze(int &x, int &y, int &length);
  struct dBool
  {
    dBool();
    bool rightWall;
    bool bottomWall;
    bool haveVisited;
  };
  dBool ** maze;
  void clear();
};

#endif
