# Simple Unit (implémentation C++)

## Utilisation standard

Utilisation des unités transformées :

```cpp
#include "unitSimpleRI.hh"

using namespace unit;

//

const IUnit* m = new FundamentalUnit();
const IUnit* km = m->scaleMultiply(1000);
const IUnit* cm = m->scaleDivide(100);
const IUnitConverter* cmToKm = cm->getConverterTo(km);

cmToKm->convert(3); // 0.00003
cmToKm->inverse()->convert(0.00003); // 3.

delete cmToKm;
delete cm;
delete km;
delete m;
```

Utilisation des unités dérivées :

```cpp
#include "unitSimpleRI.hh"

using namespace unit;

//

const IUnit* m = new FundamentalUnit();
const IUnit* km = m->scaleMultiply(1000);
const IUnit* km2 = new DerivedUnit({km->factor(2)});
const IUnit* cm = m->scaleDivide(100);
const IUnit* cm2 = new DerivedUnit({cm->factor(2)});
const IUnitConverter* km2Tocm2 = km2->getConverterTo(cm2);

km2Tocm2->convert(3); // 30000000000.
km2Tocm2->inverse()->convert(30000000000.); // 3.

delete km2Tocm2;
delete cm2;
delete cm;
delete km2;
delete km;
delete m;
```

Utilisation des unités dérivées en combinant les dimensions :

```cpp
#include "unitSimpleRI.hh"

using namespace unit;

//

const IUnit* m = new FundamentalUnit();
const IUnit* kg = new FundamentalUnit();
const IUnit* g = kg->scaleDivide(1000);
const IUnit* ton = kg->scaleMultiply(1000);
const IUnit* gPerM2 = new DerivedUnit({g, m->factor(-2)});
const IUnit* km = m->scaleMultiply(1000);
const IUnit* tonPerKm2 = new DerivedUnit({ton, km->factor(-2)});
const IUnit* cm = m->scaleDivide(100);
const IUnit* tonPerCm2 = new DerivedUnit({ton, cm->factor(-2)});
const IUnitConverter* gPerM2ToTonPerKm2 = gPerM2->getConverterTo(tonPerKm2);
const IUnitConverter* gPerM2ToTonPerCm2 = gPerM2->getConverterTo(tonPerCm2);

gPerM2ToTonPerKm2->convert(1.); // 1.
gPerM2ToTonPerKm2->inverse()->convert(3.); // 3.
gPerM2ToTonPerCm2->convert(1.); // 1e-10
gPerM2ToTonPerCm2->convert(3.); // 3e-10
gPerM2ToTonPerCm2->offset(); // 0.
gPerM2ToTonPerCm2->scale(); // 1e-10
gPerM2ToTonPerCm2->inverse()->offset(); // -0.
gPerM2ToTonPerCm2->inverse()->convert(3e-10); // 3.

delete gPerM2ToTonPerCm2;
delete gPerM2ToTonPerKm2;
delete tonPerCm2;
delete cm;
delete tonPerKm2;
delete km;
delete gPerM2;
delete ton;
delete g;
delete kg;
delete m;
```

Utilisation des températures (conversions affines et linéaires) :

```cpp
#include "unitSimpleRI.hh"

using namespace unit;

//

const IUnit* k = new FundamentalUnit();
const IUnit* c = k->shift(273.15);
const IUnitConverter* kToC = k->getConverterTo(c);


kToC->convert(0); // -273.15
kToC->inverse()->convert(0); // 273.15
kToC->convert(1); // -272.15
kToC->inverse()->convert(1); // 274.15
kToC->convert(2); // -271.15
kToC->inverse()->convert(2); // 275.15

// en combinaison avec d'autres unités, les conversions d'unités de températures doivent devenir linéaires
const IUnit* m = new FundamentalUnit();
const IUnit* cPerM = new DerivedUnit({c, m->factor(-1)});
const IUnit* kPerM = new DerivedUnit({k, m->factor(-1)});
const IUnitConverter* kPerMToCPerM = kPerM->getConverterTo(cPerM);
kPerMToCPerM->convert(3); // 3.
kPerMToCPerM->inverse()->convert(3); // 3.

delete kPerMToCPerM;
delete kPerM;
delete cPerM;
delete m;
delete kToC;
delete c;
delete k;
```

Utilisation des conversions non-décimales :

```cpp
#include "unitSimpleRI.hh"

using namespace unit;

//

const IUnit* m = new FundamentalUnit();
const IUnit* km = m->scaleMultiply(1000.0);

const IUnit* s = new FundamentalUnit();
const IUnit* h = s->scaleMultiply(3600.0);

const IUnit* ms = new DerivedUnit({m, s->factor(-1)});
const IUnit* kmh = new DerivedUnit({km, h->factor(-1)});

const IUnitConverter* msToKmh = ms->getConverterTo(kmh);

msToKmh->convert(100.0); // 360.0
msToKmh->inverse()->convert(18.0); // 5.0

delete msToKmh;
delete kmh;
delete ms;
delete h;
delete s;
delete km;
delete m;
```


## Utilisation avec surcharche des opérateurs

Utilisation des unités transformées :

