#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// MovieNode: node struct that will be stored in the MovieTree BST

MovieTree::MovieTree() {
  root = NULL;
}

void deleteNode(MovieNode * node) {
  if(node == NULL) return;
  deleteNode(node->left);
  deleteNode(node->right);
  delete node;
}

MovieTree::~MovieTree() {
  deleteNode(root);
}

void printHelper(MovieNode * node) {
  if(!node) return;
  printHelper(node->left);
  cout << "Movie: " << node->title << " " << node->rating << endl;
  printHelper(node->right);
  return;
}

void MovieTree::printMovieInventory()
{
  if(!root) {
    cout << "Tree is Empty. Cannot print" << endl;
  }
  printHelper(root);
}

MovieNode * addHelper(MovieNode * root, MovieNode * node) {
    if(!root) return node;
    if(root->title < node->title) {
        root->right = addHelper(root->right,node);
        return root;
    }
    if(root->title > node->title) {
        root->left = addHelper(root->left,node);
        return root;
    }
    return NULL;
}

void MovieTree::addMovieNode(int ranking, std::string title, int year, float rating)
{
    MovieNode * nn = new MovieNode(ranking,title,year,rating);
    root = addHelper(root, nn);
}

MovieNode * movieHelper(MovieNode * root, string title){
  if(!root) return NULL;
  if(root->title == title) return root;
  if(root->title < title) return movieHelper(root->right,title);
  if(root->title > title) return movieHelper(root->left,title);
  return NULL;
}

void MovieTree::findMovie(string title) {
  MovieNode * node = movieHelper(root, title);
  if(!node) {
    cout << "Movie not found." << endl;
    return;
  }
  cout << "Movie Info:" << endl;
  cout << "==================" << endl;
  cout << "Ranking:" << node->ranking << endl;
  cout << "Title  :" << node->title << endl;
  cout << "Year   :" << node->year << endl;
  cout << "rating :" << node->rating << endl;
}

void queryHelper(MovieNode * m, float rating, int year) {
  if(!m) return;
  if(m->rating > rating && m->year > year) cout << m->title << "(" << m->year << ") " << m->rating << endl;
  queryHelper(m->left,rating,year);
  queryHelper(m->right,rating,year);
}

void MovieTree::queryMovies(float rating, int year) {
  if(!root) {
    cout << "Tree is Empty. Cannot query Movies" << endl;
    return;
  }
  cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
  queryHelper(root,rating,year);
}


void ratingHelper(MovieNode * node, float * sum, int * count) {
  if(!node) return;
  *sum += node->rating;
  *count += 1;
  ratingHelper(node->left,sum,count);
  ratingHelper(node->right,sum,count);
  return;
}

void MovieTree::averageRating() {
  if(!root) {
    cout << "Average rating:0.0" << endl;
    return;
  }
  float sum = 0;
  int count = 0;
  ratingHelper(root,&sum,&count);
  cout << "Average rating:" << sum/count << endl;
}

void levelHelper(MovieNode * m, int level) {
  if(!m) return;
  if(!level) {
    cout << "Movie: " << m->title << " " << m->rating << endl;
  }
  else {
    level--;
    levelHelper(m->left,level);
    levelHelper(m->right,level);
  }
  return;
}

void MovieTree::printLevelNodes(int level) {
  if (level < 0) return;    // also if level is too big
  levelHelper(root,level);
}