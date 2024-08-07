#include <iostream>
#include "unitSimpleRI.hh"

using namespace std;
using namespace unit;


int main(int argc, char *argv[])
{

  const IUnit* m = new FundamentalUnit();
  const ITransformedUnit* km = m->scaleMultiply(1000.);
  const ITransformedUnit* cm = m->scaleDivide(100.);

  cout << km->toReference()->scale() << endl;

  const IUnitConverter* kmToCm = km->getConverterTo(*cm);

  cout << kmToCm->convert(10) << endl;

  const IUnit* s = new FundamentalUnit();
  const ITransformedUnit* h = s->scaleMultiply(3600.);
  const ITransformedUnit* min = s->scaleMultiply(60.);

  const IDerivedUnit* ms = new DerivedUnit({m, s->factor(-1)});
  const IDerivedUnit* kmh = new DerivedUnit({km, h->factor(-1)});

  const IUnitConverter* msToKmh = ms->getConverterTo(*kmh);

  cout << msToKmh->convert(100) << endl;

  cout << "Hello World!" << endl;
  return 0;
}
