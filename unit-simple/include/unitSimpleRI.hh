#ifndef UNIT_SIMPLE_RI_HH_INCLUDED
#define UNIT_SIMPLE_RI_HH_INCLUDED

#include <list>
#include "unitSimple.hh"

using namespace std;

namespace unit
{

class UnitConverter : public IUnitConverter
{

public:
    virtual double scale() const override;
    virtual double offset() const override;
    virtual const IUnitConverter* inverse() const override;
    virtual const IUnitConverter* linear() const override;
    virtual const IUnitConverter* linearPow(double pow) const override;
    virtual double convert(double value) const override;
    virtual const IUnitConverter* concatenate(const IUnitConverter* converter) const override;

    virtual ~UnitConverter() override;

    static const UnitConverter* of(double scale, double offset = 0.);

private:
    const double mScale;
    const double mOffset;
    const IUnitConverter* mInverse;
    const bool mDestructInverse;
    UnitConverter(double scale, double offset);
    UnitConverter(double scale, double offset, const IUnitConverter* inverse);
};

class Factor : public virtual IFactor
{

public:
    Factor(const IUnit* unit, int numerator, int denominator);

    virtual const IUnit* dim() const override;
    virtual int numerator() const override;
    virtual int denominator() const override;
    virtual double power() const override;

    virtual ~Factor() {}

private:
    const IUnit* mUnit;
    const int mNumerator;
    const int mDenominator;
};

class Unit : public Factor, virtual public IUnit
{

public:
    Unit();

    virtual const IUnitConverter* toBase() const = 0;

    virtual const IUnitConverter* getConverterTo(const IUnit* target) const override;
    virtual const ITransformedUnit* shift(double value) const override;
    virtual const ITransformedUnit* scaleMultiply(double value) const override;
    virtual const IFactor* factor(int numerator, int denominator = 1) const override;
    virtual const ITransformedUnit* scaleDivide(const double value) const override;

    virtual ~Unit() {}

    static const IUnitConverter* affine(const IUnit* source, const IUnit* target);
};

class FundamentalUnit : public Unit, virtual public IFundamentalUnit
{

public:
    FundamentalUnit();

    virtual const IUnitConverter* toBase() const override;

    virtual ~FundamentalUnit() {}
};

class TransformedUnit : public Unit, virtual public ITransformedUnit
{

public:
    TransformedUnit(const IUnitConverter* toReference, const IUnit* refUnit);

    virtual const IUnitConverter* toBase() const override;
    virtual const IUnitConverter* toReference() const override;
    virtual const IUnit* reference() const override;

    virtual ~TransformedUnit() {}

private:
    const IUnit* mReference;
    const IUnitConverter* mToReference;
};

class DerivedUnit : public Unit, virtual public IDerivedUnit
{

public:
    DerivedUnit(const list<const IFactor*> definition);

    virtual const IUnitConverter* toBase() const override;
    virtual const list<const IFactor*> definition() const override;

    virtual ~DerivedUnit() {}

private:
    const list<const IFactor*> mDefinition;
};

}
#endif /* UNIT_SIMPLE_RI_HH_INCLUDED */
