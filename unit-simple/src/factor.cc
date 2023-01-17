#include <math.h>
#include "unit.hh"

namespace unit {

  Factor::Factor(const Unit* unit, const int numerator, const int denominator) : mNumerator(numerator), mDenominator(denominator)
  {
    mUnit = unit;
  }

  Factor::~Factor()
  {
  }

  const Unit* Factor::dim() const
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
