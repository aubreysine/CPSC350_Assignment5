#ifndef BST_H
#define BST_H

#include "genericTreeNode.h"

template <class T>
class BST{
  public:
    BST();
    ~BST();
    TreeNode<T> *root;
    void insert(int k, T data);
    bool search(int key);
    bool deleteNode(int key);

    bool isEmpty();

    TreeNode<T>* getMin();
    TreeNode<T>* getMax();
    TreeNode<T>* getSuccessor(TreeNode<T> *d);

    void printTree(TreeNode<T> *node);
    T getValue(int key);
  private:
    void recursiveDestructor(TreeNode<T> *node);
};


template <class T>
BST<T>::BST(){
  root = NULL;
}

template <class T>
BST<T>::~BST(){
  recursiveDestructor(root);
}

//Returns whether the tree is empty
template <class T>
bool BST<T>::isEmpty(){
  return (root==NULL);
}

//Returns the node with the highest key value
template <class T>
TreeNode<T> *BST<T>::getMax(){
  TreeNode<T> *curr = root;

  if(root == NULL){
    return NULL;
  }
  while(curr->right != NULL){
    curr = curr->right;
  }
  return curr;
}

//Returns the node with the highest key value
template <class T>
TreeNode<T> *BST<T>::getMin(){
  TreeNode<T> *curr = root;

  if(root == NULL){
    return NULL;
  }
  while(curr->left != NULL){
    curr = curr->left;
  }
  return curr;
}

//Prints the tree in ascending order
template <class T>
void BST<T>::printTree(TreeNode<T> *node){
  if(node == NULL)
    return;

  printTree(node->left);
  cout << node->key << endl;
  printTree(node->right);
}

//Inserts new node into tree
template <class T>
void BST<T>::insert(int key, T val){
  TreeNode<T> *node = new TreeNode<T>(key,val);

  if(isEmpty()){
    root = node;
  }
  else{

    TreeNode<T> *curr = root; //we need to start at the root
    TreeNode<T> *parent;
    while(true){
      parent = curr;
      if(key < curr->key){
            //go left
        curr = curr->left;
        if(curr == NULL){
          parent->left = node;
        }
      }
      else{
        //go right
        curr = curr->right;
        if(curr == NULL){
          parent->right = node;
          break;
        }
      }
    }
  }
}

//Returns whether node exists in tree
template <class T>
bool BST<T>::search(int place){ //search function
  if(isEmpty()){
    return false;
  }
  else{
    TreeNode<T> *curr = root;

    while(curr->key != place){
      if(place<curr->key){
        curr = curr->left;
      }
      else{
        curr = curr->right;
      }
      if(curr == NULL){
        return false;
      }
    }

  }
  return true;
}

//Deletes node given key value
template <class T>
bool BST<T>::deleteNode(int k){ //delete node
  if(isEmpty())
    return false;

  TreeNode<T> *parent = root;
  TreeNode<T> *current = root;
  bool isLeft = true;

  while(current->key !=k){
    parent = current;
    if(k < current->key){
      isLeft = true;
      current = current->left;
    }
    else{
      isLeft = false;
      current = current->right;
    }
    if(current == NULL)
      return false;
  }

  if(current->left == NULL && current->right ==NULL){
    //Then we have a leaf treenode
    if(current == root){
      root = NULL;
    } else if(isLeft){
      parent->left = NULL;
    } else{
      parent->right = NULL;
    }
  } else if(current->right == NULL){
    if(current == root){
      root = current->left;
    }else if(isLeft){
      parent->left = current->left;
    }else{
      parent->right = current->left;
    }
  } else if(current->left == NULL){
    if(current == root){
      root = current->right;
    }else if(isLeft){
      parent->left = current->right;
    }else{
      parent->right = current->right;
    }
  } else{
    //The node to be deleted has two children
    TreeNode<T> *successor = getSuccessor(current);

    if(current ==root){
      root = successor;
    } else if(isLeft){
      parent->left = successor;
    } else{
      parent->right = successor;
    }

    //Link successor to current left child
    successor->left = current->left;
    return true;
  }
}

//Helper function for delete node
template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d) {
  //the parameter d represents the node to be deleted
  TreeNode<T> *current = d->right;
  TreeNode<T> *sp = d;
  TreeNode<T> *succesor = d;

  while (current != NULL) {
    sp =succesor;
    succesor = current;
    current = current->left;
  }

  if(succesor != d->right){
    sp->left = succesor->right;
    succesor->right = d->right;
  }

  return succesor;
}

//Returns value of node given key
template <class T>
T BST<T>::getValue(int k){
  TreeNode<T> *curr = root;
  while(curr->key != k){
    if(k<curr->key){
      curr = curr->left;
    }
    else{
      curr = curr->right;
    }
    if(curr == NULL){
      cout<<"no matching value. "<<endl;
    }
  }
  return curr->data;
}

//Allows for recursive deletion of node;
template <class T>
void BST<T>::recursiveDestructor(TreeNode<T> *node){
  if(node != NULL){
    recursiveDestructor(node->left);
    recursiveDestructor(node->right);
    delete node;
  }
}

