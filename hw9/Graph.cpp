#include "Graph.hpp"
#include <iostream>

using namespace std;

void Graph::addEdge(string v1, string v2, int num){
    if(v1 == v2) return;
    vertex * p1, * p2;
    for(int i = 0; i < vertices.size(); i++) {
        if(v1 == vertices[i]->name) p1 = vertices[i];
        if(v2 == vertices[i]->name) p2 = vertices[i];
    }
    if(p1 == p2) return;
    adjVertex adj1, adj2;
    adj1.v = p2;
    adj1.weight = num;
    p1->adj.push_back(adj1);
    adj2.v = p1;
    adj2.weight = num;
    p2->adj.push_back(adj2);
}

void Graph::addVertex(string name){
    bool exists = false;
    for(int i = 0; i < vertices.size(); i++) {
        if(name == vertices[i]->name) exists = true;
    }
    if(!exists) {
        vertex * add = new vertex;
        add->name = name;
        vertices.push_back(add);
    }
}

void Graph::displayEdges(){
    for(int i = 0; i < vertices.size(); i++) {
        cout << vertices[i]->name << " --> ";
        for(int j = 0; j < vertices[i]->adj.size(); j++) {
            cout << vertices[i]->adj[j].v->name << " (" << vertices[i]->adj[j].weight << ") ";
        }
        cout << endl;
    }
}

void dFTraversal(string sourceVertex, vector<vertex*> vertices){
    vertex * n;
    for(int i = 0; i < vertices.size(); i++) {
        if(vertices[i]->name == sourceVertex) n = vertices[i];
    }
    n->visited = true;
    cout << n->name << " -> ";
    for(int x = 0; x < n->adj.size(); x++) {
        if(!n->adj[x].v->visited) dFTraversal(n->adj[x].v->name,vertices);
    }
}

void Graph::depthFirstTraversal(string sourceVertex){
    dFTraversal(sourceVertex,vertices);
    cout << "DONE ";
}

void Graph::dijkstraTraverse(string source){
    vertex * vStart;
    for(int i = 0; i < vertices.size(); i++) {
        if(vertices[i]->name == source) vStart = vertices[i];
    }
    if(!vStart) return;
    queue<vertex *> q;
    q.push(vStart);
    while(!q.empty()) {
        vertex * curr = q.front();
        curr->visited = true;
        for(int x = 0; x < curr->adj.size(); x++) {
            int temp = curr->distance + curr->adj[x].weight;
            if(!curr->adj[x].v->distance) {
               curr->adj[x].v->distance = temp;
               q.push(curr->adj[x].v);
            }
            else if(temp < curr->adj[x].v->distance) {
               curr->adj[x].v->distance = temp;
               q.push(curr->adj[x].v);
            }
        }
    q.pop();
    }
}

void Graph::shortestPath(string start, string end){
    vertex * vDest;
    for(int i = 0; i < vertices.size(); i++) {
        if(vertices[i]->name == end) vDest = vertices[i];
    }
    vector<vertex*> path;
    dijkstraTraverse(start);
    int dist = 0;
    while(vDest) {
      for(int j = 0; j < vDest->adj.size(); j++) {
          if(vDest->adj[j].v == vDest->pred) dist += vDest->adj[j].weight;
      }
      path.insert(path.begin(),vDest);
      vDest = vDest->pred;
    }
    for(int i = 0; i < path.size(); i++) {
      cout << path[i]->name << " -> ";
    }
    cout << "DONE [" << dist << "]" << endl;
}