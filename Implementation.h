#ifndef IMPLEMENATION_H
#define IMPLEMENATION_H

#include "Database.h"
#include "CircularStack.h"

class Implementation{
  public:
    Implementation();
    ~Implementation();

    void start();
  private:
    Database *data;
    CircularStack<string*>* rollback; //Stores roolback details
};
#endif
