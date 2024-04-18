// main.cpp

#include <iostream>
#include <cstring>
#include "node.h"
#include <fstream>

using namespace std;

// 0 is red, 1 is black (for node->getColor(););


void ADD(node* &root, node* &current, node* parent, node* grandparent, int data);
void PRINT(node* root, int count);
void rotateleft(node* &parent, node* &root);
void rotateright(node* &parent, node* &root);
bool SEARCH(node* root, int number);
void REMOVE(node* &root, node* current, int number);


void caseone(node* &root, node* current, node* parent, node* sibling, node* closenephew, node* distantnephew);
void casetwo(node* &root, node* current, node* parent, node* sibling, node* closenephew, node* distantnephew);
void casethree(node* &root, node* current, node* parent, node* sibling, node* closenephew, node* distantnephew);
void casefour(node* &root, node* current, node* parent, node* sibling, node* closenephew, node* distantnephew);
void casefive(node* &root, node* current, node* parent, node* sibling, node* closenephew, node* distantnephew);
void casesix(node* &root, node* current, node* parent, node* sibling, node* closenephew, node* distantnephew);

void reassign(node* &current, node* &parent, node* &sibling, node* &closenephew, node* &distantnephew);

void del(node* toDelete);


int main() {

  /*
    // testing basic stuff
  node* root = new node(24);
  root->setColor(0);
  cout << root->getColor() << endl;
  cout << root->getValue() << endl;
  */

  int quit =0;
  node* root = NULL;

  while (quit==0) {
    cout << "options are:  ADD   READ   PRINT   SEARCH   REMOVE   QUIT" << endl;
    char input[50];

    cin >> input;

    if (strcmp(input, "ADD")==0) {
      cout << "What number do you want to add?" << endl;
      int n;
      cin >> n;
      ADD(root, root, root, root, n);
    }
    else if (strcmp(input, "READ")==0) {
      cout << "what's the name of your file" << endl;
      char fileName[30];
      cin >> fileName;

      ifstream fin;
      fin.open(fileName);
      int inpt;
      while(fin>>inpt) {
	ADD(root, root, root, root, inpt);
      }
    }

    else if (strcmp(input, "PRINT")==0) {
      // print
      PRINT(root, 0);
    }

    else if (strcmp(input, "SEARCH")==0) {
      // search
      cout << "What number would you like to search for?" << endl;
      int number;
      cin >> number;
      bool exists;
      exists = SEARCH(root, number);
      if (exists==false) {
	cout << "Not found in tree." << endl;
      }
      else {
	cout << "Exists in tree." << endl;
      }
      
    }
    else if (strcmp(input, "REMOVE")==0) {
      // remove
      cout << "What number would you like to remove?" << endl;
      int number;
      cin >> number;
      REMOVE(root, root, number);
      if (root!=NULL) {
	root->setColor(1);
      }
    }

    else if (strcmp(input, "QUIT")==0) {
      quit = 1;
    }


  }
  
  return 0;
}


void ADD(node* &root, node* &current, node* parent, node* grandparent, int data) {
  
  
  // REMINDER: 0 is red, 1 is black
  
  //base cases
  if (!root) {

    // case 1, where root is empty
    root = new node(data);
    root->setParent(NULL);
    root->setColor(1);
  }

  else if (current==NULL) {

    // adding the node in 
    current = new node(data);
    current->setColor(0);
    if (current->getValue() <= parent->getValue()) {
      parent->setLeft(current);
    }
    else {
      parent->setRight(current);
     
    }
    current->setParent(parent);
    cout << data << "'s parent is: " << parent->getValue() << endl;

    //while
    node* currentNode=current;
    
    while (currentNode->getParent()->getColor()==0) {
      // if the parent is red, this violates property that current and parent can't both be red.
      // now check about if uncle is red or black



      //assigning uncle
      node* uncle = NULL;
      
      node* grandparent = currentNode->getParent()->getParent();
      node* parent = currentNode->getParent();

      if (grandparent==NULL) {
	break;
      }
      if (grandparent->getRight()==currentNode->getParent()) {
	uncle = grandparent->getLeft();
	// parent is to the right of the grandparent

	if (uncle!=NULL && uncle->getColor()==0) { // error is the else for null isn't good
	  
	  // uncle is red, case 3.1
	    
	    uncle->setColor(1);
	    parent->setColor(1);
	    parent->getParent()->setColor(0);
	    if (grandparent!=root) {
	      currentNode = grandparent;
	    }

	}
	    
	
	else if (currentNode->getValue() <= parent->getValue()) {
	  // current is to the left of parent
	  rotateright(parent, root);
	  currentNode = parent;
	}
	
	else {
	  // current is to the right of the parent.
	  rotateleft(grandparent, root);
	  grandparent->setColor(0);
	  grandparent->getParent()->setColor(1);
	  
	}

	

      }

      else {
	uncle = grandparent->getRight();
	if (uncle!=NULL && uncle->getColor()==0) {
	    uncle->setColor(1);
	    parent->setColor(1);
	    grandparent->setColor(0);
	    if (grandparent!=root) {
	      currentNode = grandparent;
	    }
	}

	else if (currentNode->getValue() <= parent->getValue()) {

	  // case 3.2.3
	  // parent is left child of g, current is left of parent
	  
	  rotateright(grandparent, root);
	  grandparent->setColor(0);
	  grandparent->getParent()->setColor(1);
	}
	
	else {
	  rotateleft(parent, root);
	  currentNode = parent;
	}
        
      }

      root->setColor(1);


        


      root->setColor(1);
    }

    // setting root color to black !
    root->setColor(1);

  }
  
  //recursive cases

  // same as binary search tree:
  else if (data <= current->getValue()) {
    node* l = current->getLeft();
    ADD(root, l,current, parent, data);
  }
  else {
    node* r = current->getRight();
    ADD(root, r, current, parent, data);
  }

  

  
  
  
  //return root;
}


