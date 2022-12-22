#include <list>

using namespace std;

namespace unit {

class UnitConverter {

  public:
    UnitConverter(double scale, double offset);
    virtual ~UnitConverter();
    virtual double scale() const;
    virtual double offset() const;
    virtual const UnitConverter* inverse() const;
    virtual const UnitConverter* linear() const;
    virtual const UnitConverter* linearPow(double pow) const;
    virtual double convert(double value) const;
    virtual const UnitConverter* concatenate(const UnitConverter* converter) const;
    static const UnitConverter* of(double scale, double offset = 0.);
    static const UnitConverter* identity;

  private:
    UnitConverter(double scale, double offset, const UnitConverter* inverse);
    const double mScale;
    const double mOffset;
    const UnitConverter* mInverse;
};

class Unit;

class Factor {
  public:
    Factor(const Unit* unit, int numerator, int denominator);
    virtual ~Factor();
    virtual const Unit* dim() const;
    virtual int numerator() const;
    virtual int denominator() const;
    virtual double power() const;

  private:
    const Unit* mUnit;
    const int mNumerator;
    const int mDenominator;
};

class TransformedUnit;

class Unit : public Factor {

  public:
    Unit();
    static const UnitConverter* affine(const Unit* source, const Unit* target);
    virtual const UnitConverter* getConverterTo(const Unit* target) const;
    virtual const UnitConverter* toBase() const = 0;
    virtual const TransformedUnit* shift(double value) const;
    virtual const TransformedUnit* scaleMultiply(double value) const;
    virtual const Factor* factor(int numerator, int denominator = 1) const;
    virtual const TransformedUnit* scaleDivide(const double value) const;

  protected:
};

class FundamentalUnit : public Unit {
  public:
    FundamentalUnit();
    virtual const UnitConverter* toBase() const override;
};

class TransformedUnit : public Unit {
  public:
    TransformedUnit(const UnitConverter* toReference, const Unit* refUnit);
    virtual const UnitConverter* toBase() const override;
    virtual const UnitConverter* toReference() const;
    virtual const Unit* reference() const;

  private:
    const Unit* mReference;
    const UnitConverter* mToReference;
};

class DerivedUnit : public Unit {
  public:
    DerivedUnit(const list<const Factor*> definition);
    virtual const UnitConverter* toBase() const override;
    virtual const list<const Factor*> definition() const;

  private:
    const list<const Factor*> mDefinition;
};

}
