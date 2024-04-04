// node.cpp

#include "node.h"
#include <iostream>
#include <cstring>

using namespace std;


node::node(int tdata) {
  data = tdata;
  left =NULL;
  right = NULL;
  parent = NULL;
  color = 1;
}

node::~node() {

}

void node::setLeft(node* tleft) {
  left = tleft;
}

node* node::getLeft() {
  return left;
}

void node::setRight(node* tright) {
  right = tright;
}
node* node::getRight() {
  return right;
}

int node::getValue() {
  return data;
  
}

void node::setValue(int tdata) {
  data  =tdata;
}

int node::getColor() {
  return color;
  //0 is red, 1 is black
}

void node::setColor(int tcolor) {
  color = tcolor;
}

node* node::getParent() {
  return parent;
}

void node::setParent(node* tparent) {
  parent = tparent;
}