void PRINT(node* root, int count) {

  
  if (root==NULL) {
    return;
  }
  if (root->getLeft()!=NULL) {
    PRINT(root->getLeft(), (count+1));
  }

  for (int b=0; b<count; b++) {
    cout << "\t";
  }

  cout << root->getValue() << "," << root->getColor() << endl;
  cout << endl;
  if (root->getRight()!=NULL) {
    PRINT(root->getRight(), (count+1));
  }



  
}


void rotateleft(node* &parent, node* & root) {
  

  
  node* up= parent->getParent();
  
  node* templeft = parent->getLeft();
  node* newparent = parent->getRight();
  node* templeftchild = NULL;
  if (parent->getRight()!=NULL) {
    templeftchild = parent->getRight()->getLeft();
  }
  //node* templeftchild = parent->getRight()->getLeft();

  if (up==NULL) {
    // this means the parent is the root
    root = newparent;
    root->setParent(NULL);
    
  }
  else if (parent->getValue() > up->getValue() ) {
    // change up->setRight()
    up->setRight(newparent);
    newparent->setParent(up);
  }
  else {
    // change up->setLeft();
    up->setLeft(newparent);
    newparent->setParent(up);
  }
  newparent->setLeft(parent);
  parent->setParent(newparent);



  

  if (templeftchild!=NULL) {
    parent->setRight(templeftchild);
    templeftchild->setParent(parent);
  }

  else {

    parent->setRight(NULL);
  }
  //  parent->setRight(NULL);
  

    
}

void rotateright(node* &parent, node* &root) {

  node* up = parent->getParent();

  node* newparent = parent->getLeft();

  node* temprightchild = newparent->getRight();
  if (up==NULL) {
    root = newparent;
    root->setParent(NULL);
    
  }

  else if (parent->getValue() > up->getValue()) {
    up->setRight(newparent);
    newparent->setParent(up);
  }
  else {
    up->setLeft(newparent);
    newparent->setParent(up);
  }


  newparent->setRight(parent);
  parent->setParent(newparent);
  if (temprightchild!=NULL) {
    parent->setLeft(temprightchild);
    temprightchild->setParent(parent);
  }

  else {
    parent->setLeft(NULL);
  }
  
}


bool SEARCH(node* root, int number) {
  // search
  if (root==NULL) {
    return false;
  }
  if (root->getValue()==number) {
    return true;
  }
  if (number < root->getValue()) {
    return(SEARCH(root->getLeft(), number));
  }
  else {
    return(SEARCH(root->getRight(), number));
  }
}


