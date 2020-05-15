#include "implementation.h"

int main(int argc, char const *argv[]) {
  Implementation* i = new Implementation();
  i->start();

  delete i;

  return 0;
}
