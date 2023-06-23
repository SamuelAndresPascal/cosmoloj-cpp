#include <math.h>
#include "unit.hh"

namespace unit {

      UnitConverter::UnitConverter(double scale, double offset, const UnitConverter* inverse) : mScale(scale), mOffset(offset)
      {
        mInverse = inverse;
      }

      UnitConverter::UnitConverter(double scale, double offset) : mScale(scale), mOffset(offset)
      {
        mInverse = new UnitConverter(1 / mScale, -mOffset / mScale, this);
      }

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
        if (this->mOffset == 0.0)
        {
          return this;
        }
        else
        {
          return new UnitConverter(this->mScale, 0.);
        }
      }

      const UnitConverter* UnitConverter::linearPow(const double e) const
      {
        // on fait volontairement ici une égalité exacte sur un double
        if (this->mOffset == 0.0 && e == 1.0)
        {
          return this;
        }
        else
        {
          return new UnitConverter(pow(this->mScale, e), 0.);
        }
      }

      double UnitConverter::convert(double value) const
      {
        return value * this->mScale + this->mOffset;
      }

      const UnitConverter* UnitConverter::concatenate(const UnitConverter* converter) const
      {
        return new UnitConverter(converter->scale() * this->mScale, this->convert(converter->offset()));
      }

      const UnitConverter* UnitConverter::of(double scale, double offset)
      {
        return new UnitConverter(scale, offset);
      }
}
