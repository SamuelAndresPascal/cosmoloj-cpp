#include <cppunit/ui/text/TestRunner.h>
#include "unit-test.cc"
#include "unit-operators-test.cc"
#include "parameterized-test.cc"
#include "polymorphism-test.cc"
#include "boost-math-distribution-test.cc"

int main( int argc, char **argv)
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest( SimpleUnitTest::suite() );
  runner.addTest( SimpleUnitOperatorsTest::suite() );
  runner.addTest( PolymorphismTest::suite() );
  runner.addTest( ParameterizedTest::suite() );
  runner.addTest( BoostMathDistributionTest::suite() );
  return !runner.run( "", false );
}
