# Simple Unit (implémentation C++)

## Utilisation

Utilisation des unités transformées :

```cpp
#include "unit.hh"

using namespace unit;

//

const Unit* m = new FundamentalUnit();
const Unit* km = m->scaleMultiply(1000);
const Unit* cm = m->scaleDivide(100);
const UnitConverter* cmToKm = cm->getConverterTo(km);

cmToKm->convert(3); // 0.00003
cmToKm->inverse()->convert(0.00003); // 3.
```

Utilisation des unités dérivées :

```cpp
#include "unit.hh"

using namespace unit;

//

const Unit* m = new FundamentalUnit();
const Unit* km = m->scaleMultiply(1000);
const Unit* km2 = new DerivedUnit({km->factor(2)});
const Unit* cm = m->scaleDivide(100);
const Unit* cm2 = new DerivedUnit({cm->factor(2)});
const UnitConverter* km2Tocm2 = km2->getConverterTo(cm2);

km2Tocm2->convert(3); // 30000000000.
km2Tocm2->inverse()->convert(30000000000.); // 3.
```

Utilisation des unités dérivées en combinant les dimensions :

```cpp
#include "unit.hh"

using namespace unit;

//

const Unit* m = new FundamentalUnit();
const Unit* kg = new FundamentalUnit();
const Unit* g = kg->scaleDivide(1000);
const Unit* ton = kg->scaleMultiply(1000);
const Unit* gPerM2 = new DerivedUnit({g, m->factor(-2)});
const Unit* km = m->scaleMultiply(1000);
const Unit* tonPerKm2 = new DerivedUnit({ton, km->factor(-2)});
const Unit* cm = m->scaleDivide(100);
const Unit* tonPerCm2 = new DerivedUnit({ton, cm->factor(-2)});
const UnitConverter* gPerM2ToTonPerKm2 = gPerM2->getConverterTo(tonPerKm2);
const UnitConverter* gPerM2ToTonPerCm2 = gPerM2->getConverterTo(tonPerCm2);

gPerM2ToTonPerKm2->convert(1.); // 1.
gPerM2ToTonPerKm2->inverse()->convert(3.); // 3.
gPerM2ToTonPerCm2->convert(1.); // 1e-10
gPerM2ToTonPerCm2->convert(3.); // 3e-10
gPerM2ToTonPerCm2->offset(); // 0.
gPerM2ToTonPerCm2->scale(); // 1e-10
gPerM2ToTonPerCm2->inverse()->offset(); // -0.
gPerM2ToTonPerCm2->inverse()->convert(3e-10); // 3.
```

Utilisation des températures (conversions affines et linéaires) :

```cpp
#include "unit.hh"

using namespace unit;

//

const Unit* k = new FundamentalUnit();
const Unit* c = k->shift(273.15);
const UnitConverter* kToC = k->getConverterTo(c);


kToC->convert(0); // -273.15
kToC->inverse()->convert(0); // 273.15
kToC->convert(1); // -272.15
kToC->inverse()->convert(1); // 274.15
kToC->convert(2); // -271.15
kToC->inverse()->convert(2); // 275.15

// en combinaison avec d'autres unités, les conversions d'unités de températures doivent devenir linéaires
const Unit* m = new FundamentalUnit();
const Unit* cPerM = new DerivedUnit({c, m->factor(-1)});
const Unit* kPerM = new DerivedUnit({k, m->factor(-1)});
const UnitConverter* kPerMToCPerM = kPerM->getConverterTo(cPerM);
kPerMToCPerM->convert(3); // 3.
kPerMToCPerM->inverse()->convert(3); // 3.
```

Utilisation des conversions non-décimales :

```cpp
#include "unit.hh"

using namespace unit;

//

const Unit* m = new FundamentalUnit();
const Unit* km = m->scaleMultiply(1000.0);

const Unit* s = new FundamentalUnit();
const Unit* h = s->scaleMultiply(3600.0);

const Unit* ms = new DerivedUnit({m, s->factor(-1)});
const Unit* kmh = new DerivedUnit({km, h->factor(-1)});

const UnitConverter* msToKmh = ms->getConverterTo(kmh);

msToKmh->convert(100.0); // 360.0
msToKmh->inverse()->convert(18.0); // 5.0
```

## Développement

### Réinitialisation du projet, génération de la configuration CodeBlocks et du Makefile, et compilation:

```bash
cd unit-simple
rm -rf bin/ lib/ CMakeFiles/ CMakeCache.txt Makefile cmake_install.cmake
cmake . -G "CodeBlocks - Unix Makefiles"
make
```

### Tests

```bash
cd unit-simple
bin/test
```
