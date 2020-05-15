#ifndef PERSON_H
#define PERSON_H

#include<string>
#include<iostream>
using namespace std;

class Person{
  public:
    Person(){
      m_id = 0;
      m_name = "";
      m_level = "";
    }

    Person(int id, string name, string level){
      m_id = id;
      m_name = name;
      m_level = level;
    }

    ~Person(){}

    virtual void printDetails(){}

    //Returns id of person
    int getID(){
      return m_id;
    }
  protected:
    //Shared variables
    int m_id;
    string m_name;
    string m_level;
};

#endif
