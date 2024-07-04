#include <math.h>
#include "unitSimpleRI.hh"

namespace unit
{

Unit::Unit() : Factor(this, 1, 1)
{
}

const IUnitConverter* Unit::affine(const IUnit* source, const IUnit* target)
{
    return target->toBase()->inverse()->concatenate(*(source->toBase()));
}

const IUnitConverter* Unit::getConverterTo(const IUnit& target) const
{
    return affine(this, &target);
}

const ITransformedUnit* Unit::shift(const double value) const
{
    return new TransformedUnit(UnitConverter::of(1., value), this);
}

const ITransformedUnit* Unit::scaleMultiply(const double value) const
{
    return new TransformedUnit(UnitConverter::of(value), this);
}

const ITransformedUnit* Unit::scaleDivide(const double value) const
{
    return scaleMultiply(1. / value);
}

const IFactor* Unit::factor(const int numerator, const int denominator) const
{
    return new Factor(this, numerator, denominator);
}

const IDerivedUnit* Unit::operator*(const IFactor& other) const
{
    return new DerivedUnit({this, &other});
}

const IDerivedUnit* Unit::operator/(const IFactor& other) const
{
    return new DerivedUnit({this, new Factor(&other, -1)});
}

const IDerivedUnit* Unit::operator^(const double value) const
{
    return new DerivedUnit({new Factor(this, value)});
}

const IDerivedUnit* Unit::operator~() const
{
    return new DerivedUnit({new Factor(this, -1)});
}

const IUnitConverter* FundamentalUnit::toBase() const
{
    return UnitConverter::of(1.);
}

FundamentalUnit::FundamentalUnit() : Unit()
{
}

TransformedUnit::TransformedUnit(const IUnitConverter* toReference, const IUnit* refUnit) : mToReference(toReference), mReference(refUnit)
{
}

const IUnitConverter* TransformedUnit::toReference() const
{
    return mToReference;
}

const IUnit* TransformedUnit::reference() const
{
    return mReference;
}

const IUnitConverter* TransformedUnit::toBase() const
{
    return this->reference()->toBase()->concatenate(*(this->toReference()));
}

DerivedUnit::DerivedUnit(const list<const IFactor*> definition) : mDefinition(definition)
{
}

const list<const IFactor*> DerivedUnit::definition() const
{
    return mDefinition;
}

const IUnitConverter* DerivedUnit::toBase() const
{

    const IUnitConverter* transform = UnitConverter::of(1.);

    for (const IFactor* factor : definition())
    {
        const IUnitConverter* oldTransform = transform;
        transform = factor->dim()->toBase()->linearPow(factor->power())->concatenate(*transform);
        delete oldTransform;
    }
    return transform;
}
}
