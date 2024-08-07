#ifndef UNIT_SIMPLE_HH
#define UNIT_SIMPLE_HH

#include <list>

namespace unit
{

class IUnitConverter
{

public:
    virtual double scale() const = 0;
    virtual double offset() const = 0;
    virtual const IUnitConverter& inverse() const = 0;
    virtual const IUnitConverter* linear() const = 0;
    virtual const IUnitConverter* linearPow(const double pow) const = 0;
    virtual double convert(const double value) const = 0;
    virtual const IUnitConverter* concatenate(const IUnitConverter& converter) const = 0;

    const IUnitConverter& operator~() const
    {
      return inverse();
    }

    virtual ~IUnitConverter() {}
};

class IUnit;
class IDerivedUnit;

class IFactor {

  public:
    virtual const IUnit& dim() const = 0;
    virtual int numerator() const = 0;
    virtual int denominator() const = 0;
    virtual double power() const = 0;

    virtual const IDerivedUnit* operator*(const IFactor& other) const = 0;
    virtual const IDerivedUnit* operator/(const IFactor& other) const = 0;
    virtual const IDerivedUnit* operator~() const = 0;

    virtual ~IFactor() {}
};

class ITransformedUnit;

class IUnit : virtual public IFactor {

  public:
    virtual const IUnitConverter* getConverterTo(const IUnit& target) const = 0;
    virtual const IUnitConverter* toBase() const = 0;
    virtual const ITransformedUnit* shift(const double value) const = 0;
    virtual const ITransformedUnit* scaleMultiply(const double value) const = 0;
    virtual const IFactor* factor(const int numerator, const int denominator = 1) const = 0;
    virtual const ITransformedUnit* scaleDivide(const double value) const = 0;

    virtual const IDerivedUnit* operator*(const IFactor& other) const = 0;
    virtual const IDerivedUnit* operator/(const IFactor& other) const = 0;
    virtual const IDerivedUnit* operator^(const double value) const = 0;
    virtual const IDerivedUnit* operator~() const = 0;

    const IUnitConverter* operator>>(const IUnit& target) const
    {
      return getConverterTo(target);
    }

    const IUnitConverter* operator<<(const IUnit& target) const
    {
      return target.getConverterTo(*this);
    }

    const ITransformedUnit* operator+(const double value) const
    {
      return shift(value);
    }

    const ITransformedUnit* operator-(const double value) const
    {
      return shift(-value);
    }

    const ITransformedUnit* operator*(const double value) const
    {
      return scaleMultiply(value);
    }

    const ITransformedUnit* operator/(const double value) const
    {
      return scaleDivide(value);
    }

    virtual ~IUnit() {}
};

class IFundamentalUnit : virtual public IUnit {

  public:
    virtual ~IFundamentalUnit() {}
};

class ITransformedUnit : virtual public IUnit {

  public:
    virtual const IUnitConverter& toReference() const = 0;
    virtual const IUnit& reference() const = 0;

    virtual ~ITransformedUnit() {}
};

class IDerivedUnit : virtual public IUnit {

public:
    virtual const std::list<const IFactor*> definition() const = 0;

    virtual ~IDerivedUnit() {}
};

}


#endif // UNIT_SIMPLE_HH
