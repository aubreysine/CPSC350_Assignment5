#ifndef PERSONBST_H
#define PERSONBST_H

#include "genericBST.h"
#include "Person.h"
#include <typeinfo>

//Specific class for a person BST to alllow for direct access of person functions
class PersonBST : public BST<Person*>{
  public:
    PersonBST(): BST<Person*>(){
      keys = "";
      keyCount = 0;
    }
    ~PersonBST(){}

    //Prints the tree using information from people class
    void printTree(TreeNode<Person*> *node){
      if(node == NULL)
        return;

      printTree(node->left);
      node->data->printDetails();
      printTree(node->right);
    }

    //Inserts into tree and also adds the key to the list
    void insert(int key, Person* val){
      TreeNode<Person*> *node = new TreeNode<Person*>(key,val);

      if(isEmpty()){
        root = node;
      }
      else{

        TreeNode<Person*> *curr = root; //we need to start at the root
        TreeNode<Person*> *parent;
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
      keys += to_string(key) + ",";
      keyCount++;
    }

    //Returns keys as string seperated by commas
    string getKeys(){
      return keys;
    }

    //Returns key count
    int getKeyCount(){
      return keyCount;
    }

  private:
    string keys;
    int keyCount;

};
#endif
