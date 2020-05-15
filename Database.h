#ifndef DATABASE_H
#define DATABASE_H

#include "PersonBST.h"
#include "Student.h"
#include "Faculty.h"

#include <fstream>
#include <sstream>

class Database{
  public:
    Database();
    Database(ifstream &inFS);
    ~Database();

    void addStudent(Student *s);
    void addFaculty(Faculty *f);

    void deleteStudent(int id);
    void deleteFaculty(int id);

    void printStudents();
    void printFaculty();

    Student* getStudent(int id);
    Faculty* getFaculty(int id);

    void changeAdvisor(int s_id, int f_id);
    void removeAdvisee(int f_id, int s_id);
    void addAdvisee(int f_id, int s_id);

    bool containsStudent(int s_id);
    bool containsFaculty(int f_id);

    void write(ofstream &outFS);
  private:
    PersonBST *sTree; //Student Tree
    PersonBST *fTree; //Faculty Tree
};

#endif
