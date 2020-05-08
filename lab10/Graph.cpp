#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

// function to add edge between two vertices
void Graph::addEdge(int v1, int v2){

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->key == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j]->key == v2 && i != j){
                    adjVertex av;
                    av.v = vertices[j];
                    vertices[i]->adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = vertices[i];
                    vertices[j]->adj.push_back(av2);
                }
            }
        }
    }
}


// function to add a vertex to the graph
void Graph::addVertex(int n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->key == n){
            found = true;
        }
    }
    if(found == false){
        vertex * v = new vertex;
        v->key = n;
        vertices.push_back(v);
    }
}

// GOLD : function to print the path of the shortest path from src to dest vertex
// First modify the findShortestPath function to update the predecessor(pred) when updating the distance of the adjacent vertices,
// then complete the following function
void Graph::printPath(int src, int dest)
{
  // the "path" vector stores the vertices of the shortest path
  vector<vertex*> path;

  // A pointer for destination vertex
  vertex *vDest;

  for(int i = 0; i < vertices.size(); i++) {
      if(vertices[i]->key == dest) {
          vDest = vertices[i];
      }
  }

  cout<<"The shortest path is: " <<endl;

  findShortestPath(src,dest);
  while(vDest) {
      path.insert(path.begin(),vDest);
      vDest = vDest->pred;
  }

  for(int i = 0; i < path.size(); i++) {
      cout << path[i]->key << " ";
  }

  // For some reason, the code below wasn't working. This was attempting to use an array that is filled from its highest index down
  // and then printed in normal order. The findShortestPath call below would return -1, messing up the array indices, even though
  // in main.cpp it returned 2 as expected. 
  
  //   int length;
  //   length = findShortestPath(src,dest);
    
  //   cout<<"The shortest path is: " <<endl;
  
  //   int keys[length];
  //   for(int j = length-1; j > -1; j--) {
  //     keys[j] = vDest->key;
  //     vDest = vDest->pred;
  //   }

  //   for(int k = 0; k < length; k++) {
  //       cout << k << keys[k] << " ";
  //   }

  return;
}

// SILVER: Complete the following function and return the length of the shortest path (return -1 if you can't find a path)
int Graph::findShortestPath(int src, int dest){

    // Need to find the source vertex since we only have it's key 'src'
    // A pointer for source vertex
    vertex *vStart;

    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->key == src)
        {
            vStart = vertices[i];
        }
    }

    vStart->visited = true;

    // Use the queue to keep track of visited vertices
    queue<vertex*> q;

    // Enqueue the source vertex
    q.push(vStart);

    vertex *n;

    // standard BFS
    while(!q.empty()){
        n = q.front();
        q.pop();

        // go to all the adjacent vertices of n
        for( int x = 0; x < n->adj.size(); x++ )
        {
            // If a adjacent has not been visited, then mark it visited and enqueue it
            // Update the distance of the adjacent vertices along the way
            // Stop when you reach the destination vertex and return the needful
            if(!n->adj[x].v->visited) {
                q.push(n->adj[x].v);
                n->adj[x].v->pred = n;
                n->adj[x].v->visited = true;
                n->adj[x].v->distance = n->distance + 1;
            }
            if(n->adj[x].v->key == dest) {
                return n->adj[x].v->distance;
            }
        }
    }

    return -1;

}
