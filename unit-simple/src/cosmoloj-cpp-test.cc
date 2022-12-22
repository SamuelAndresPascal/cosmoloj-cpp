#include <iostream>
#include "../include/unit.hh"

using namespace std;
using namespace unit;


int main(int argc, char *argv[])
{

  const Unit* m = new FundamentalUnit();
  const TransformedUnit* km = m->scaleMultiply(1000.);
  const TransformedUnit* cm = m->scaleDivide(100.);

  cout << km->toReference()->scale() << endl;

  const UnitConverter* kmToCm = km->getConverterTo(cm);

  cout << kmToCm->convert(10) << endl;

  const Unit* s = new FundamentalUnit();
  const TransformedUnit* h = s->scaleMultiply(3600.);
  const TransformedUnit* min = s->scaleMultiply(60.);

  const DerivedUnit* ms = new DerivedUnit({m, s->factor(-1)});
  const DerivedUnit* kmh = new DerivedUnit({km, h->factor(-1)});

  const UnitConverter* msToKmh = ms->getConverterTo(kmh);

  cout << msToKmh->convert(100) << endl;

  cout << "Hello World!" << endl;
  return 0;
}
