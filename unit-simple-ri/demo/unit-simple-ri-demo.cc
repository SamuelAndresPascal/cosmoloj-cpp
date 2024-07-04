#include <iostream>
#include "unitSimpleRI.hh"

using namespace unit;


int main(int argc, char *argv[])
{

  const IUnit* m = new FundamentalUnit();
  const ITransformedUnit* km = m->scaleMultiply(1000.);
  const ITransformedUnit* cm = m->scaleDivide(100.);

  std::cout << km->toReference().scale() << std::endl;

  const IUnitConverter* kmToCm = km->getConverterTo(*cm);

  std::cout << kmToCm->convert(10) << std::endl;

  const IUnit* s = new FundamentalUnit();
  const ITransformedUnit* h = s->scaleMultiply(3600.);
  const ITransformedUnit* min = s->scaleMultiply(60.);

  const IDerivedUnit* ms = new DerivedUnit({m, s->factor(-1)});
  const IDerivedUnit* kmh = new DerivedUnit({km, h->factor(-1)});

  const IUnitConverter* msToKmh = ms->getConverterTo(*kmh);

  std::cout << msToKmh->convert(100) << std::endl;

  std::cout << "Hello World!" << std::endl;
  return 0;
}
