#include <math.h>
#include "unitSimpleRI.hh"

namespace unit {

  Factor::Factor(const IUnit& unit, const int numerator, const int denominator) : mNumerator(numerator), mDenominator(denominator), mUnit(unit)
  {
  }

  Factor::Factor(const IFactor& dim, const int numerator, const int denominator)
	  : mNumerator(dim.numerator() * numerator), mDenominator(dim.denominator() * denominator), mUnit(dim.dim())
  {
  }

  const IUnit& Factor::dim() const
  {
    return mUnit;
  }

  int Factor::numerator() const
  {
    return mNumerator;
  }

  int Factor::denominator() const
  {
    return mDenominator;
  }

  double Factor::power() const
  {
    return mNumerator / (double) mDenominator;
  }

  const IDerivedUnit* Factor::operator*(const IFactor& other) const
  {
    return new DerivedUnit({this, &other});
  }

  const IDerivedUnit* Factor::operator/(const IFactor& other) const
  {
    return new DerivedUnit({this, new Factor(other, -1)});
  }

  const IDerivedUnit* Factor::operator~() const
  {
    return new DerivedUnit({new Factor(*this, -1)});
  }
}
