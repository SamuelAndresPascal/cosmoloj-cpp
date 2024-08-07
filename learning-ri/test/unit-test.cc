#include <extensions/HelperMacros.h>
#include <TestCase.h>
#include <TestFixture.h>
#include <TestSuite.h>
#include <TestCaller.h>
#include "unitSimpleRI.hh"

using namespace unit;


class SimpleUnitTest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE( SimpleUnitTest );
    CPPUNIT_TEST( transformed );
    CPPUNIT_TEST( derived );
    CPPUNIT_TEST( combinedDerived );
    CPPUNIT_TEST( temperatures );
    CPPUNIT_TEST( speed );
    CPPUNIT_TEST_SUITE_END();

public:

  void transformed()
  {
    const IUnit* m = new FundamentalUnit();
    const IUnit* km = m->scaleMultiply(1000);
    const IUnit* cm = m->scaleDivide(100);
    const IUnitConverter* cmToKm = cm->getConverterTo(*km);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.00003, cmToKm->convert(3), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., cmToKm->inverse()->convert(0.00003), 1e-10);

    delete cmToKm;
    delete cm;
    delete km;
    delete m;
  }

  void derived()
  {
    const IUnit* m = new FundamentalUnit();
    const IUnit* km = m->scaleMultiply(1000);
    const IUnit* km2 = new DerivedUnit({km->factor(2)});
    const IUnit* cm = m->scaleDivide(100);
    const IUnit* cm2 = new DerivedUnit({cm->factor(2)});
    const IUnitConverter* km2Tocm2 = km2->getConverterTo(*cm2);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(30000000000., km2Tocm2->convert(3), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., km2Tocm2->inverse()->convert(30000000000.), 1e-10);

    delete km2Tocm2;
    delete cm2;
    delete cm;
    delete km2;
    delete km;
    delete m;
  }

  void combinedDerived()
  {

    const IUnit* m = new FundamentalUnit();
    const IUnit* kg = new FundamentalUnit();
    const IUnit* g = kg->scaleDivide(1000);
    const IUnit* ton = kg->scaleMultiply(1000);
    const IUnit* gPerM2 = new DerivedUnit({g, m->factor(-2)});
    const IUnit* km = m->scaleMultiply(1000);
    const IUnit* tonPerKm2 = new DerivedUnit({ton, km->factor(-2)});
    const IUnit* cm = m->scaleDivide(100);
    const IUnit* tonPerCm2 = new DerivedUnit({ton, cm->factor(-2)});
    const IUnitConverter* gPerM2ToTonPerKm2 = gPerM2->getConverterTo(*tonPerKm2);
    const IUnitConverter* gPerM2ToTonPerCm2 = gPerM2->getConverterTo(*tonPerCm2);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(1., gPerM2ToTonPerKm2->convert(1.), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., gPerM2ToTonPerKm2->inverse()->convert(3.), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1e-10, gPerM2ToTonPerCm2->convert(1.), 1e-20);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3e-10, gPerM2ToTonPerCm2->convert(3.), 1e-20);
    CPPUNIT_ASSERT_EQUAL(0., gPerM2ToTonPerCm2->offset());
    CPPUNIT_ASSERT_EQUAL(1e-10, gPerM2ToTonPerCm2->scale());
    CPPUNIT_ASSERT_EQUAL(-0., gPerM2ToTonPerCm2->inverse()->offset());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., gPerM2ToTonPerCm2->inverse()->convert(3e-10), 1e-10);

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
  }

  void temperatures()
  {

    const IUnit* k = new FundamentalUnit();
    const IUnit* c = k->shift(273.15);
    const IUnitConverter* kToC = k->getConverterTo(*c);


    CPPUNIT_ASSERT_DOUBLES_EQUAL(-273.15, kToC->convert(0), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(273.15, kToC->inverse()->convert(0), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-272.15, kToC->convert(1), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(274.15, kToC->inverse()->convert(1), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-271.15, kToC->convert(2), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(275.15, kToC->inverse()->convert(2), 1e-10);

    // en combinaison avec d'autres unités, les conversions d'unités de températures doivent devenir linéaires
    const IUnit* m = new FundamentalUnit();
    const IUnit* cPerM = new DerivedUnit({c, m->factor(-1)});
    const IUnit* kPerM = new DerivedUnit({k, m->factor(-1)});
    const IUnitConverter* kPerMToCPerM = kPerM->getConverterTo(*cPerM);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., kPerMToCPerM->convert(3), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., kPerMToCPerM->inverse()->convert(3), 1e-10);

    delete kPerMToCPerM;
    delete kPerM;
    delete cPerM;
    delete m;
    delete kToC;
    delete c;
    delete k;
  }

  void speed()
  {
    const IUnit* m = new FundamentalUnit();
    const IUnit* km = m->scaleMultiply(1000.0);

    const IUnit* s = new FundamentalUnit();
    const IUnit* h = s->scaleMultiply(3600.0);

    const IUnit* ms = new DerivedUnit({m, s->factor(-1)});
    const IUnit* kmh = new DerivedUnit({km, h->factor(-1)});

    const IUnitConverter* msToKmh = ms->getConverterTo(*kmh);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(360.0, msToKmh->convert(100.0), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, msToKmh->inverse()->convert(18.0), 1e-10);

    delete msToKmh;
    delete kmh;
    delete ms;
    delete h;
    delete s;
    delete km;
    delete m;
  }
};
