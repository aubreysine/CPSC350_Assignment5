#include "Student.h"

Student::Student() : super(){
  m_major = "";
  m_gpa = 0;
  m_advisor = 0;
}

Student::Student(int id, string name, string level, string major, double gpa, int advisor) : super(id, name,level){
  m_major = major;
  m_gpa = gpa;
  m_advisor = advisor;
}

Student::~Student(){}

//Returns advisor ID
int Student::getAdvisor(){
  return m_advisor;
}

//Sets advisor ID
void Student::setAdvisor(int id){
  m_advisor = id;
}

//Prints details of student
void Student::printDetails(){
  cout << m_id << "|" << m_name << "|" << m_level << "|" << m_major << "|" << m_gpa << "|" << m_advisor << endl;
}

//Returns details of student as string array
string* Student::getDetails(){
  string *out = new string[6];
  out[0] = to_string(m_id);
  out[1] = m_name;
  out[2] = m_level;
  out[3] = m_major;
  out[4] = to_string(m_gpa);
  out[5] = to_string(m_advisor);
  return out;
}

//Helper function to print a header for student information
void Student::printHeader(){
  cout << "id|name|level|major|gpa|advisor" << endl;
}
