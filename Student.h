#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <iostream>
using namespace std;

class Student : public Person{
  public:
    typedef Person super;

    Student();
    Student(int id, string name, string level, string major, double gpa, int advisor);
    ~Student();

    int getAdvisor();
    void setAdvisor(int id);

    void printDetails();
    string* getDetails();

    static void printHeader();
  private:
    string m_major;
    double m_gpa;
    int m_advisor;
};

#endif
