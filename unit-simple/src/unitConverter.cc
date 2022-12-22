#ifndef UNIT_CONVERTER_CC_
#define UNIT_CONVERTER_CC_

#include <math.h>
#include "../include/unit.hh"

namespace unit {

  UnitConverter::UnitConverter(const double scale, const double offset, const UnitConverter* inverse) : mScale(scale), mOffset(offset)
  {
    mInverse = inverse;
  }

  UnitConverter::UnitConverter(const double scale, const double offset) : mScale(scale), mOffset(offset)
  {
    mInverse = new UnitConverter(1 / mScale, -mOffset / mScale, this);
  }

  const UnitConverter* UnitConverter::of(const double scale, const double offset)
  {
    return new UnitConverter(scale, offset);
  }

  const UnitConverter* UnitConverter::identity = UnitConverter::of(1.);

  UnitConverter::~UnitConverter()
  {
    delete mInverse;
  }

  double UnitConverter::scale() const
  {
    return this->mScale;
  }

  double UnitConverter::offset() const
  {
    return this->mOffset;
  }

  const UnitConverter* UnitConverter::inverse() const
  {
    return this->mInverse;
  }

  const UnitConverter* UnitConverter::linear() const
  {
    // on fait volontairement ici une égalité exacte sur un double
    if (this->mOffset == 0.0) {
      return this;
    } else {
      return new UnitConverter(this->mScale, 0.);
    }
  }

  const UnitConverter* UnitConverter::linearPow(const double e) const
  {
    // on fait volontairement ici une égalité exacte sur un double
    if (this->mOffset == 0.0 && e == 1.0) {
      return this;
    } else {
      return new UnitConverter(pow(this->mScale, e), 0.);
    }
  }

  double UnitConverter::convert(const double value) const
  {
    return value * this->mScale + this->mOffset;
  }

  const UnitConverter* UnitConverter::concatenate(const UnitConverter* converter) const
  {
    return new UnitConverter(converter->scale() * this->mScale, this->convert(converter->offset()));
  }
}
#endif /* UNIT_CONVERTER_CC_ */
