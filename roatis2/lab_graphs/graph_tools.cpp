/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
using namespace std;
/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */

    vector<Vertex> v = newVVec(graph);
    markUnexplored(graph); //mark all the edfes unexplored also

    //PSUEDOCODE FROM LECTURE
    //queue q
    queue <Vertex> q;
    //setlabel(v, VISITED)
    graph.setVertexLabel(v[0], "VISITED"); //set it as visited so that we know we've been there
    //q.enqueue(v)
    q.push(v[0]); //create a queue and put the first vertex into it

    Vertex compare1 = v[0];
    Vertex compare2 = (graph.getAdjacent(compare1))[0]; //the first place we're going to cross check with
    int minEdgeWeight = graph.getEdgeWeight(compare1, compare2); //this is the only edge weight we know so it must be out min weight at first

    //while q ! empty
    while(!isEmpty(q)){ //while there are still items on the queue
      Vertex s = q.front();
      //dequeue
      vector<Vertex> adjacent = graph.getAdjacent(s); //find the adjacent vectors
      q.pop(); //store our first vertex to a var and then pop it off bc we wont need it anymore

      //for all w in adjacent vcertices
      for(size_t i = 0; i < adjacent.size(); i++){ //while there are still adjacent vectors that we have not VISITED
        //if unexplored
        if(graph.getVertexLabel(adjacent[i]) == "UNEXPLORED"){ //if there's an unexplored in there...
        //set as discoery and vsitied
        if(graph.getEdgeWeight(adjacent[i], s) < minEdgeWeight){ //if this is less than the one we set before, change it
          minEdgeWeight = graph.getEdgeWeight(adjacent[i], s);
          compare1 = s;
          compare2 = adjacent[i];
        }
          graph.setEdgeLabel(s, adjacent[i],"DISCOVERY"); //mark the edge a discovery edge
          graph.setVertexLabel(adjacent[i], "VISITED"); //and then mark the vertex as vsiited, since it is

          //q.eneueue
          q.push(adjacent[i]); //now push the said adjacent vertex to our queue so we can explore the vertecies that it is adjacent to
        }
        //if unexplored
        else if(graph.getEdgeLabel(s, adjacent[i]) == "UNEXPLORED") //if the edge is unexplored...
        {
          //set as cross
          if( graph.getEdgeWeight(adjacent[i], s) < minEdgeWeight) //obviously if this is smaller we make it the new minimum
          {
            minEdgeWeight =  graph.getEdgeWeight(adjacent[i], s);
            compare1 = s;
            compare2 = adjacent[i];
          }
          graph.setEdgeLabel(s, adjacent[i], "CROSS"); //make it a cross edfes

        }
      }
    }
    graph.setEdgeLabel(compare1, compare2, "MIN"); //since we've been adjusting the holders that tell the two verticies our minimum weight is between, we're now marking this edge with "min" label so that we know
    return minEdgeWeight; //return this value
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */

    /*label all edges as UNEXPLORED*/
    markUnexplored(graph);
    vector<Vertex> v = newVVec(graph);
    queue <Vertex> q;
    unordered_map <Vertex, Vertex> p;
    graph.setVertexLabel(start, "VISITED"); //set that to visited, because we're currently there
    q.push(start); //push the start vertex onto the queue

    while(!isEmpty(q)) //while q still has stuff on the queue
    {
      Vertex s = q.front(); //take the next in line and save it as a vertex
      vector<Vertex> adjacent = graph.getAdjacent(s); //find the adjacent vertecies(a vector of them)
      q.pop(); //pop it off the queue bc we're currently visiting it

      for(size_t i = 0; i < adjacent.size(); i++) //for every vector in the list of vertices
      {
        if(graph.getVertexLabel(adjacent[i]) == "UNEXPLORED") //if the vertex is unexplored...
        {
          pair <Vertex, Vertex> pairVertex(adjacent[i], s); //pair the current vertex and the adjacent one
          p.insert(pairVertex); //insert that pairing into our map
          q.push(adjacent[i]); //push the adjacent onto our queue so we can explore those edges
          graph.setEdgeLabel(s, adjacent[i],"DISCOVERY"); //set the vertex edge to discovery
          graph.setVertexLabel(adjacent[i], "VISITED"); //sert vertex to visited, since we are there already

        }
        else if(graph.getEdgeLabel(s, adjacent[i]) == "UNEXPLORED") //if the edge is currently unexplored
        {
          graph.setEdgeLabel(s, adjacent[i], "CROSS"); //set it to a cross edge
        }
      }
    }
    int dist = 0; //calculate the distance basically
    while(end != start)
    {
      graph.setEdgeLabel(end, p[end], "MINPATH");
      end = p[end];
      dist++;
    }
    return dist;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    /*  HOW TO DO

    Get a list of all edges in the graph and sort them by increasing weight.
Create a disjoint sets structure where each vertex is represented by a set.
Traverse the list from the start (i.e., from lightest weight to heaviest).

    Inspect the current edge. If that edge connects two vertices from different sets, union their respective sets and mark the edge as part of the MST. Otherwise there would be a cycle, so do nothing.
    Repeat this until n−1

edges have been added, where n is the number of vertices in the graph.
    */

    vector <Edge> e = graph.getEdges();
    vector <Edge>::iterator it;
    sort(e.begin(), e.end(), sort_edge); //SORT EDGES IN NON DECREASING ORDER

    vector <Vertex> v = graph.getVertices(); //collect all the vertexes into a vector
    DisjointSets setVertices;
    setVertices.addElem(v.size()); //ad an element to our disjoint set that is the amount of vectors we have


    for(size_t i = 0; i < e.size(); i++) //going through all our edges in our vector
    {
      Vertex s = e[i].source; //label our source and destination vectors
      Vertex d = e[i].dest;
      if(setVertices.find(s) == setVertices.find(d)) { //if they are in same set
        //do ntohinbg
      }
      else{
        //setVertices.find(s,d);
        setVertices.UBS(s,d);
        graph.setEdgeLabel(s, d, "MST");
      }
    }
}

bool GraphTools::sort_edge(Edge s, Edge d){
  return (s.weight < d. weight);
}

void GraphTools::markUnexplored(Graph& graph){

  vector<Edge> e = graph.getEdges(); //traverse through all edges in the vector(going to and from)
  for(size_t i = 0; i < e.size(); i++){//and set those both to unexplored
    Vertex s = e[i].source;
    Vertex d = e[i].dest;
    graph.setEdgeLabel(s, d, "UNEXPLORED");
  }
}

bool GraphTools::isEmpty(queue <Vertex> q){
  return q.empty();
}

vector<Vertex> GraphTools::newVVec(Graph & graph){
  vector <Vertex> v = graph.getVertices(); // we traverse through the graph settimg every vertex
  for(size_t i = 0; i < v.size(); i++){ //to unexplored so that we can mark it explored in the future
    graph.setVertexLabel(v[i], "UNEXPLORED"); //cant put this into helper function because we need to access the proper v later
  }
  return v;

}
