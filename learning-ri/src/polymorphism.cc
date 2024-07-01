#include "polymorphismRI.hh"

const int Parent::getInt() const
{
  return 1;
}

const int Child::getInt() const
{
  return 2;
}
