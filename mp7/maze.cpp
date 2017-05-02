/* Your code here! */
#include "maze.h"
#include <queue>
using namespace std;
////////////////////////////////////////////////////////////////////////////////
SquareMaze::SquareMaze()
{
  //no parameter constructor
}

SquareMaze::~SquareMaze()
{
	clear();
}

void SquareMaze::clear()
{
	for(int i = 0; i < w; i++)
 	{
 		delete [] maze[i];
 	}
 	delete [] maze;
	return;
}

SquareMaze::dBool::dBool()
{
	haveVisited = false;
	rightWall = true;
  bottomWall = true;
}
////////////////////////////////////////////////////////////////////////////////
void SquareMaze::makeMaze(int width, int height)
{
	//first we need to clear everything
	DisjointSets s;
  this->h = height;
  this->w = width;
	int res = w * h;
	maze = new dBool * [w];
	for(int i = 0; i < w; i++)
		maze[i] = new dBool[h];
	/*will be true if the wall is present
  will befalse if the wall is absent
	and all the walls are present in the beginning*/
	s.addelements(res);
  //initialize x and y
	int y;
	int x;
  //initialize PRNG
	srand(time(NULL));
  int count = 0;
	while(count != (res - 1))
	{
    y = rand() % h;
    x = rand() % w;
		bool flag = rand() % 2;

    if(flag == false && (y + 1 < h))
		{
			if((s.find(x * h + y) != s.find(x * h + y + 1)))
			{
				s.setunion(s.find(x * h + y), s.find(x * h + y + 1));
				maze[x][y].bottomWall = false;
        count++;
			}
		}
		else if((x + 1 < w) && flag == true)
		{
			if((s.find(x * h + y) != s.find((x + 1) * h + y)))
			{
				s.setunion(s.find(x * h + y), s.find((x + 1) * h + y));
				maze[x][y].rightWall = false;
        count++;
			}
		}
	}
	return;
}
////////////////////////////////////////////////////////////////////////////////
bool SquareMaze::canTravel(int x, int y, int dir) const
{
	//right
	if(dir == 0)
	{
    if(maze[x][y].rightWall == true)
			return false;
    else if(x == w-1)
			return false;
		else
			return true;
	}
  //left
	else if(dir == 2)
	{
		if(x == 0)
			return false;
		else if(maze[x-1][y].rightWall == true)
			return false;
		else
			return true;
	}
  //up
	else if(dir == 3)
	{
		if(maze[x][y-1].bottomWall == true)
			return false;
    else if(y == 0)
  		return false;
		else
			return true;
	}
	//down
	else if(dir == 1)
	{
		if(maze[x][y].bottomWall == true)
			return false;
    else if(y == h-1)
  		return false;
		else
			return true;
	}
	else
		return false;
}
////////////////////////////////////////////////////////////////////////////////
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
	//checks if specific wall exists or not
  if(dir == 1)
		maze[x][y].bottomWall = exists;
  else if(dir == 0)
		maze[x][y].rightWall = exists;
	return;
}
////////////////////////////////////////////////////////////////////////////////
vector<int> SquareMaze::solveMaze()
{
	//first set all maze to unvisited
	for(int i = 0; i < h; i++)
		for(int j = 0; j < w; j++)
			maze[j][i].haveVisited = false;
  vector<int> dist(w * h, 0);
  vector<int> pred(w * h, -1);
	queue <int> t;
	t.push(0);
  int front, x, y;
  maze[0][0].haveVisited = true;
	while(t.empty() == false)
	{
		front = t.front();
		t.pop();
		y = front / h;
		x = front % h;
    //case where there is a right path
    if(canTravel(x, y, 0) && maze[x+1][y].haveVisited==0)
		{
			dist[front + 1] = dist[front] + 1;
      pred[front + 1] = front;
      maze[x + 1][y].haveVisited = true;
			t.push(front + 1);
		}
    //case where there is a left path
		if(canTravel(x, y, 2) && maze[x - 1][y].haveVisited == 0)
		{
			dist[front - 1] = dist[front] + 1;
      pred[front - 1] = front;
      maze[x - 1][y].haveVisited = true;
			t.push(front - 1);
		}
    //case where there is an up path
		if(canTravel(x, y, 3) && maze[x][y - 1].haveVisited == 0)
		{
			dist[front - h] = dist[front] + 1;
      pred[front - h] = front;
      maze[x][y - 1].haveVisited = true;
			t.push(front - h);
		}
    //case where there is a down path
    if(canTravel(x, y, 1) && maze[x][y + 1].haveVisited == 0)
		{
			dist[h + front] = dist[front] + 1;
      pred[h + front] = front;
      maze[x][y + 1].haveVisited = true;
			t.push(front + h);
		}
	}
	int max = w * h - w;
	for(int i = 1; i < w; i++)
		if(dist[(w * h) - w + i] > dist[max])
			max = (w*h)- w + i; //update max
  vector<int> direction;
  int follow = max;
	while(pred[follow] != -1)
	{
    //used for checking
		y = front % h;
		//used for checking
    x = front / h;
    //left
		if(pred[follow] == follow-1)
		{
      follow = pred[follow];
      direction.insert(direction.begin(), 0);
		}
    //right
    if(pred[follow] == follow+1)
		{
      follow = pred[follow];
      direction.insert(direction.begin(), 2);
		}
    //up
		if(pred[follow] == follow - h)
		{
      follow = pred[follow];
      direction.insert(direction.begin(), 1);
		}
    //down
		if(pred[follow] == follow + h)
		{
      follow = pred[follow];
      direction.insert(direction.begin(), 3);
		}

	}
	this->max = max;
	return direction;
}
////////////////////////////////////////////////////////////////////////////////
PNG * SquareMaze::drawMaze()const
{
	PNG * t = new PNG();
	t->resize(w * 10 + 1, h * 10 + 1); //set to right size
  /*set up borders*/
  for(int i = 0; i < h * 10 + 1; i++)
	{
		(*t)(0,i)->red=0; (*t)(0,i)->green=0; (*t)(0,i)->blue=0;
	}
	for(int i = 10; i < w * 10 + 1; i++)
	{
		(*t)(i,0)->red=0; (*t)(i,0)->green=0; (*t)(i,0)->blue=0;
	}
	for(int j = 0; j < h; j++)
	{
		for(int i = 0; i < w; i++)
		{
      if(maze[i][j].bottomWall == true)
			{
				for(int c = 0; c <= 10; c++)
				{
					 (*t)(i * 10 + c, (j+1) * 10)->green = 0;
					 (*t)(i * 10 + c, (j+1) * 10)->blue = 0;
					 (*t)(i * 10 + c, (j+1) * 10)->red = 0;
				}
			}
      if(maze[i][j].rightWall == true)
			{
				for(int c = 0; c <= 10; c++) //c++ lol
				{
					 (*t)((i+1) * 10, j * 10 + c)->green = 0;
					 (*t)((i+1) * 10, j * 10 + c)->blue = 0;
					 (*t)((i+1) * 10, j * 10 + c)->red = 0;
				}
			}
		}
	}
	PNG * solution = t;
	return solution;
}
////////////////////////////////////////////////////////////////////////////////
PNG * SquareMaze::drawMazeWithSolution()
{
	PNG * solution = drawMaze();
	vector<int> path = solveMaze();
	//modify image to show path
	int y = 5;
	int x = y;
	for(size_t m =0; m < path.size(); m++)
	{
    //right
		if(path[m] == 0)
		{
			for(int i = 0; i < 11; i++)
			{ //red already set to 255
				(*solution)(x+i, y)->green = 0;
				(*solution)(x+i, y)->blue  = 0;
			}
			x += 10;
		}
    //left
		else if(path[m] == 2)
		{
			for(int i = 0; i < 11; i++)
			{ //red already set to 255
				(*solution)(x-i, y)->green = 0;
				(*solution)(x-i, y)->blue  = 0;
			}
			x -= 10;
		}
    //up
    else if(path[m] == 3)
    {
      for(int i = 0; i < 11; i++)
      { //red already set to 255
        (*solution)(x, y-i)->green = 0;
        (*solution)(x, y-i)->blue  = 0;
      }
      y -= 10;
    }
    //down
		else if(path[m] == 1)
		{
			for(int i = 0; i < 11; i++)
			{  //red already set to 255
				(*solution)(x, y+i)->green = 0;
				(*solution)(x, y+i)->blue  = 0;
			}
			y += 10;
		}
	}
	for(int i = 0; i < 9; i++)
	{
		(*solution)(x - 4 + i, y + 5)->green = 255;
		(*solution)(x - 4 + i, y + 5)->blue = 255;
		(*solution)(x - 4 + i, y + 5)->red = 255;
	}
	return solution;
}
