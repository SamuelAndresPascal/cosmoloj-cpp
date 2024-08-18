#include <extensions/HelperMacros.h>
#include <TestCase.h>
#include <TestFixture.h>
#include <TestSuite.h>
#include <TestCaller.h>
#include <polymorphismRI.hh>


class PolymorphismTest : public CppUnit::TestFixture
{

    CPPUNIT_TEST_SUITE( PolymorphismTest );
    CPPUNIT_TEST( testIntReference );
    CPPUNIT_TEST_SUITE_END();


public:

    void testIntReference()
    {
        const Child child;
        CPPUNIT_ASSERT_EQUAL(2, child.getInt());

        const Parent parent;
        CPPUNIT_ASSERT_EQUAL(1, parent.getInt());
    }
};
