#ifndef UNIT_SIMPLE_RI_HH_INCLUDED
#define UNIT_SIMPLE_RI_HH_INCLUDED

#include <list>
#include "unitSimple.hh"

using namespace std;

namespace unit
{

class A : virtual public IA
{
  public:
    A();
    virtual ~A() override {}
    double a2() const override;
};

class B : public A, virtual public IB
{
  public:
    B();
    virtual ~B() override {}
    virtual double a1() const override;
    virtual double b() const override;
};

class UnitConverter : public IUnitConverter {

  public:
    virtual ~UnitConverter();
    virtual double scale() const;
    virtual double offset() const;
    virtual const IUnitConverter* inverse() const;
    virtual const IUnitConverter* linear() const;
    virtual const IUnitConverter* linearPow(double pow) const;
    virtual double convert(double value) const;
    virtual const IUnitConverter* concatenate(const IUnitConverter* converter) const;
    static const UnitConverter* of(double scale, double offset = 0.);

  private:
    const double mScale;
    const double mOffset;
    const IUnitConverter* mInverse;
    const bool mDestructInverse;
    UnitConverter(double scale, double offset);
    UnitConverter(double scale, double offset, const IUnitConverter* inverse);
};

class Unit;

class Factor {
  public:
    Factor(const Unit* unit, int numerator, int denominator);
    virtual ~Factor();
    virtual const Unit* dim() const;
    virtual int numerator() const;
    virtual int denominator() const;
    virtual double power() const;

  private:
    const Unit* mUnit;
    const int mNumerator;
    const int mDenominator;
};

class TransformedUnit;

class Unit : public Factor {

  public:
    Unit();
    static const IUnitConverter* affine(const Unit* source, const Unit* target);
    virtual const IUnitConverter* getConverterTo(const Unit* target) const;
    virtual const IUnitConverter* toBase() const = 0;
    virtual const TransformedUnit* shift(double value) const;
    virtual const TransformedUnit* scaleMultiply(double value) const;
    virtual const Factor* factor(int numerator, int denominator = 1) const;
    virtual const TransformedUnit* scaleDivide(const double value) const;
};

class FundamentalUnit : public Unit {
  public:
    FundamentalUnit();
    virtual const IUnitConverter* toBase() const override;
};

class TransformedUnit : public Unit {
  public:
    TransformedUnit(const UnitConverter* toReference, const Unit* refUnit);
    virtual const IUnitConverter* toBase() const override;
    virtual const IUnitConverter* toReference() const;
    virtual const Unit* reference() const;

  private:
    const Unit* mReference;
    const UnitConverter* mToReference;
};

class DerivedUnit : public Unit {
  public:
    DerivedUnit(const list<const Factor*> definition);
    virtual const IUnitConverter* toBase() const override;
    virtual const list<const Factor*> definition() const;

  private:
    const list<const Factor*> mDefinition;
};

}
#endif /* UNIT_SIMPLE_RI_HH_INCLUDED */
