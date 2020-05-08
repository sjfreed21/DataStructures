#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>
#include <queue>


using namespace std;

void Graph::addEdge(string source, string target){
    for(unsigned int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == source){
            for(unsigned int j = 0; j < vertices.size(); j++){
                if(vertices[j]->name == target && i != j){
                    adjVertex av;
                    av.v = vertices[j];
                    vertices[i]->adj.push_back(av);
                }
            }
        }
    }
}

void Graph::addVertex(string vName){
    bool found = false;
    for(unsigned int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == vName){
            found = true;
            cout<<vertices[i]->name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex * v = new vertex;
        v->name = vName;
        vertices.push_back(v);
    }
}

void Graph::display(){
    cout<<"vertex"<<":"<<"color"<<endl;
    for(unsigned int i = 0; i < vertices.size(); i++){
        cout<<vertices[i]->name<<":"<<vertices[i]->color<<endl;

    }
}

void Graph::color(string source){
    // Based on HW8 Breadth First Traversal
    // Creation of pointer to "root" - source vertex
    vertex * root = nullptr;
    // Search for root vertex
    for(int i = 0; i < vertices.size(); i++) {
        if(vertices[i]->name == source) root = vertices[i];
    }
    // Input of correct values to root
    root->visited = true;
    root->color = "black";
    // Creation of queue to allow for BFT and initialization with root
    queue<vertex*> q;
    q.push(root);
    // Queue operation loop
    while(!q.empty()) {
        vertex * curr = q.front();
        // Scan through adjacency list and check if any adjacent vertex have been visited
        for(int x = 0; x < curr->adj.size(); x++) {
            // If so, push onto queue and adjust values
            if(!curr->adj[x].v->visited) {
                q.push(curr->adj[x].v);
                curr->adj[x].v->visited=true;
                curr->adj[x].v->dist = curr->dist + 1;
                if(curr->dist%2) curr->adj[x].v->color = "black";
                else curr->adj[x].v->color = "red";
            }
        }
        // Pop from queue to allow for next vertex to be scanned
        q.pop();
    }
    // Check for any white vertices (not yet visited)
    for(int j = 0; j < vertices.size(); j++) {
        if(!vertices[j]->visited) vertices[j]->color = "white";
    }
}
