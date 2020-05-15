#include "ListNode.h"

template <class T>
class DoublyLinkedList{
  private:
    ListNode<T> *front;
    ListNode<T> *back;
    unsigned int size;
  public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insertFront(T d);
    void insertBack(T d);
    void insertAtPos(T d, int pos);

    T removeFront();
    T removeBack();
    T remove(T val);
    T removeAtPos(int pos);

    int search(T val);
    bool contains(T val);

    T getFront();
    T getData(int pos);
    unsigned int getSize();

    bool isEmpty();
    void printList();
    T* getList();
};

//Doubly Linked List implementation

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(){
  size = 0;
  front = NULL;
  back = NULL;
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList(){
  while(front->next != NULL){
    front->next->prev = NULL;

    ListNode<T> *temp = front;
    front = front->next;
    delete temp;
    size--;
  }

  delete front;
}

//Returns size of LinkedList
template <class T>
unsigned int DoublyLinkedList<T>::getSize(){
  return size;
}

//Returns front of LinkedList
template <class T>
T DoublyLinkedList<T>::getFront(){
  return front->data;
}

//returns whether LinkedList is empty
template <class T>
bool DoublyLinkedList<T>::isEmpty(){
  return (size == 0);
}

//Prints LinkedList
template <class T>
void DoublyLinkedList<T>::printList(){
  ListNode<T> *curr = front;

  while(curr != NULL){
    cout << curr->data<< endl;
    curr = curr ->next;
  }
}

//Returns LinkedList as an array
template <class T>
T* DoublyLinkedList<T>::getList(){
  T* out = new T[size];
  ListNode<T> *curr = front;

  for(int i =0; i < size; ++i){
    out[i] = curr->data;
    curr = curr ->next;
  }
  return out;
}

//Insert element at front of list
template <class T>
void DoublyLinkedList<T>::insertFront(T d){
  ListNode<T> *node = new ListNode<T>(d);

  if(isEmpty()){
    back = node;
  } else{
    front->prev = node;
    node->next = front;
  }
  front = node;
  size++;
}

//Inserts element at back of list
template <class T>
void DoublyLinkedList<T>::insertBack(T d){
  ListNode<T> *node = new ListNode<T>(d);

  if(isEmpty()){
    front = node;
  } else{
    back->next = node;
    node->prev = back;
  }
  back = node;
  size++;
}

//Inserts element at position
template <class T>
void DoublyLinkedList<T>::insertAtPos(T d, int pos){
  if(pos >= size){
    cout << "Error: Position " << pos << " exceeds list size of " << size << endl;
    return;
  }

  ListNode<T> *node = new ListNode<T>(d);
  ListNode<T> *curr = front;
  int idx = 0;

  while(idx != pos){
    curr = curr->next;
    idx++;
  }

  node->prev = curr->prev;
  curr->prev->next = node;
  curr->prev = node;
  node->next = curr;
}

//Removes front element of list
template <class T>
T DoublyLinkedList<T>::removeFront(){
  ListNode<T> *tempNode = front;

  if(front->next == NULL){
    //There is only one node in the List
    back = NULL;
  } else{
    //More than one node in the List
    front->next->prev = NULL;
  }

  front = front->next;
  tempNode->next = NULL;
  T temp = tempNode->data;
  delete tempNode;
  size--;

  return temp;
}

//Removes back element of list
template <class T>
T DoublyLinkedList<T>::removeBack(){
  ListNode<T> *tempNode = back;

  if(back->prev == NULL){
    front = NULL;
  } else{
    back->prev->next = NULL;
  }

  back = back->prev;
  tempNode->prev = NULL;
  T temp = tempNode->data;
  delete tempNode;
  size--;

  return temp;
}

//Removes element given value
template <class T>
T DoublyLinkedList<T>::remove(T val){
  ListNode<T> *curr = front;

  while(curr->data !=val){
    curr = curr->next;
    if(curr == NULL)
      return -1; //if it doesn't find it in list
  }

  if(curr == front){
    front = curr ->next;
  }
  else{
    curr->prev->next = curr->next;
  }

  if(curr == back){
    back = curr->prev;
  }else{
    curr->next->prev = curr->prev;
  }

  curr->next = NULL;
  curr->prev = NULL;
  T temp = curr->data;
  size--;
  delete curr;

  return temp;
}

//Removes element given postion in list
template <class T>
T DoublyLinkedList<T>::removeAtPos(int pos){
  if(isEmpty()){
    cout << "Error: list is empty" << endl;
    return NULL;
  } else if(pos >= size){
    cout << "Error: Position " << pos << " exceeds list size of " << size << endl;
    return NULL;
  }

  int idx = 0;
  ListNode<T> *curr = front;
  ListNode<T> *prev = front;

  while(idx != pos){
    prev = curr;
    curr = curr->next;
    idx++;
  }

  if(curr == front){
    front = curr->next;
  }
  else{
    curr->prev->next = curr->next;
  }

  if(curr == back){
    back = curr->prev;
  }else{
    curr->next->prev = curr->prev;
  }

  curr->next = NULL;
  curr->prev = NULL;
  T temp = curr->data;
  size--;
  delete curr;

  return temp;
}

//Returns postion of element given value
template <class T>
int DoublyLinkedList<T>::search(T val){
  int pos = -1;
  ListNode<T> *curr = front;

  while(curr != NULL){
    ++pos;
    if(curr->data == val){
      break;
    }
    else{
      curr = curr->next;
    }
  }

  if(curr == NULL){
    pos =-1;
  }

  return pos;
}

//Returns whether linked list contains element
template <class T>
bool DoublyLinkedList<T>::contains(T val){
  ListNode<T> *curr = front;

  while(curr != NULL){
    if(curr->data == val){
      return true;
    }
    else{
      curr = curr->next;
    }
  }

  return false;
}

//Returns element given position
template <class T>
T DoublyLinkedList<T>::getData(int pos){
  int idx = 0;
  ListNode<T> *curr = front;

  while(idx != pos){
    curr = curr->next;
    idx++;
  }

  return curr->data;
}
