#ifndef POLYMORPHISM_RI_HH
#define POLYMORPHISM_RI_HH

#include "polymorphism.hh"

class Parent : public virtual IParent
{
  public:
  const int getInt() const override;
};

class Child : public Parent, public virtual IChild
{
  public:
  const int getInt() const override;
};
#endif /* POLYMORPHISM_RI_HH */
