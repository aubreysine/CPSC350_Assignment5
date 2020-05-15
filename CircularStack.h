#ifndef CIRCULARSTACK_H
#define CIRCULARSTACK_H

using namespace std;

//Stack that removes bottom item of stack if stack is full
template <class T>
class CircularStack{
  public:
    CircularStack();
    CircularStack(int maxSize);
    ~CircularStack(); //destructor

    //core functions
    void push(T data); //insert
    void push(T* data);
    T pop(); //remove

    //aux/helper functions
    T peek(); //AKA top
    bool isEmpty();
    bool isFull();

  private:
    int top;
    int m_size;
    int numElements;

    T *myArray; //memory adress of the first block
};

template <class T>
//Default Constructor
CircularStack<T>::CircularStack(){
  myArray = new T[128];
  m_size = 128;

  numElements = 0;
  top = 0;
}

template <class T>
//Overload Constructor
CircularStack<T>::CircularStack(int maxSize){
  myArray = new T[maxSize];
  m_size = maxSize;

  numElements = 0;
  top = 0;
}

template <class T>
//Desturctor
CircularStack<T>::~CircularStack(){
  delete[] myArray;
}

template <class T>
//Adds element to top of stack
void CircularStack<T>::push(T data){
  if(top == m_size){
    //if full make start at the beginning of the array
    top = 0;
  }
  myArray[top++] = data;

  if(!isFull()){
    numElements++;
  }

}

template <class T>
//Adds element to top of stack
void CircularStack<T>::push(T* data){
  if(top == m_size){
    //if full make start at the beginning of the array
    top = 0;
  }
  myArray[top++] = *data;

  if(!isFull()){
    numElements++;
  }

}

template <class T>
//Removes element from top of stack
T CircularStack<T>::pop(){
  //check if empty before attempting to remove
  T temp;
  if(isEmpty()){
    return temp;
  } else{
    temp = myArray[--top];
  }

  if(!isEmpty() && top == 0){
    top = m_size;
  }

  numElements--;
  return temp;
}

template <class T>
//Returns top of stack
T CircularStack<T>::peek(){
  if(top == 0){
    return myArray[m_size-1];
  } else{
    return myArray[top - 1];
  }
}

template <class T>
//Checks if stack is empty
bool CircularStack<T>::isEmpty(){
  return (numElements == 0);
}

template <class T>
//Returns whether stack is full
bool CircularStack<T>::isFull(){
  return (numElements == m_size);
}
#endif
