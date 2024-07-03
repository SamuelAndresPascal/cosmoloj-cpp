#include <math.h>
#include "unitSimpleRI.hh"

namespace unit {

      UnitConverter::UnitConverter(double scale, double offset, const IUnitConverter* inverse) : mScale(scale), mOffset(offset), mDestructInverse(false), mInverse(inverse)
      {
      }

      UnitConverter::UnitConverter(double scale, double offset) : mScale(scale), mOffset(offset), mDestructInverse(true)
      {
        mInverse = new UnitConverter(1 / mScale, -mOffset / mScale, this);
      }

      UnitConverter::~UnitConverter()
      {
        if (mDestructInverse)
        {
          delete mInverse;
        }
      }

      double UnitConverter::scale() const
      {
        return this->mScale;
      }

      double UnitConverter::offset() const
      {
        return this->mOffset;
      }

      const IUnitConverter& UnitConverter::inverse() const
      {
        return *(this->mInverse);
      }

      const IUnitConverter& UnitConverter::linear() const
      {
        // on fait volontairement ici une égalité exacte sur un double
        if (this->mOffset == 0.0)
        {
          return *this;
        }
        else
        {
          static const IUnitConverter& c = UnitConverter(this->mScale, 0.);
          return c;
        }
      }

      const IUnitConverter& UnitConverter::linearPow(const double e) const
      {
        // on fait volontairement ici une égalité exacte sur un double
        if (this->mOffset == 0.0 && e == 1.0)
        {
          return *this;
        }
        else
        {
          static const IUnitConverter& c = UnitConverter(pow(this->mScale, e), 0.);
          return c;
        }
      }

      double UnitConverter::convert(double value) const
      {
        return value * this->mScale + this->mOffset;
      }

      const IUnitConverter& UnitConverter::concatenate(const IUnitConverter& converter) const
      {
        static const IUnitConverter& c = UnitConverter(converter.scale() * this->mScale, this->convert(converter.offset()));
        return c;
      }

      const IUnitConverter& UnitConverter::of(double scale, double offset)
      {
        static const IUnitConverter& c = UnitConverter(scale, offset);
        return c;
      }
}
