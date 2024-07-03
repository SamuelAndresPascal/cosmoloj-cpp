#include <iostream>
#include "unitSimpleRI.hh"

using namespace std;
using namespace unit;


int main(int argc, char *argv[])
{

  const FundamentalUnit m;
  const ITransformedUnit* km = m.scaleMultiply(1000.);
  const ITransformedUnit* cm = m.scaleDivide(100.);

  const IUnitConverter& toto = km->toBase();

  const IUnitConverter& kmToCm = km->getConverterTo(cm);

  cout << kmToCm.convert(10) << endl;

  const FundamentalUnit s;
  const ITransformedUnit* h = s.scaleMultiply(3600.);
  const ITransformedUnit* min = s.scaleMultiply(60.);

  const DerivedUnit ms = DerivedUnit({&m, s.factor(-1)});
  const DerivedUnit kmh = DerivedUnit({km, h->factor(-1)});

  const IUnitConverter& msToKmh = ms.getConverterTo(&kmh);

  cout << msToKmh.convert(100) << endl;

  cout << "Hello World!" << endl;
  return 0;
}
