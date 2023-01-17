#include <math.h>
#include "unitConverter.cc"

namespace unit {

  Unit::Unit() : Factor(this, 1, 1)
  {
  }

  const UnitConverter* Unit::affine(const Unit* source, const Unit* target)
  {
    return target->toBase()->inverse()->concatenate(source->toBase());
  }

  const UnitConverter* Unit::getConverterTo(const Unit* target) const
  {
    return affine(this, target);
  }

  const TransformedUnit* Unit::shift(const double value) const
  {
    return new TransformedUnit(UnitConverterImpl::of(1., value), this);
  }

  const TransformedUnit* Unit::scaleMultiply(const double value) const
  {
    return new TransformedUnit(UnitConverterImpl::of(value), this);
  }

  const TransformedUnit* Unit::scaleDivide(const double value) const
  {
    return scaleMultiply(1. / value);
  }

  const Factor* Unit::factor(const int numerator, const int denominator) const
  {
    return new Factor(this, numerator, denominator);
  }

  const UnitConverter* FundamentalUnit::toBase() const
  {
    return UnitConverterImpl::of(1.);
  }

  FundamentalUnit::FundamentalUnit() : Unit()
  {
  }

  TransformedUnit::TransformedUnit(const UnitConverter* toReference, const Unit* refUnit)
  {
    mToReference = toReference;
    mReference = refUnit;
  }

  const UnitConverter* TransformedUnit::toReference() const
  {
    return mToReference;
  }

  const Unit* TransformedUnit::reference() const
  {
    return mReference;
  }

  const UnitConverter* TransformedUnit::toBase() const
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

  const UnitConverter* DerivedUnit::toBase() const
  {

    const UnitConverter* transform = UnitConverterImpl::of(1.);

    for (const Factor* factor : definition())
    {
      transform = factor->dim()->toBase()->linearPow(factor->power())->concatenate(transform);
    }
    return transform;
  }
}
