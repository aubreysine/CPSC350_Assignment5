#ifndef FACULTY_H
#define FACULTY_H

#include "Person.h"
#include "DoublyLinkedList.h"

using namespace std;

class Faculty: public Person{
  public:
    typedef Person super;

    Faculty();
    Faculty(int id, string name, string level, string department);
    Faculty(int id, string name, string level, string department, DoublyLinkedList<int>* advisees);

    ~Faculty();

    void addAdvisee(int id);
    void removeAdvisee(int id);
    bool containsAdvisee(int id);

    int* getAdvisees();
    int getNumAdvisees();

    void printDetails();
    string* getDetails();

    static void printHeader();
  private:
    string m_department;
    DoublyLinkedList<int> *m_advisees; //stores advisee IDs
    int m_numAdvisees;
};
#endif
