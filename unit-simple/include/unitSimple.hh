#ifndef UNIT_SIMPLE_HH_INCLUDED
#define UNIT_SIMPLE_HH_INCLUDED
namespace unit
{

class IUnitConverter
{

public:
    virtual ~IUnitConverter() {}
    virtual double scale() const = 0;
    virtual double offset() const = 0;
    virtual const IUnitConverter* inverse() const = 0;
    virtual const IUnitConverter* linear() const = 0;
    virtual const IUnitConverter* linearPow(double pow) const = 0;
    virtual double convert(double value) const = 0;
    virtual const IUnitConverter* concatenate(const IUnitConverter* converter) const = 0;
};
}


#endif // UNIT_SIMPLE_HH_INCLUDED
