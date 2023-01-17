#include <math.h>
#include "unit.hh"

namespace unit {

  class UnitConverterImpl : public UnitConverter {

    public:
      UnitConverterImpl(double scale, double offset) : mScale(scale), mOffset(offset)
      {
        mInverse = new UnitConverterImpl(1 / mScale, -mOffset / mScale, this);
      }

      virtual ~UnitConverterImpl()
      {
        delete mInverse;
      }

      double scale() const
      {
        return this->mScale;
      }

      double offset() const
      {
        return this->mOffset;
      }

      const UnitConverter* inverse() const
      {
        return this->mInverse;
      }

      const UnitConverter* linear() const
      {
        // on fait volontairement ici une égalité exacte sur un double
        if (this->mOffset == 0.0)
        {
          return this;
        }
        else
        {
          return new UnitConverterImpl(this->mScale, 0.);
        }
      }

      const UnitConverter* linearPow(const double e) const
      {
        // on fait volontairement ici une égalité exacte sur un double
        if (this->mOffset == 0.0 && e == 1.0)
        {
          return this;
        }
        else
        {
          return new UnitConverterImpl(pow(this->mScale, e), 0.);
        }
      }

      double convert(double value) const
      {
        return value * this->mScale + this->mOffset;
      }

      const UnitConverter* concatenate(const UnitConverter* converter) const
      {
        return new UnitConverterImpl(converter->scale() * this->mScale, this->convert(converter->offset()));
      }

      static const UnitConverter* of(double scale, double offset = 0.)
      {
        return new UnitConverterImpl(scale, offset);
      }

    private:
      UnitConverterImpl(double scale, double offset, const UnitConverter* inverse) : mScale(scale), mOffset(offset)
      {
        mInverse = inverse;
      }
      const double mScale;
      const double mOffset;
      const UnitConverter* mInverse;
  };
}