void REMOVE(node* &root, node* current, int number) {
  // Base cases:----
  if (root==NULL) {
    cout << "Empty tree." << endl;
    return;
  }
  if (SEARCH(root, number)==false) {
    cout << number << " isn't in the tree." << endl;
    return;
  }

  if (current->getValue()==number) {
    // found the node to remove.
    if (current==root && root->getRight()==NULL && root->getLeft()==NULL) {
      delete current;
      root = NULL;
      return;
    }
    // first check what the replacement would be.
    if (current->getRight()==NULL && current->getLeft()==NULL) {
      // is a leaf
      cout << "Deleting a leaf." << endl;
      if (current==root) {
	delete root;
	root = NULL;
	cout << "Tree is now empty." << endl;
      }
      if (current->getColor()==0) {
	if (current->getValue() > current->getParent()->getValue()) {
	  // child is on the right of its parent.
	  current->getParent()->setRight(NULL);
	}
	else {
	  // child is on the left of its parent.
	  current->getParent()->setLeft(NULL);
	}
	cout << "Deleting the red leaf." << endl;
	delete current;
      }
      else {
	// aww :(( time to delete black leaf

	//node* nil = new node(0);
	//nil->setColor(2);
	//cout << "Deleting the black leaf." << endl;
	//node* db = current;
	//current->setColor(2);

	node* toDelete = current;
	cout << "the blak leaf is: " << current->getValue() << endl;
	// setting variables.
	node* parent = current->getParent();
	char direction = 'a';
	node* sibling = NULL;
	node* closenephew = NULL;
	node* distantnephew = NULL;
	if (current == parent->getRight()) {
	  direction = 'r';
	  // current is to the right of the parent
	  sibling = parent->getLeft();
	  if (sibling!=NULL) {
	    closenephew = sibling->getRight();
	    distantnephew = sibling->getLeft();
	  }
	  

	  //parent->setRight(nil);
	}
	else {
	  direction = 'l';
	  sibling = parent->getRight();
	  if (sibling!=NULL) {
	    closenephew = sibling->getLeft();
	    distantnephew = sibling->getRight();
	  }

	  //parent->setLeft(nil);
	}
	//delete current;
	//current = nil;
	//node* toDelete = current;
	while (current!=root && current->getColor()>0) {
	  cout << "in the do while loop." << endl;

	  
	  
	  if (sibling!=NULL && sibling->getColor()==0) {
	    // go to case D2
	    //gotoe Case_D2;
	    casethree(root, current, parent, sibling, closenephew, distantnephew);

	    del(toDelete);
	    return;
	    reassign(current, parent, sibling, closenephew, distantnephew);
	  }

	  //reassign(current, parent, sibling, closenephew, distantnephew);
	  if (distantnephew!=NULL && distantnephew->getColor()==0) {
	    // go to case D6
	    //goto Case_D6;
	    casesix(root, current, parent, sibling, closenephew, distantnephew);
	    del(toDelete);
	    return;
	    
	  }
	  //reassign(current, parent, sibling, closenephew, distantnephew);
	  if (closenephew!=NULL && closenephew->getColor()==0) {
	    // go to case D5
	    //goto Case_D5;
	    casefive(root, current, parent, sibling, closenephew, distantnephew);
	    del(toDelete);
	    return;
	    reassign(current, parent, sibling, closenephew, distantnephew);
	  }

	  //reassign(current, parent, sibling, closenephew, distantnephew);

	  if (parent!=NULL && parent->getColor()==0) {
	    // go to case D4
	    //goto Case_D4;
	    casefour(root, current, parent, sibling, closenephew, distantnephew);

	    del(toDelete);
	    return;
	  }

	  //reassign(current, parent, sibling, closenephew, distantnephew);

	  // case d_2
	  if (sibling!=NULL) {
	    sibling->setColor(0);
	  }
	  //sibling->setColor(0);


	  
	  // assigning varibales AGAIN :(
	  current = parent;
	  parent = current->getParent();
	  if (parent==NULL) {
	    break;
	  }
	  reassign(current, parent, sibling, closenephew, distantnephew);

	  
	  
	}

	del(toDelete);
	// deleting nil ?
	//REMOVE(root, root, 0);
        cout << "[rinting" << endl;
	PRINT(root, 0);
	cout << "rinted" << endl;
      }

	
    }
    else if (current->getRight()==NULL) {
      // left child only
      cout << "setting values." << endl;
      current->setValue(current->getLeft()->getValue());
    
      delete current->getLeft();
      current->setLeft(NULL);
    }
    else if (current->getLeft()==NULL) {
      // right child only
      cout << "Setting values." << endl;
      current->setValue(current->getRight()->getValue());
      delete current->getRight();
      current->setRight(NULL);
    }

    else {
      // there are two children
      cout << "Deleting a node with two children." << endl;
      // find successor.
      
      node* s = current->getRight();
      node* sp = current;
      while (s->getLeft()!=NULL) {
	sp = s;
	s = s->getLeft();
      }
      /*
      if (sp!=current) {
	sp->setLeft(s->getRight());
      }
      else {
	sp->setRight(s->getRight());
      }
      */
      int value = s->getValue();
      cout << "Calling remove on: " << value << endl;
      PRINT(root, 0);
      REMOVE(root, root, s->getValue());
      current->setValue(value);
      if (current==root) {
	root->setValue(value);
      }
      //REMOVE(root, root, 
    }
    root->setColor(1);
    return;
  }






  //recursive cases
  if (number < current->getValue()) {
    REMOVE(root, current->getLeft(), number);
  }
  else {
    REMOVE(root, current->getRight(), number);
  }
}


