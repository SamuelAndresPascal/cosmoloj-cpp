#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "unit-test.cc"
#include "unit-operators-test.cc"

int main( int argc, char **argv)
{
  CppUnit::TextUi::TestRunner runner;
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  runner.addTest( SimpleUnitTest::suite() );
  runner.addTest( SimpleUnitOperatorsTest::suite() );
  //runner.run();
  bool wasSuccessful = runner.run( "", false );
  return !wasSuccessful;
  //return 0;
}
