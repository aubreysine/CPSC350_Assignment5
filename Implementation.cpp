#include "Implementation.h"

Implementation::Implementation(){
  ifstream inFS;
  inFS.open("schoolDatabase.txt");

  //If file exists read it in if not create new database
  if(inFS.is_open()){
    data = new Database(inFS);
  } else{
    data = new Database();
  }
  inFS.close();

  rollback = new CircularStack<string*>(5); //stores up to 5 elements
}

Implementation::~Implementation(){
  delete data;
  delete rollback;
}

void Implementation::start(){
  int choice;
  bool isRollback = false;
  string *tempRollback;

  while(true){
    int s_id, f_id;

    cout << "\nChoose an Option: " << endl;
    cout << "\t1. Display all student information" << endl;
    cout << "\t2. Display all faculty information" << endl;
    cout << "\t3. Display a student's information" << endl;
    cout << "\t4. Display a faculty's information" << endl;
    cout << "\t5. Display the information of a student's faculty advisor" << endl;
    cout << "\t6. Display the information of a faculty's advisees" << endl;
    cout << "\t7. Add a new student" << endl;
    cout << "\t8. Delete a student" << endl;
    cout << "\t9. Add a new faculty" << endl;
    cout << "\t10. Delete a faculty" << endl;
    cout << "\t11. Change a student's advisor" << endl;
    cout << "\t12. Remove one of a faculty's advisees" << endl;
    cout << "\t13. Rollback" << endl;
    cout << "\t14. Exit" << endl;
    cout << "Choice: ";
    cin >> choice;
    cout << endl;

    //If exit end program
    if(choice == 14)
      break;

    do{
      switch (choice) {
        case 1: //Print all students
        {
          Student::printHeader();
          data->printStudents();
        }break;
        case 2: //Print all faculty
        {
          Faculty::printHeader();
          data->printFaculty();
        }break;
        case 3: //Print a student's info
        {
          cout << "Enter the student's ID: ";
          cin >> s_id;

          if(!(data->containsStudent(s_id))){
            cout << "Student with ID " << s_id << " does not exist" << endl;
            break;
          } else{
            data->getStudent(s_id)->printDetails();
          }
        }break;
        case 4: //Print a faculty's info
        {
          cout << "Enter the faculty's ID: ";
          cin >> f_id;

          if(!(data->containsFaculty(f_id))){
            cout << "Faculty with ID " << f_id << " does not exist" << endl;
            break;
          }
          data->getFaculty(f_id)->printDetails();
        }break;
        case 5: //Display advisor info
        {
          cout << "Enter the student's ID: ";
          cin >> s_id;

          if(!(data->containsStudent(s_id))){
            cout << "Student with ID " << s_id << " does not exist" << endl;
            break;
          }

          if(data->getStudent(s_id)->getAdvisor() == 0){
            cout << "Student does not have an advisor yet" << endl;
          } else{
            data->getFaculty(data->getStudent(s_id)->getAdvisor())->printDetails();
          }
        }break;
        case 6: //Display advisee info
        {
          cout << "Enter the Faculty's ID: ";
          cin >> f_id;

          if(!(data->containsFaculty(f_id))){
            cout << "Faculty with ID " << f_id << " doesn't exist. Please try again." << endl;
            break;
          }

          int* adviseeList = data->getFaculty(f_id)->getAdvisees();
          int listSize = data->getFaculty(f_id)->getNumAdvisees();

          Student::printHeader();
          for(int i =0; i < listSize; ++i){
            data->getStudent(adviseeList[i])->printDetails();
          }

          delete adviseeList;
        }break;
        case 7: //Add student
        {
          int id,advisor;
          string name,level, major;
          double gpa;

          //If being called for roll back, assign variables based on the stored values
          //Else get new data for variables
          if(isRollback){
            stringstream(tempRollback[1]) >> id;
            name = tempRollback[2];
            level = tempRollback[3];
            major = tempRollback[4];
            stringstream(tempRollback[5]) >> gpa;
            stringstream(tempRollback[6]) >> advisor;
            isRollback = false;
          } else{
            tempRollback = new string[2]; //Creating array to be stored in rollback
            tempRollback[0] = "8"; //Assigning the choice slot to the opposite of add student (delete student)

            cout << "Enter the following: " << endl;
            cout << "\tStudent ID: ";
            cin >> id;
            tempRollback[1] = to_string(id); //adding neccessary parameter for delete student

            if(data->containsStudent(id)){
              cout << "Student with ID " << id << " already exists" << endl;
              break;
            }
            cout << "\tName: ";
            cin >> name;
            cout << "\tGrade Level: ";
            cin >> level;
            cout << "\tMajor: ";
            cin >> major;
            cout << "\tGPA: ";
            cin >> gpa;
            cout << "\tFaculty advisor ID (if no advisor yet enter 0): ";
            cin >> advisor;

            rollback->push(tempRollback); //adding action to rollback stack
          }

          if(advisor == 0){}
          else if(!(data->containsFaculty(advisor))){
            cout << "Faculty with ID " << advisor << " doesn't exist" << endl;
            break;
          } else{
            data->addAdvisee(advisor,id);
          }
          data->addStudent(new Student(id,name,level,major,gpa,advisor));
        }break;
        case 8: //Delete student
        {
          //If being called for roll back, assign variables based on the stored values
          //Else get new data for variables
          if(isRollback){
            stringstream(tempRollback[1]) >> s_id;
            isRollback = false;
          }else{
            cout << "Enter the student's ID: ";
            cin >> s_id;

            if(!(data->containsStudent(s_id))){
              cout << "Student with ID " << s_id << " does not exist" << endl;
              break;
            } else{
              //Copy student information to rollback
              tempRollback = new string[7];
              tempRollback[0] = "7";

              string *temp = data->getStudent(s_id)->getDetails();
              copy(temp,temp + 6, tempRollback + 1);
              rollback->push(tempRollback);
            }
          }
          data->deleteStudent(s_id);
        }break;
        case 9: //Add faculty
        {
          int id;
          string name,level, department, adviseeId, temp = "";
          DoublyLinkedList<int> *advisees = new DoublyLinkedList<int>();

          //If being called for roll back, assign variables based on the stored values
          //Else get new data for variables
          if(isRollback){
            int tempId;
            stringstream(tempRollback[1]) >> id;
            name = tempRollback[2];
            level = tempRollback[3];
            department = tempRollback[4];
            adviseeId = tempRollback[5];

            for(char i : adviseeId){
              if(i == ','){
                stringstream(temp) >> tempId;
                data->getStudent(tempId)->setAdvisor(id);
                advisees->insertBack(tempId);
                temp = "";
              } else{
                temp += i;
              }
            }
            isRollback = false;
            data->addFaculty(new Faculty(id,name,level,department, advisees));
          } else{
            tempRollback = new string[2]; //creating array to be stored as rollback array
            tempRollback[0] = "10"; //Assigning the choice slot to the opposite of add Faculty (delete faculty)

            cout << "Enter the following: " << endl;
            cout << "\tFaculty ID: ";
            cin >> id;
            if(data->containsFaculty(id)){
              cout << "Faculty with ID " << id << " already exists" << endl;
              break;
            }
            tempRollback[1] = to_string(id);

            cout << "\tName: ";
            cin >> name;
            cout << "\tTeaching Level: ";
            cin >> level;
            cout << "\tDepartment: ";
            cin >> department;
            cout << "Note: To add advisees change individual students advisors" << endl;
            data->addFaculty(new Faculty(id,name,level,department));
            rollback->push(tempRollback);
          }
        }break;
        case 10: //Delete faculty
        {
          //If being called for roll back, assign variables based on the stored values
          //Else get new data for variables
          if(isRollback){
            stringstream(tempRollback[1]) >> f_id;
            isRollback = false;
          }else{
            cout << "Enter the faculty's ID: ";
            cin >> f_id;

            if(!(data->containsFaculty(f_id))){
              cout << "Faculty with ID " << f_id << " does not exist" << endl;
              break;
            } else{
              //Copy Faculty information to rollback
              tempRollback = new string[6];
              tempRollback[0] = "9";
              string* x = data->getFaculty(f_id)->getDetails();

              copy(x, x + 5, tempRollback + 1);
              rollback->push(tempRollback);
            }
          }
          data->deleteFaculty(f_id);
        }break;
        case 11: //Change an advisor
        {
          //If being called for roll back, assign variables based on the stored values
          //Else get new data for variables
          if(isRollback){
            stringstream(tempRollback[1]) >> s_id;
            stringstream(tempRollback[2]) >> f_id;
            isRollback = false;
          }else{
            cout << "Enter the student's ID: ";
            cin >> s_id;
            if(!(data->containsStudent(s_id))){
              cout << "Student with ID " << s_id << " does not exist" << endl;
              break;
            }

            cout << "Enter ID of new faculty advisor: ";
            cin >> f_id;

            if(!(data->containsFaculty(f_id))){
              cout << "Faculty with ID " << f_id << " doesn't exist" << endl;
              break;
            }
            //Copying data to array to be stored as rollback
            tempRollback = new string[3];
            tempRollback[0] = "11";
            tempRollback[1] = to_string(s_id);
            tempRollback[2] = to_string(data->getStudent(s_id)->getAdvisor());
            rollback->push(tempRollback);
          }
          data->changeAdvisor(s_id, f_id);
        }break;
        case 12: //Remove an advisee
        {
          //If being called for roll back, assign variables based on the stored values
          //Else get new data for variables
          if(isRollback){
            stringstream(tempRollback[1]) >> f_id;
            stringstream(tempRollback[2]) >> s_id;

            cout << "F_id: " << f_id << " s_id: " << s_id << endl;
            data->changeAdvisor(s_id,f_id);
            isRollback = false;
          }else{
            cout << "Enter faculty's ID: ";
            cin >> f_id;

            if(!(data->containsFaculty(f_id))){
              cout << "Faculty with ID " << f_id << " doesn't exist" << endl;
              break;
            }

            cout << "Enter the student's ID: ";
            cin >> s_id;
            if(!(data->containsStudent(s_id))){
              cout << "Student with ID " << s_id << " does not exist" << endl;
              break;
            }
            //Copying the data and storing as rollback
            tempRollback = new string[3];
            tempRollback[0] = "12";
            tempRollback[1] = to_string(data->getStudent(s_id)->getAdvisor());
            tempRollback[2] = to_string(s_id);
            rollback->push(tempRollback);

            data->removeAdvisee(f_id, s_id);
          }

        }break;
        case 13: //RollBack
        {
          if(!rollback->isEmpty()){
            tempRollback = rollback->pop();
            stringstream(tempRollback[0]) >> choice;
            isRollback = true;
          } else{
            cout << "No previous databases stored" << endl;
          }
        }break;
        default: //Incorrect choice
          cout << choice << " was not an option. Try again" << endl;
          break;
        }
    } while(isRollback);
  }

  //Write data to file for storage
  ofstream outFS;
  outFS.open("schoolDatabase.txt");
  data->write(outFS);
  outFS.close();
}
