#include<iostream>
#include<string>

using namespace std;

const char None =' ';

class BST;
class IterBST;

class Node{
  friend class BST;
  friend class IterBST;
  char val;
  Node* lc;
  Node* rc;
public:
  Node();
  int empty();
  void write();
};

class IterBST{
  Node** nodeStack;
  int nextNode;
  int nodeCount;
  void stackNodes(BST*);
  void stackNodesAux(Node*);
public:
  IterBST(BST&);
  ~IterBST(){delete[] nodeStack;}
  Node* getNextNode();
};

class BST{
  friend class IterBST;
  int count;
  Node* root;
  Node* tree;
  void addNodeAux(const char);
  void inorderAux(Node*);
public:
  BST();
  void addNode(const char);
  void inorder();
};


IterBST::IterBST(BST* bst){
  nodeCount = bst -> count;
  nodeStack = new Node*[nodeCount];
  nextNode = 0;
  stackNodes(bst);
  nextNode = 0;
}

void IterBST::stackNodes(BST* bst){
  stackNodesAux(bst -> root);
}

void IterBST::stackNodesAux(Node* n){
  if(n->empty())
  return;
  stackNodesAux(n -> lc);
  nodeStack[nextNode++] = n;
  stackNodesAux(n -> rc);
}

Node* IterBST::getNextNode(){
  Node* retval = nodeStack[nextNode];
  nextNode = (nextNode + 1) % nodeCount;
  return retval;
}

Node::Node(){
  lc = rc = 0;
  val = None;
}

int Node::empty(){
  return val == None;
}

void Node::write(){
  cout<<val;
  cout<<"\n";
}

BST::BST(){
  root = tree = new Node;
}

void BST::addNode(const char v){
tree = root;
addNodeAux(v);
}

void BST::addNodeAux(const char v){
  if(tree -> empty()){
    tree -> val = v;
    tree -> lc = new Node;
    tree -> rc = new Node;
  return;
  }

  if(v <= tree -> val)
  tree = tree -> lc;
  else
  tree = tree -> rc;

  addNodeAux(v);
}

void BST::inorder(){
  inorderAux(root);
}

void BST::inorderAux(Node* n){
  if(n -> empty())
  return;

  inorderAux(n -> lc);
  n -> write();
  inorderAux(n -> rc);
}

int main(){

  Node *n;
  BST bst;
  bst.addNode('K');
  bst.addNode('G');
  bst.addNode('F');
  bst.inorder();
  IterBST iter(bst*);
  n = iter.getNextNode();
  n -> write();

  return EXIT_SUCCESS;
}
