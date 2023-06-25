#include <math.h>
#include "unitSimpleRI.hh"

namespace unit {

  Factor::Factor(const IUnit* unit, const int numerator, const int denominator) : mNumerator(numerator), mDenominator(denominator)
  {
    mUnit = unit;
  }

  const IUnit* Factor::dim() const
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
}
