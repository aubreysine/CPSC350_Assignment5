#include "Faculty.h"

Faculty::Faculty() : super(){
  m_department = "";
  m_advisees = new DoublyLinkedList<int>();
  m_numAdvisees = 0;
}

//Constructor if linked list is empty
Faculty::Faculty(int id, string name, string level, string department) : super(id,name,level){
  m_department = department;
  m_advisees = new DoublyLinkedList<int>();
  m_numAdvisees = 0;
}

Faculty::Faculty(int id, string name, string level, string department, DoublyLinkedList<int>* advisees) : super(id,name,level){
  m_department = department;
  m_advisees = advisees;
  m_numAdvisees = advisees->getSize();
}

Faculty::~Faculty(){
  delete m_advisees;
}

//Adds an advisee given id
void Faculty::addAdvisee(int id){
  m_advisees->insertBack(id);
  m_numAdvisees++;
}

//Removes an advisee given id
void Faculty::removeAdvisee(int id){
  m_advisees->remove(id);
  m_numAdvisees--;
}

//Returns a student is an advisee
bool Faculty::containsAdvisee(int id){
  return m_advisees->contains(id);
}

//Returns advisees as an array of int ids
int* Faculty::getAdvisees(){
  return m_advisees->getList();
}

//Returns number of advisees
int Faculty::getNumAdvisees(){
  return m_numAdvisees;
}

//Prints the details of the faculty
void Faculty::printDetails(){
  cout << m_id << "|" << m_name << "|" << m_level << "|" << m_department << "|";
  if(m_numAdvisees == 0){
    cout << "N/A" << endl;
  }
  int* adviseeList = m_advisees->getList();
  for(int i =0; i < m_numAdvisees; ++i){
    if(i == (m_numAdvisees - 1)){
      cout << adviseeList[i] << endl;
    }else{
      cout << adviseeList[i] << ",";
    }
  }

  delete adviseeList;
}

//Returns the details of the faculty in a string array
string* Faculty::getDetails(){
  string* out = new string[5];
  string advisees = "";

  out[0] = to_string(m_id);
  out[1] = m_name;
  out[2] = m_level;
  out[3] = m_department;

  if(m_numAdvisees == 0){
    out[4] = "N/A";
  } else{
    int* adviseeList = m_advisees->getList();
    for(int i =0; i < m_numAdvisees; ++i){
        advisees += to_string(adviseeList[i]) + ",";
    }
    out[4] = advisees;
    delete adviseeList;
  }

  return out;
}

//Helper function to print header for details of faculty
void Faculty::printHeader(){
  cout << "id|name|level|department|advisee ids" << endl;
}
