#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using namespace std;

template <class T>
class TreeNode{
public:
  TreeNode();
  TreeNode(int key, T data);
  ~TreeNode();
  int key;
  T data;
  TreeNode *left;
  TreeNode *right;

};

template <class T>
TreeNode<T>::TreeNode(){
  key = 0;
  left = NULL;
  right = NULL;
}

template <class T>
TreeNode<T>::TreeNode(int k, T val){
  key = k;
  data = val;
  left = NULL;
  right = NULL;
}


template <class T>
TreeNode<T>::~TreeNode(){
}


//Creating second class to allow for pointers in the BST
template <class T>
class TreeNode<T*>{
public:
  TreeNode();
  TreeNode(int key, T* data);
  ~TreeNode();

  int key;
  T* data;
  TreeNode<T*> *left;
  TreeNode<T*> *right;

};

template <class T>
TreeNode<T*>::TreeNode(){
  key = 0;
  data = NULL;
  left = NULL;
  right = NULL;
}

template <class T>
TreeNode<T*>::TreeNode(int k, T* val){
  key = k;
  data = val;
  left = NULL;
  right = NULL;
}


template <class T>
TreeNode<T*>::~TreeNode(){
  delete data;
}
#endif
