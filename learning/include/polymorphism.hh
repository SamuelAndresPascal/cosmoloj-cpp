#ifndef POLYMORPHISM_HH
#define POLYMORPHISM_HH

class IParent
{
  public:
  virtual const int getInt() const = 0;
};

class IChild : virtual public IParent
{
};


#endif // POLYMORPHISM_HH