//Creating second class to allow for pointers in the BST
template <class T>
class BST<T*>{
  public:
    BST();
    ~BST();
    TreeNode<T*> *root;
    void insert(int k, T *data);
    bool search(int key);
    bool deleteNode(int key);

    bool isEmpty();

    TreeNode<T*>* getMin();
    TreeNode<T*>* getMax();
    TreeNode<T*>* getSuccessor(TreeNode<T*> *d);


    void printTree(TreeNode<T*> *node);
    T* getValue(int k);

  private:
    void recursiveDestructor(TreeNode<T*> *node);
};


template <class T>
BST<T*>::BST(){
  root = NULL;
}

template <class T>
BST<T*>::~BST(){

}

template <class T>
bool BST<T*>::isEmpty(){
  return (root==NULL);
}

template <class T>
TreeNode<T*> *BST<T*>::getMax(){
  TreeNode<T*> *curr = root;

  if(root == NULL){
    return NULL;
  }
  while(curr->right != NULL){
    curr = curr->right;
  }
  return curr;
}

template <class T>
TreeNode<T*> *BST<T*>::getMin(){
  TreeNode<T*> *curr = root;

  if(root == NULL){
    return NULL;
  }
  while(curr->left != NULL){
    curr = curr->left;
  }
  return curr;
}

template <class T>
void BST<T*>::printTree(TreeNode<T*> *node){
  if(node == NULL)
    return;

  printTree(node->left);
  cout << node->key << endl;
  printTree(node->right);
}

template <class T>
void BST<T*>::insert(int key, T* val){
  TreeNode<T*> *node = new TreeNode<T*>(key,val);

  if(isEmpty()){
    root = node;
  }
  else{

    TreeNode<T*> *curr = root; //we need to start at the root
    TreeNode<T*> *parent;
    while(true){
      parent = curr;
      if(key < curr->key){
            //go left
        curr = curr->left;
        if(curr == NULL){
          parent->left = node;
        }
      }
      else{
        //go right
        curr = curr->right;
        if(curr == NULL){
          parent->right = node;
          break;
        }
      }
    }
  }
}

template <class T>
bool BST<T*>::search(int place){ //search function
  if(isEmpty()){
    return false;
  }
  else{
    TreeNode<T*> *curr = root;

    while(curr->key != place){
      if(place<curr->key){
        curr = curr->left;
      }
      else{
        curr = curr->right;
      }
      if(curr == NULL){
        return false;
      }
    }

  }
  return true;
}

template <class T>
bool BST<T*>::deleteNode(int k){ //delete node
  if(isEmpty())
    return false;

  TreeNode<T*> *parent = root;
  TreeNode<T*> *current = root;
  bool isLeft = true;

  while(current->key !=k){
    parent = current;
    if(k < current->key){
      isLeft = true;
      current = current->left;
    }
    else{
      isLeft = false;
      current = current->right;
    }
    if(current == NULL)
      return false;
  }

  if(current->left == NULL && current->right ==NULL){
    //Then we have a leaf treenode
    if(current == root){
      root = NULL;
    } else if(isLeft){
      parent->left = NULL;
    } else{
      parent->right = NULL;
    }
  } else if(current->right == NULL){
    if(current == root){
      root = current->left;
    }else if(isLeft){
      parent->left = current->left;
    }else{
      parent->right = current->left;
    }
  } else if(current->left == NULL){
    if(current == root){
      root = current->right;
    }else if(isLeft){
      parent->left = current->right;
    }else{
      parent->right = current->right;
    }
  } else{
    //The node to be deleted has two children
    TreeNode<T*> *successor = getSuccessor(current);

    if(current ==root){
      root = successor;
    } else if(isLeft){
      parent->left = successor;
    } else{
      parent->right = successor;
    }

    //Link successor to current left child
    successor->left = current->left;
    return true;
  }
}

template <class T>
TreeNode<T*> *BST<T*>::getSuccessor(TreeNode<T*> *d) {
  //the parameter d represents the node to be deleted
  TreeNode<T*> *current = d->right;
  TreeNode<T*> *sp = d;
  TreeNode<T*> *succesor = d;

  while (current != NULL) {
    sp =succesor;
    succesor = current;
    current = current->left;
  }

  if(succesor != d->right){
    sp->left = succesor->right;
    succesor->right = d->right;
  }

  return succesor;
}

template <class T>
T* BST<T*>::getValue(int k){
  TreeNode<T*> *curr = root;
  while(curr->key != k){
    if(k<curr->key){
      curr = curr->left;
    }
    else{
      curr = curr->right;
    }
    if(curr == NULL){
      cout<<"no matching value. "<<endl;
    }
  }
  return curr->data;
}

template <class T>
void BST<T*>::recursiveDestructor(TreeNode<T*> *node){
  if(node != NULL){
    recursiveDestructor(node->left);
    recursiveDestructor(node->right);
    delete node;
  }
}

#endif
