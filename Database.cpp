#include "DataBase.h"

Database::Database(){
  sTree = new PersonBST();
  fTree = new PersonBST();
}

//Reads in stored database
Database::Database(ifstream &inFS){
  sTree = new PersonBST();
  fTree = new PersonBST();

  string fCont, temp = "";
  string *sArr = new string[6];
  string *fArr = new string[5];
  int count = 0;

  //individual person characteristics
  int s_id, f_id;
  string name, level, major, department, tempId;
  double gpa;

  //Getting student details and adding them to the student tree
  while(true){
    inFS >> fCont;

    if(fCont == "*"){
      break;
    }

    cout << fCont << endl;
    for(char c: fCont){
      if(c == '|'){
        cout << "Count: " << count << "| Temp: " << temp << endl;
        sArr[count++] = temp;
        temp = "";
      } else{
        temp += c;
      }
    }
    // cout << "here" << endl;
    stringstream(sArr[0]) >> s_id;
    name = sArr[1];
    level = sArr[2];
    major = sArr[3];
    stringstream(sArr[4]) >> gpa;
    stringstream(sArr[5]) >> f_id;

    sTree->insert(s_id, new Student(s_id, name, level, major, gpa, f_id));
    count = 0;
  }

  //getting faculty details and adding them to the faculty tree
  while(true){
    DoublyLinkedList<int> *advisees = new DoublyLinkedList<int>();

    cout << "Here" << endl;
    inFS >> fCont;

    if(inFS.eof()){
      break;
    }
    cout << fCont << endl;
    cout << count << endl;
    for(char c: fCont){
      if(c == '|'){
        cout << "Temp: " << temp << endl;
        fArr[count++] = temp;
        temp = "";
      } else{
        temp += c;
      }
    }
    stringstream(fArr[0]) >> f_id;
    name = fArr[1];
    level = fArr[2];
    department = fArr[3];
    tempId = fArr[4];

    for(char i : tempId){

      if(i == ','){
        if (temp != "N/A"){
          stringstream(temp) >> f_id;
          advisees->insertBack(f_id);
        }
        temp = "";
      } else{
        temp += i;
      }
      count = 0;
    }
  }
}

Database::~Database(){
  delete sTree;
  delete fTree;
}

//Adds student to student tree
void Database::addStudent(Student *s){
  sTree->insert(s->getID(), s);
}

//Adds faculty to faculty tree
void Database::addFaculty(Faculty *f){
  fTree->insert(f->getID(), f);
}

//Deletes student from student tree
void Database::deleteStudent(int id){
  //Removing student as an advisee if they have an advisee
  if(getStudent(id)->getAdvisor() !=0)
    (dynamic_cast<Faculty*>(fTree->getValue((dynamic_cast<Student*>(sTree->getValue(id)))->getAdvisor())))->removeAdvisee(id);
  sTree->deleteNode(id);
}

//Delete aculty from faculty tree
void Database::deleteFaculty(int id){
  int* adviseeList = getFaculty(id)->getAdvisees();
  int listSize = getFaculty(id)->getNumAdvisees();

  //Setting the students who were advisees to a null advisee
  for(int i =0; i < listSize; ++i){
    getStudent(adviseeList[i])->setAdvisor(0);
  }

  fTree->deleteNode(id);
}

//Prints students in student tree
void Database::printStudents(){
  sTree->printTree(sTree->root);
}

//Prints facuty in faculty tree
void Database::printFaculty(){
  fTree->printTree(fTree->root);
}

//Returns student given id
Student* Database::getStudent(int id){
  return (dynamic_cast<Student*> (sTree->getValue(id)));
}

//Returns faculty given id
Faculty* Database::getFaculty(int id){
  return (dynamic_cast<Faculty*> (fTree->getValue(id)));
}

//Change the advisor of a student to a given faculty
void Database::changeAdvisor(int s_id, int f_id){
  //If student has advisor, remove student as advisee
  if(((dynamic_cast<Student*>(sTree->getValue(s_id)))->getAdvisor()) != 0)
    (dynamic_cast<Faculty*>(fTree->getValue((dynamic_cast<Student*>(sTree->getValue(s_id)))->getAdvisor())))->removeAdvisee(s_id);

  //Adds student as advisee if new faculty isn't 0
  if(f_id != 0)
    (dynamic_cast<Faculty*>(fTree->getValue(f_id)))->addAdvisee(s_id);

  (dynamic_cast<Student*>(sTree->getValue(s_id)))->setAdvisor(f_id);
}

//Removes given advisee and setting stdents new advisor to 0
void Database::removeAdvisee(int f_id, int s_id){
  (dynamic_cast<Faculty*>(fTree->getValue(f_id)))->removeAdvisee(s_id); //Removing advisee from faculty advisee list
  (dynamic_cast<Student*>(sTree->getValue(s_id)))->setAdvisor(0); //Setting advisor to null
}

//Adds a given advisee to a given faculty
void Database::addAdvisee(int f_id, int s_id){
  if(!(getFaculty(f_id)->containsAdvisee(s_id))){
    (dynamic_cast<Faculty*>(fTree->getValue(f_id)))->addAdvisee(s_id);
  }
}

//Returns whether student exist in student tree
bool Database::containsStudent(int s_id){
  return sTree->search(s_id);
}

//Returns whether faculty exist in faculty tree
bool Database::containsFaculty(int f_id){
  return fTree->search(f_id);
}

//Writing to output file to store
void Database::write(ofstream &outFS){
   string sKeys= sTree->getKeys();
   string fKeys = fTree->getKeys();

   int* sKeyArr = new int[sTree->getKeyCount()];
   int* fKeyArr = new int[fTree->getKeyCount()];

   string temp, *personDetails;
   int tempKey, count = 0;

   //Converting student keys to ints and adding them to the int array
   for(char c : sKeys){
     if(c == ','){
       stringstream(temp) >> tempKey;
       sKeyArr[count++] = tempKey;
       temp = "";
     } else{
       temp += c;
     }
   }
   count = 0;

   //Converting faculty keys to ints and adding them to the int array
   for(char c : fKeys){
     if(c == ','){
       stringstream(temp) >> tempKey;
       fKeyArr[count++] = tempKey;
       temp = "";
     } else{
       temp += c;
     }
   }

   //Printing all students in nodes to output file
   for(int i = 0; i < sTree->getKeyCount(); ++i){
     if(sTree->search(sKeyArr[i])){
       personDetails = getStudent(sKeyArr[i])->getDetails();
       outFS << personDetails[0] << "|"
       <<personDetails[1] << "|"
       <<personDetails[2] << "|"
       <<personDetails[3] << "|"
       <<personDetails[4] << "|"
       <<personDetails[5] << "|\n";
     }
   }

   outFS << "*\n"; //Character in between 2 lists

  //Printing all faculty in nodes to output file
   for(int i = 0; i < fTree->getKeyCount(); ++i){
     if(fTree->search(fKeyArr[i])){
       personDetails = getFaculty(fKeyArr[i])->getDetails();
       outFS << personDetails[0] << "|"
       <<personDetails[1] << "|"
       <<personDetails[2] << "|"
       <<personDetails[3] << "|"
       <<personDetails[4] << "|\n";
     }
   }

}
