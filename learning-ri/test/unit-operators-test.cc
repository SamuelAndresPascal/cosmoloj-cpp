//#include <cppunit/extensions/HelperMacros.h>
#include <TestCase.h>
#include <TestFixture.h>
#include <TestSuite.h>
#include <TestCaller.h>
#include "unitSimpleRI.hh"

using namespace unit;

class SimpleUnitOperatorsTest : public CppUnit::TestFixture {
public:

  void transformed()
  {
    const IUnit* m = new FundamentalUnit();
    const IUnit* km = *m * 1000;
    const IUnit* cm = *m / 100;
    const IUnitConverter& cmToKm = *cm >> *km;

    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.00003, cmToKm.convert(3), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., (~cmToKm).convert(0.00003), 1e-10);

    //delete cmToKm;
    delete cm;
    delete km;
    delete m;
  }

  void derived()
  {
    const IUnit* m = new FundamentalUnit();
    const IUnit* km = *m * 1000;
    const IUnit* km2 = *km ^ 2;
    const IUnit* cm = *m / 100;
    const IUnit* cm2 = *cm ^ 2;
    const IUnitConverter& km2Tocm2 = *km2 >> *cm2;

    CPPUNIT_ASSERT_DOUBLES_EQUAL(30000000000., km2Tocm2.convert(3), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., (~km2Tocm2).convert(30000000000.), 1e-10);

    //delete km2Tocm2;
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
    const IUnit* g = *kg / 1000;
    const IUnit* ton = *kg * 1000;
    const IUnit* gPerM2 = *g * *(*m ^ -2);
    const IUnit* km = *m * 1000;
    const IUnit* tonPerKm2 = *ton * *(*(~*km) ^ 2);
    const IUnit* cm = *m / 100;
    const IUnit* tonPerCm2 = *ton / *(*cm ^ 2);
    const IUnitConverter& gPerM2ToTonPerKm2 = *gPerM2 >> *tonPerKm2;
    const IUnitConverter& gPerM2ToTonPerCm2 = *tonPerCm2 << *gPerM2;

    CPPUNIT_ASSERT_DOUBLES_EQUAL(1., gPerM2ToTonPerKm2.convert(1.), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., (~gPerM2ToTonPerKm2).convert(3.), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1e-10, gPerM2ToTonPerCm2.convert(1.), 1e-20);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3e-10, gPerM2ToTonPerCm2.convert(3.), 1e-20);
    CPPUNIT_ASSERT_EQUAL(0., gPerM2ToTonPerCm2.offset());
    CPPUNIT_ASSERT_EQUAL(1e-10, gPerM2ToTonPerCm2.scale());
    CPPUNIT_ASSERT_EQUAL(-0., (~gPerM2ToTonPerCm2).offset());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., (~gPerM2ToTonPerCm2).convert(3e-10), 1e-10);

    //delete gPerM2ToTonPerCm2;
    //delete gPerM2ToTonPerKm2;
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
    const IUnit* c = *k + 273.15;
    const IUnitConverter& kToC = *k >> *c;


    CPPUNIT_ASSERT_DOUBLES_EQUAL(-273.15, kToC.convert(0), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(273.15, (~kToC).convert(0), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-272.15, kToC.convert(1), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(274.15, (~kToC).convert(1), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-271.15, kToC.convert(2), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(275.15, (~kToC).convert(2), 1e-10);

    // en combinaison avec d'autres unités, les conversions d'unités de températures doivent devenir linéaires
    const IUnit* m = new FundamentalUnit();
    const IUnit* cPerM = *c / *m;
    const IUnit* kPerM = *k / *m;
    const IUnitConverter& kPerMToCPerM = *kPerM >> *cPerM;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., kPerMToCPerM.convert(3), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., (~kPerMToCPerM).convert(3), 1e-10);

    //delete kPerMToCPerM;
    delete kPerM;
    delete cPerM;
    delete m;
    //delete kToC;
    delete c;
    delete k;
  }

  void speed()
  {
    const IUnit* m = new FundamentalUnit();
    const IUnit* km = *m * 1000.0;

    const IUnit* s = new FundamentalUnit();
    const IUnit* h = *s * 3600.0;

    const IUnit* ms = *s / *m;
    const IUnit* kmh = *km / *h;

    const IUnitConverter& msToKmh = *ms >> *kmh;

    CPPUNIT_ASSERT_DOUBLES_EQUAL(360.0, msToKmh.convert(100.0), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, (~msToKmh).convert(18.0), 1e-10);

    //delete msToKmh;
    delete kmh;
    delete ms;
    delete h;
    delete s;
    delete km;
    delete m;
  }


  static CppUnit::Test *suite()
  {
    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "SimpleUnitTest" );
    suiteOfTests->addTest( new CppUnit::TestCaller<SimpleUnitOperatorsTest>(
                                   "transformed unit conversion",
                                   &SimpleUnitOperatorsTest::transformed ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<SimpleUnitOperatorsTest>(
                                   "derived unit conversion",
                                   &SimpleUnitOperatorsTest::derived ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<SimpleUnitOperatorsTest>(
                                   "combined dimension derived unit conversion",
                                   &SimpleUnitOperatorsTest::combinedDerived ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<SimpleUnitOperatorsTest>(
                                   "temperatures",
                                   &SimpleUnitOperatorsTest::temperatures ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<SimpleUnitOperatorsTest>(
                                   "speed",
                                   &SimpleUnitOperatorsTest::speed ) );
    return suiteOfTests;
  }


};
