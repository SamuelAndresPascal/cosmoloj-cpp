#include <math.h>
#include "unitSimpleRI.hh"

namespace unit {

  Unit::Unit() : Factor(this, 1, 1)
  {
  }

  const IUnitConverter* Unit::affine(const Unit* source, const Unit* target)
  {
    return target->toBase()->inverse()->concatenate(source->toBase());
  }

  const IUnitConverter* Unit::getConverterTo(const Unit* target) const
  {
    return affine(this, target);
  }

  const TransformedUnit* Unit::shift(const double value) const
  {
    return new TransformedUnit(UnitConverter::of(1., value), this);
  }

  const TransformedUnit* Unit::scaleMultiply(const double value) const
  {
    return new TransformedUnit(UnitConverter::of(value), this);
  }

  const TransformedUnit* Unit::scaleDivide(const double value) const
  {
    return scaleMultiply(1. / value);
  }

  const Factor* Unit::factor(const int numerator, const int denominator) const
  {
    return new Factor(this, numerator, denominator);
  }

  const IUnitConverter* FundamentalUnit::toBase() const
  {
    return UnitConverter::of(1.);
  }

  FundamentalUnit::FundamentalUnit() : Unit()
  {
  }

  TransformedUnit::TransformedUnit(const UnitConverter* toReference, const Unit* refUnit)
  {
    mToReference = toReference;
    mReference = refUnit;
  }

  const IUnitConverter* TransformedUnit::toReference() const
  {
    return mToReference;
  }

  const Unit* TransformedUnit::reference() const
  {
    return mReference;
  }

  const IUnitConverter* TransformedUnit::toBase() const
  {
    return this->reference()->toBase()->concatenate(this->toReference());
  }

  DerivedUnit::DerivedUnit(const list<const Factor*> definition) : mDefinition(definition)
  {
  }

  const list<const Factor*> DerivedUnit::definition() const
  {
    return mDefinition;
  }

  const IUnitConverter* DerivedUnit::toBase() const
  {

    const IUnitConverter* transform = UnitConverter::of(1.);

    for (const Factor* factor : definition())
    {
      transform = factor->dim()->toBase()->linearPow(factor->power())->concatenate(transform);
    }
    return transform;
  }
}