```cpp
#include "unitSimpleRI.hh"

using namespace unit;

//

const IUnit* m = new FundamentalUnit();
const IUnit* km = *m * 1000;
const IUnit* cm = *m / 100;
const IUnitConverter* cmToKm = *cm >> *km;

cmToKm->convert(3); // 0.00003
~(*cmToKm)->convert(0.00003); // 3.

delete cmToKm;
delete cm;
delete km;
delete m;
```

Utilisation des unités dérivées :

```cpp
#include "unitSimpleRI.hh"

using namespace unit;

//

const IUnit* m = new FundamentalUnit();
const IUnit* km = *m * 1000;
const IUnit* km2 = new DerivedUnit({*km ^ 2});
const IUnit* cm = *m / 100;
const IUnit* cm2 = new DerivedUnit({*cm ^ 2});
const IUnitConverter* km2Tocm2 = *km2 >> *cm2;

km2Tocm2->convert(3); // 30000000000.
km2Tocm2->inverse()->convert(30000000000.); // 3.

delete km2Tocm2;
delete cm2;
delete cm;
delete km2;
delete km;
delete m;
```

Utilisation des unités dérivées en combinant les dimensions :

```cpp
#include "unitSimpleRI.hh"

using namespace unit;

//

const IUnit* m = new FundamentalUnit();
const IUnit* kg = new FundamentalUnit();
const IUnit* g = *kg / 1000;
const IUnit* ton = *kg * 1000;
const IUnit* gPerM2 = new DerivedUnit({g, *m ^ -2});
const IUnit* km = *m * 1000;
const IUnit* tonPerKm2 = new DerivedUnit({ton, *km ^ -2});
const IUnit* cm = *m / 100;
const IUnit* tonPerCm2 = new DerivedUnit({ton, *cm ^ -2});
const IUnitConverter* gPerM2ToTonPerKm2 = *gPerM2 >> *tonPerKm2);
const IUnitConverter* gPerM2ToTonPerCm2 = *tonPerCm2 << *gPerM2;

gPerM2ToTonPerKm2->convert(1.); // 1.
~(*gPerM2ToTonPerKm2)->convert(3.); // 3.
gPerM2ToTonPerCm2->convert(1.); // 1e-10
gPerM2ToTonPerCm2->convert(3.); // 3e-10
gPerM2ToTonPerCm2->offset(); // 0.
gPerM2ToTonPerCm2->scale(); // 1e-10
~(*gPerM2ToTonPerCm2)->offset(); // -0.
~(*gPerM2ToTonPerCm2)->convert(3e-10); // 3.

delete gPerM2ToTonPerCm2;
delete gPerM2ToTonPerKm2;
delete tonPerCm2;
delete cm;
delete tonPerKm2;
delete km;
delete gPerM2;
delete ton;
delete g;
delete kg;
delete m;
```

Utilisation des températures (conversions affines et linéaires) :

```cpp
#include "unitSimpleRI.hh"

using namespace unit;

//

const IUnit* k = new FundamentalUnit();
const IUnit* c = *k + 273.15;
const IUnitConverter* kToC = *k >> *c;


kToC->convert(0); // -273.15
~(*kToC)->convert(0); // 273.15
kToC->convert(1); // -272.15
~(*kToC)->convert(1); // 274.15
kToC->convert(2); // -271.15
~(*kToC)->convert(2); // 275.15

// en combinaison avec d'autres unités, les conversions d'unités de températures doivent devenir linéaires
const IUnit* m = new FundamentalUnit();
const IUnit* cPerM = new DerivedUnit({c, *m ^ -1});
const IUnit* kPerM = new DerivedUnit({k, *m ^ -1});
const IUnitConverter* kPerMToCPerM = *kPerM >> *cPerM;
kPerMToCPerM->convert(3); // 3.
~(*kPerMToCPerM)->convert(3); // 3.

delete kPerMToCPerM;
delete kPerM;
delete cPerM;
delete m;
delete kToC;
delete c;
delete k;
```

Utilisation des conversions non-décimales :

```cpp
#include "unitSimpleRI.hh"

using namespace unit;

//

const IUnit* m = new FundamentalUnit();
const IUnit* km = *m * 1000.0;

const IUnit* s = new FundamentalUnit();
const IUnit* h = *s * 3600.0;

const IUnit* ms = new DerivedUnit({m, *s ^ -1});
const IUnit* kmh = new DerivedUnit({km, *h ^ -1});

const IUnitConverter* msToKmh = *ms >> *kmh;

msToKmh->convert(100.0); // 360.0
~(*msToKmh)->convert(18.0); // 5.0

delete msToKmh;
delete kmh;
delete ms;
delete h;
delete s;
delete km;
delete m;
```

## Développement

### Réinitialisation du projet, génération de la configuration CodeBlocks et du Makefile, et compilation:

```bash
cd unit-simple-ri
rm -rf bin/ lib/ CMakeFiles/ CMakeCache.txt Makefile cmake_install.cmake
cmake . -G "CodeBlocks - Unix Makefiles"
make
```

### Tests

```bash
cd unit-simple-ri
bin/test
```

### Build et test en un script (GNU/Linux)

```bash
cd unit-simple-ri
. build.sh
```
