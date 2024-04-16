#ifndef NODE_H
#define NODE_H

//node.h

#include <iostream>
#include <cstring>

using namespace std;

class node {
 public:
  node(int tdata);
  ~node();

  void setLeft(node* tleft);
  node* getLeft();

  void setRight(node* tright);
  node* getRight();

  int getValue();
  void setValue(int tadata);

  int getColor();
  void setColor(int tcolor);

  node* getParent();
  void setParent(node* tparent);

 private:
  int data;
  int color; //0 is red, 1 is black
  node* right;
  node* left;
  node* parent;
  




};
#endif
