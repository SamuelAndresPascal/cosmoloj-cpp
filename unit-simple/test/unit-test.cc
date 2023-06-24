//#include <cppunit/extensions/HelperMacros.h>
#include <TestCase.h>
#include <TestFixture.h>
#include <TestSuite.h>
#include <TestCaller.h>
#include "unitSimpleRI.hh"

using namespace unit;

class SimpleUnitTest : public CppUnit::TestFixture {
public:

  void transformed()
  {
    const Unit* m = new FundamentalUnit();
    const Unit* km = m->scaleMultiply(1000);
    const Unit* cm = m->scaleDivide(100);
    const IUnitConverter* cmToKm = cm->getConverterTo(km);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.00003, cmToKm->convert(3), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., cmToKm->inverse()->convert(0.00003), 1e-10);
  }

  void derived()
  {
    const Unit* m = new FundamentalUnit();
    const Unit* km = m->scaleMultiply(1000);
    const Unit* km2 = new DerivedUnit({km->factor(2)});
    const Unit* cm = m->scaleDivide(100);
    const Unit* cm2 = new DerivedUnit({cm->factor(2)});
    const IUnitConverter* km2Tocm2 = km2->getConverterTo(cm2);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(30000000000., km2Tocm2->convert(3), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., km2Tocm2->inverse()->convert(30000000000.), 1e-10);
  }

  void combinedDerived()
  {

    const Unit* m = new FundamentalUnit();
    const Unit* kg = new FundamentalUnit();
    const Unit* g = kg->scaleDivide(1000);
    const Unit* ton = kg->scaleMultiply(1000);
    const Unit* gPerM2 = new DerivedUnit({g, m->factor(-2)});
    const Unit* km = m->scaleMultiply(1000);
    const Unit* tonPerKm2 = new DerivedUnit({ton, km->factor(-2)});
    const Unit* cm = m->scaleDivide(100);
    const Unit* tonPerCm2 = new DerivedUnit({ton, cm->factor(-2)});
    const IUnitConverter* gPerM2ToTonPerKm2 = gPerM2->getConverterTo(tonPerKm2);
    const IUnitConverter* gPerM2ToTonPerCm2 = gPerM2->getConverterTo(tonPerCm2);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(1., gPerM2ToTonPerKm2->convert(1.), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., gPerM2ToTonPerKm2->inverse()->convert(3.), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1e-10, gPerM2ToTonPerCm2->convert(1.), 1e-20);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3e-10, gPerM2ToTonPerCm2->convert(3.), 1e-20);
    CPPUNIT_ASSERT_EQUAL(0., gPerM2ToTonPerCm2->offset());
    CPPUNIT_ASSERT_EQUAL(1e-10, gPerM2ToTonPerCm2->scale());
    CPPUNIT_ASSERT_EQUAL(-0., gPerM2ToTonPerCm2->inverse()->offset());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., gPerM2ToTonPerCm2->inverse()->convert(3e-10), 1e-10);
  }

  void temperatures()
  {

    const Unit* k = new FundamentalUnit();
    const Unit* c = k->shift(273.15);
    const IUnitConverter* kToC = k->getConverterTo(c);


    CPPUNIT_ASSERT_DOUBLES_EQUAL(-273.15, kToC->convert(0), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(273.15, kToC->inverse()->convert(0), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-272.15, kToC->convert(1), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(274.15, kToC->inverse()->convert(1), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-271.15, kToC->convert(2), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(275.15, kToC->inverse()->convert(2), 1e-10);

    // en combinaison avec d'autres unités, les conversions d'unités de températures doivent devenir linéaires
    const Unit* m = new FundamentalUnit();
    const Unit* cPerM = new DerivedUnit({c, m->factor(-1)});
    const Unit* kPerM = new DerivedUnit({k, m->factor(-1)});
    const IUnitConverter* kPerMToCPerM = kPerM->getConverterTo(cPerM);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., kPerMToCPerM->convert(3), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., kPerMToCPerM->inverse()->convert(3), 1e-10);
  }

  void speed()
  {
    const Unit* m = new FundamentalUnit();
    const Unit* km = m->scaleMultiply(1000.0);

    const Unit* s = new FundamentalUnit();
    const Unit* h = s->scaleMultiply(3600.0);

    const Unit* ms = new DerivedUnit({m, s->factor(-1)});
    const Unit* kmh = new DerivedUnit({km, h->factor(-1)});

    const IUnitConverter* msToKmh = ms->getConverterTo(kmh);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(360.0, msToKmh->convert(100.0), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, msToKmh->inverse()->convert(18.0), 1e-10);
  }


  static CppUnit::Test *suite()
  {
    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "SimpleUnitTest" );
    suiteOfTests->addTest( new CppUnit::TestCaller<SimpleUnitTest>(
                                   "transformed unit conversion",
                                   &SimpleUnitTest::transformed ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<SimpleUnitTest>(
                                   "derived unit conversion",
                                   &SimpleUnitTest::derived ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<SimpleUnitTest>(
                                   "combined dimension derived unit conversion",
                                   &SimpleUnitTest::combinedDerived ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<SimpleUnitTest>(
                                   "temperatures",
                                   &SimpleUnitTest::temperatures ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<SimpleUnitTest>(
                                   "speed",
                                   &SimpleUnitTest::speed ) );
    return suiteOfTests;
  }


};