void caseone(node*& root, node* current, node* parent, node* sibling, node* closenephew, node* distantnephew) {
  cout << "case one." << endl;
}

void casetwo(node* &root, node* current, node* parent, node* sibling, node* closenephew, node* distantnephew) {
  cout << "case two" << endl;
  if (sibling!=NULL) {
    sibling->setColor(0);
  }
  current = parent;
}

void casethree(node* &root, node* current, node* parent, node* sibling, node* closenephew, node* distantnephew) {
  cout << "case 3" << endl;
  // s red and p , c, and d are black
  if (current == parent->getRight()) {
    rotateright(parent, root);

  }
  else {
    rotateleft(parent, root);
  }
  parent->setColor(0);
  sibling->setColor(1);

  /*
  sibling->setValue(closenephew->getValue());
  if (current == parent->getRight()) {
    distantnephew = sibling->getLeft();
    closenephew = sibling->getRight();
  }
  else {
    distantnephew = sibling->getRight();
    closenephew = sibling->getLeft();
  }

  */
  reassign(current, parent, sibling, closenephew, distantnephew);

  if (distantnephew != NULL && distantnephew->getColor()!=2 && distantnephew->getColor()==0) {

    //reassign(current, parent, sibling, closenephew, distantnephew);
    casesix(root, current, parent, sibling, closenephew, distantnephew);
  }
  return;
  if (closenephew != NULL && closenephew->getColor()!=2 && closenephew->getColor()==0) {
    //reassign(current, parent, sibling, closenephew, distantnephew);
    casefive(root, current, parent, sibling, closenephew, distantnephew);
    return;
  }

  else {
    casefour(root, current, parent, sibling, closenephew, distantnephew);
    return;
  }

  
}

void casefour(node* &root, node* current, node* parent, node* sibling, node* closenephew, node* distantnephew) {
  cout << "case 4" << endl;
  sibling->setColor(0);
  parent->setColor(1);
  return;
}

void casefive(node* &root, node* current, node* parent, node* sibling, node* closenephew, node* distantnephew) {
  cout << "case 5" << endl;
  if (current == parent->getRight()) {
    rotateleft(sibling, root);
  }
  else {
    rotateright(sibling, root);
  }
  sibling->setColor(0);
  closenephew->setColor(1);


  reassign(current, parent, sibling, closenephew, distantnephew);
  casesix(root, current, parent, sibling, closenephew, distantnephew);
}

void casesix(node* &root, node* current, node* parent, node* sibling, node* closenephew, node* distantnephew) {
  cout << "case 6" << endl;
  if (current == parent->getRight()) {
    rotateright(parent, root);
  }
  else {
    rotateleft(parent, root);
  }
  sibling->setColor(parent->getColor());
  parent->setColor(1);
  distantnephew->setColor(1);
  return;
}


void reassign(node* &current, node* &parent, node* &sibling, node* &closenephew, node* &distantnephew) {
  if (current->getParent()!=NULL) {
    parent = current->getParent();
    if (current == parent->getRight()) {
      sibling = parent->getLeft();
      if (sibling!=NULL) {
	closenephew = sibling->getRight();
	distantnephew = sibling->getLeft();
      }
    }
    else {
      sibling = parent->getRight();
      if (sibling!=NULL) {
	closenephew = sibling->getLeft();
	distantnephew = sibling->getRight();
      }
    }
  }
  
}



void del(node* toDelete) {
  if (toDelete->getParent()!=NULL) {
    node* parent = toDelete->getParent();
    if (toDelete == parent->getRight()) {
      parent->setRight(NULL);
      delete toDelete;
    }
    else {
      parent->setLeft(NULL);
      delete toDelete;
    }
  }
}
