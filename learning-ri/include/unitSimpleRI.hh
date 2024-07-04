#ifndef UNIT_SIMPLE_RI_HH
#define UNIT_SIMPLE_RI_HH

#include <list>
#include "unitSimple.hh"

namespace unit
{

class UnitConverter : public IUnitConverter
{

public:
    virtual double scale() const override;
    virtual double offset() const override;
    virtual const IUnitConverter* inverse() const override;
    virtual const IUnitConverter* linear() const override;
    virtual const IUnitConverter* linearPow(const double pow) const override;
    virtual double convert(const double value) const override;
    virtual const IUnitConverter* concatenate(const IUnitConverter& converter) const override;

    virtual ~UnitConverter() override;

    static const UnitConverter* of(const double scale, const double offset = 0.);

private:
    const double mScale;
    const double mOffset;
    const IUnitConverter* mInverse;
    const bool mDestructInverse;
    UnitConverter(const double scale, const double offset);
    UnitConverter(const double scale, const double offset, const IUnitConverter* inverse);
};

class Factor : public virtual IFactor
{

public:
    Factor(const IUnit* unit, const int numerator, const int denominator = 1);
    Factor(const IFactor* dim, const int numerator, const int denominator = 1);

    virtual const IUnit* dim() const override;
    virtual int numerator() const override;
    virtual int denominator() const override;
    virtual double power() const override;

    virtual const IDerivedUnit* operator*(const IFactor& other) const override;
    virtual const IDerivedUnit* operator/(const IFactor& other) const override;
    virtual const IDerivedUnit* operator~() const override;

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

    virtual const IUnitConverter* getConverterTo(const IUnit& target) const override;
    virtual const ITransformedUnit* shift(const double value) const override;
    virtual const ITransformedUnit* scaleMultiply(const double value) const override;
    virtual const IFactor* factor(const int numerator, const int denominator = 1) const override;
    virtual const ITransformedUnit* scaleDivide(const double value) const override;

    virtual const IDerivedUnit* operator^(const double value) const override;
    virtual const IDerivedUnit* operator*(const IFactor& other) const override;
    virtual const IDerivedUnit* operator/(const IFactor& other) const override;
    virtual const IDerivedUnit* operator~() const override;

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
    DerivedUnit(const std::list<const IFactor*> definition);

    virtual const IUnitConverter* toBase() const override;
    virtual const std::list<const IFactor*> definition() const override;

    virtual ~DerivedUnit() {}

private:
    const std::list<const IFactor*> mDefinition;
};

}
#endif /* UNIT_SIMPLE_RI_HH */
