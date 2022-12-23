//#include <cppunit/extensions/HelperMacros.h>
#include <TestCase.h>
#include <TestFixture.h>
#include <TestSuite.h>
#include <TestCaller.h>
#include "../include/unit.hh"

using namespace unit;

class SimpleUnitTest : public CppUnit::TestFixture { 
public: 

  void transformed() 
  {
    const Unit* m = new FundamentalUnit();
    const Unit* km = m->scaleMultiply(1000);
    const Unit* cm = m->scaleDivide(100);
    const UnitConverter* cmToKm = cm->getConverterTo(km);

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
    const UnitConverter* km2Tocm2 = km2->getConverterTo(cm2);

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
    const UnitConverter* gPerM2ToTonPerKm2 = gPerM2->getConverterTo(tonPerKm2);
    const UnitConverter* gPerM2ToTonPerCm2 = gPerM2->getConverterTo(tonPerCm2);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(1., gPerM2ToTonPerKm2->convert(1.), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., gPerM2ToTonPerKm2->inverse()->convert(3.), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1e-10, gPerM2ToTonPerCm2->convert(1.), 1e-20);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3e-10, gPerM2ToTonPerCm2->convert(3.), 1e-20);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0., gPerM2ToTonPerCm2->offset(), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1e-10, gPerM2ToTonPerCm2->scale(), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-0., gPerM2ToTonPerCm2->inverse()->offset(), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3., gPerM2ToTonPerCm2->inverse()->convert(3e-10), 1e-10);
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
    return suiteOfTests;
  }
  

};
