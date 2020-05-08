#include "Graph.hpp"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

void Graph::addEdge(string v1, string v2) {
    if(v1 == v2) return;
    vertex * p1, * p2;
    for(int i = 0; i < vertices.size(); i++) {
        if(v1 == vertices[i]->name) p1 = vertices[i];
        if(v2 == vertices[i]->name) p2 = vertices[i];
    }
    if(p1 == p2) return;
    adjVertex adj1, adj2;
    adj1.v = p2;
    p1->adj.push_back(adj1);
    adj2.v = p1;
    p2->adj.push_back(adj2);
}

void Graph::addVertex(string name) {
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

void Graph::displayEdges() {
    for(int i = 0; i < vertices.size(); i++) {
        cout << vertices[i]->name << " --> ";
        for(int j = 0; j < vertices[i]->adj.size(); j++) {
            cout << vertices[i]->adj[j].v->name << " ";
        }
        cout << endl;
    }
}

void Graph::breadthFirstTraverse(string sourceVertex) {
    cout<< "Starting vertex (root): " << sourceVertex << "-> ";
    vertex * root;
    for(int i = 0; i < vertices.size(); i++) {
        if(sourceVertex == vertices[i]->name) root = vertices[i];
    }
    root->visited = true;
    queue<vertex*> q;
    q.push(root);
    while(!q.empty()) {
        vertex * n = q.front();
        for(int x = 0; x < n->adj.size(); x++) {
            if(!n->adj[x].v->visited) {
                q.push(n->adj[x].v);
                n->adj[x].v->visited = true;
                n->adj[x].v->distance = n->distance + 1;
                cout << n->adj[x].v->name << "("<< n->adj[x].v->distance <<")"<< " "; 
            }
        }
        q.pop();
    }
}

void DFTraversal(vertex *n){
    n->visited = true;
    for(int x = 0; x < n->adj.size(); x++) {
        if(!n->adj[x].v->visited) DFTraversal(n->adj[x].v);
    }
}

int Graph::getConnectedComponents() {
  int components = 0;
  for(int u = 0; u < vertices.size(); u++) {
    if(!vertices[u]->visited) {
      components++;
      DFTraversal(vertices[u]);
    }
  }
  return components;
}