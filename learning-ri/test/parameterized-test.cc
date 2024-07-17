#include <extensions/HelperMacros.h>
#include <TestCase.h>
#include <TestFixture.h>
#include <TestSuite.h>
#include <TestCaller.h>
#include "unitSimpleRI.hh"
#include <ostream>

using namespace unit;

class Parameter1
{
public:
    Parameter1(const std::string toto, const std::string tata) : m_toto(toto), m_tata(tata)
    {
    }

    const std::string& toto() const
    {
        return m_toto;
    }

    const std::string& tata() const
    {
        return m_tata;
    }

    friend std::ostream& operator<<(std::ostream& strm, const Parameter1& data)
    {
        strm << data.toto();
        return strm;
    }

private:
    const std::string m_toto;
    const std::string m_tata;
};


class Parameter2
{
public:
    Parameter2(const std::string toto, const std::string tata) : m_toto(toto), m_tata(tata)
    {
    }

    const std::string& toto() const
    {
        return m_toto;
    }

    const std::string& tata() const
    {
        return m_tata;
    }

private:
    const std::string m_toto;
    const std::string m_tata;
};

template<> inline std::string CppUnit::StringHelper::toString(const Parameter2& p)
{
    return p.toto();
}


class ParameterizedTest : public CppUnit::TestFixture
{

    CPPUNIT_TEST_SUITE( ParameterizedTest );
    CPPUNIT_TEST_PARAMETERIZED( parameterized1,
    {
        Parameter1("toto1", "au revoir1"),
        Parameter1("tuto2", "au revoir2")
    });
    CPPUNIT_TEST_PARAMETERIZED( parameterized2,
    {
        Parameter2("toto1", "au revoir1"),
        Parameter2("tuto2", "au revoir2")
    });
    CPPUNIT_TEST_SUITE_END();


public:

    void parameterized1(Parameter1& x)
    {
        CPPUNIT_ASSERT_EQUAL(5, (int)x.toto().length());
    }

    void parameterized2(Parameter2& x)
    {
        CPPUNIT_ASSERT_EQUAL(5, (int)x.toto().length());
    }
};
