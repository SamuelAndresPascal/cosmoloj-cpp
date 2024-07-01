#include <iostream>
#include "polymorphismRI.hh"


int main(int argc, char *argv[])
{
  const Parent p;
  std::cout << p.getInt() << std::endl;

  const Child c;
  std::cout << c.getInt() << std::endl;

  std::cout << "Hello World!" << std::endl;
  return 0;
}
