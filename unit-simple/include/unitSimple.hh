#ifndef UNIT_SIMPLE_HH_INCLUDED
#define UNIT_SIMPLE_HH_INCLUDED

#include <list>

using namespace std;

namespace unit
{

class IUnitConverter
{

public:
    virtual ~IUnitConverter() {}
    virtual double scale() const = 0;
    virtual double offset() const = 0;
    virtual const IUnitConverter* inverse() const = 0;
    virtual const IUnitConverter* linear() const = 0;
    virtual const IUnitConverter* linearPow(double pow) const = 0;
    virtual double convert(double value) const = 0;
    virtual const IUnitConverter* concatenate(const IUnitConverter* converter) const = 0;
};

class IUnit;

class IFactor {
  public:
    virtual ~IFactor() {}
    virtual const IUnit* dim() const = 0;
    virtual int numerator() const = 0;
    virtual int denominator() const = 0;
    virtual double power() const = 0;
};

class ITransformedUnit;

class IUnit : public IFactor {

  public:
    virtual const IUnitConverter* getConverterTo(const IUnit* target) const = 0;
    virtual const IUnitConverter* toBase() const = 0;
    virtual const ITransformedUnit* shift(double value) const = 0;
    virtual const ITransformedUnit* scaleMultiply(double value) const = 0;
    virtual const IFactor* factor(int numerator, int denominator = 1) const = 0;
    virtual const ITransformedUnit* scaleDivide(const double value) const = 0;
};

class IFundamentalUnit : public IUnit {
  public:
    virtual const IUnitConverter* toBase() const override;
};

class ITransformedUnit : public IUnit {
  public:
    virtual const IUnitConverter* toBase() const override;
    virtual const IUnitConverter* toReference() const = 0;
    virtual const IUnit* reference() const = 0;
};

class IDerivedUnit : public IUnit {
  public:
    virtual const IUnitConverter* toBase() const override;
    virtual const list<const IFactor*> definition() const = 0;
};

}


#endif // UNIT_SIMPLE_HH_INCLUDED
