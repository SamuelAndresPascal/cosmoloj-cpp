#include <cppunit/ui/text/TestRunner.h>
#include "unit-test.cc"
#include "unit-operators-test.cc"

int main( int argc, char **argv)
{
  CppUnit::TextUi::TestRunner runner;
  //runner.addTest( ExampleTestCase::suite() );
  runner.addTest( SimpleUnitTest::suite() );
  runner.addTest( SimpleUnitOperatorsTest::suite() );
  runner.run();
  return 0;
}
