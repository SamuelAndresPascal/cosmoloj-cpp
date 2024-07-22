#include <extensions/HelperMacros.h>
#include <TestCase.h>
#include <TestFixture.h>
#include <TestSuite.h>
#include <TestCaller.h>
#include "boost/math/distributions.hpp"
#include "stats.hh"


class Expon
{
public:
    Expon(const double loc, const double lambda, const double x, const double expected, const std::string message)
    : m_loc(loc), m_lambda(lambda), m_x(x), m_expected(expected), m_message(message)
    {
    }

    const double loc() const
    {
        return m_loc;
    }

    const double lambda() const
    {
        return m_lambda;
    }

    const double x() const
    {
        return m_x;
    }

    const double expected() const
    {
        return m_expected;
    }

    const std::string message() const
    {
        return m_message;
    }

private:
    const double m_loc;
    const double m_lambda;
    const double m_x;
    const double m_expected;
    const std::string m_message;
};

template<> inline std::string CppUnit::StringHelper::toString(const Expon& p)
{
    return p.message();
}


class Norm
{
public:
    Norm(const double mean, const double sd, const double x, const double expected, const std::string message)
    : m_mean(mean), m_sd(sd), m_x(x), m_expected(expected), m_message(message)
    {
    }

    const double mean() const
    {
        return m_mean;
    }

    const double sd() const
    {
        return m_sd;
    }

    const double x() const
    {
        return m_x;
    }

    const double expected() const
    {
        return m_expected;
    }

    const std::string message() const
    {
        return m_message;
    }

private:
    const double m_mean;
    const double m_sd;
    const double m_x;
    const double m_expected;
    const std::string m_message;
};

template<> inline std::string CppUnit::StringHelper::toString(const Norm& p)
{
    return p.message();
}

class Gamma
{
public:
    Gamma(const double a, const double loc, const double scale, const double x, const double expected, const std::string message)
    : m_a(a), m_loc(loc), m_scale(scale), m_x(x), m_expected(expected), m_message(message)
    {
    }

    const double a() const
    {
        return m_a;
    }

    const double loc() const
    {
        return m_loc;
    }

    const double scale() const
    {
        return m_scale;
    }

    const double x() const
    {
        return m_x;
    }

    const double expected() const
    {
        return m_expected;
    }

    const std::string message() const
    {
        return m_message;
    }

private:
    const double m_a;
    const double m_loc;
    const double m_scale;
    const double m_x;
    const double m_expected;
    const std::string m_message;
};

template<> inline std::string CppUnit::StringHelper::toString(const Gamma& p)
{
    return p.message();
}

class BoostMathDistributionTest : public CppUnit::TestFixture
{

    CPPUNIT_TEST_SUITE( BoostMathDistributionTest );
    CPPUNIT_TEST_PARAMETERIZED( expon_pdf,
    {
        Expon(0, 1., 0.5, 0.6065306597126334, ""),
        Expon(0.2, 1., 0.7, 0.6065306597126334, ""),
        Expon(0.2, 1., 0.5, 0.7408182206817179, "")
    });
    CPPUNIT_TEST_PARAMETERIZED( expon_cdf,
    {
        Expon(0, 1., 0.5, 0.3934693402873666, ""),
        Expon(0.2, 1., 0.7, 0.39346934028736646, ""),
        Expon(0.2, 1., 0.5, 0.2591817793182821, "")
    });
    CPPUNIT_TEST_PARAMETERIZED( expon_ppf,
    {
        Expon(0, 1., 0.3934693402873666, 0.5, ""),
        Expon(0.2, 1., 0.39346934028736646, 0.7, ""),
        Expon(0.2, 1., 0.2591817793182821, 0.5, "")
    });
    CPPUNIT_TEST_PARAMETERIZED( norm_pdf,
    {
        Norm(0, 1., 0.5, 0.3520653267642995, ""),
        Norm(0.2, 1., 0.7, 0.3520653267642995, ""),
        Norm(0.2, 1., 0.5, 0.38138781546052414, "")
    });
    CPPUNIT_TEST_PARAMETERIZED( norm_cdf,
    {
        Norm(0, 1., 0.5, 0.6914624612740131, ""),
        Norm(0.2, 1., 0.7, 0.691462461274013, ""),
        Norm(0.2, 1., 0.5, 0.6179114221889526, "")
    });
    CPPUNIT_TEST_PARAMETERIZED( norm_ppf,
    {
        Norm(0, 1., 0.6914624612740131, 0.5, ""),
        Norm(0.2, 1., 0.691462461274013, 0.7, ""),
        Norm(0.2, 1., 0.6179114221889526, 0.5, "")
    });
    CPPUNIT_TEST_PARAMETERIZED( gamma_pdf,
    {
        Gamma(1., 0, 1., 0.5, 0.6065306597126334, ""),
        Gamma(1., 0.2, 1., 0.7, 0.6065306597126334, ""),
        Gamma(1., 0.2, 1., 0.5, 0.7408182206817179, ""),
        Gamma(1.1, 0, 1., 0.5, 0.5948522183564979, ""),
        Gamma(1.1, 0.2, 1., 0.7, 0.5948522183564979, ""),
        Gamma(1.1, 0.2, 1., 0.5, 0.6903719013195413, ""),
        Gamma(0.9, 0, 1., 0.5, 0.6083155580655996, ""),
        Gamma(0.9, 0.2, 1., 0.7, 0.6083155580655996, ""),
        Gamma(0.9, 0.2, 1., 0.5, 0.7819386772878384, ""),
        Gamma(0.9, 0.2, 1.2, 0.5, 0.6976286342567877, "")
    });
    CPPUNIT_TEST_PARAMETERIZED( gamma_cdf,
    {
        Gamma(1., 0, 1., 0.5, 0.3934693402873666, ""),
        Gamma(1., 0.2, 1., 0.7, 0.39346934028736646, ""),
        Gamma(1., 0.2, 1., 0.5, 0.2591817793182821, ""),
        Gamma(1.1, 0, 1., 0.5, 0.3465502275336354, ""),
        Gamma(1.1, 0.2, 1., 0.7, 0.3465502275336354, ""),
        Gamma(1.1, 0.2, 1., 0.5, 0.21798608841049288, ""),
        Gamma(0.9, 0, 1., 0.5, 0.4444064959610267, ""),
        Gamma(0.9, 0.2, 1., 0.7, 0.4444064959610267, ""),
        Gamma(0.9, 0.2, 1., 0.5, 0.3064068791124165, ""),
        Gamma(0.9, 0.2, 1.2, 0.5, 0.26595645375601923, "")
    });
    CPPUNIT_TEST_PARAMETERIZED( gamma_ppf,
    {
        Gamma(1., 0, 1., 0.3934693402873666, 0.5, ""),
        Gamma(1., 0.2, 1., 0.39346934028736646, 0.7, ""),
        Gamma(1., 0.2, 1., 0.2591817793182821, 0.5, ""),
        Gamma(1.1, 0, 1., 0.3465502275336354, 0.5, ""),
        Gamma(1.1, 0.2, 1., 0.3465502275336354, 0.7, ""),
        Gamma(1.1, 0.2, 1., 0.21798608841049288, 0.5, ""),
        Gamma(0.9, 0, 1., 0.4444064959610267, 0.5, ""),
        Gamma(0.9, 0.2, 1., 0.4444064959610267, 0.7, ""),
        Gamma(0.9, 0.2, 1., 0.3064068791124165, 0.5, ""),
        Gamma(0.9, 0.2, 1.2, 0.26595645375601923, 0.5, "")
    });
    CPPUNIT_TEST( coucou );
    CPPUNIT_TEST( pdf );
    CPPUNIT_TEST_SUITE_END();


public:

    void coucou()
    {
        CPPUNIT_ASSERT_EQUAL(std::string("coucou"), stats::coucou());
    }

    void pdf()
    {
        const auto exponential = boost::math::exponential_distribution<>{1.};
        const std::vector<double> exp_x = {0.5, 0.5, 0.3};
        const std::vector<double> exp_result = stats::pdf(exponential, exp_x);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.6065306597126334, exp_result[0], 1e-10);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.6065306597126334, exp_result[1], 1e-10);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7408182206817179, exp_result[2], 1e-10);

        const auto normal = boost::math::normal_distribution<>{0.2, 1.};
        const std::vector<double> normal_x = {0.7, 0.5};
        const std::vector<double> normal_result = stats::pdf(normal, normal_x);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3520653267642995, normal_result[0], 1e-10);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.38138781546052414, normal_result[1], 1e-10);

        const auto gamma = boost::math::gamma_distribution<>{0.9, 1.};
        const std::vector<double> gamma_x = {0.5, 0.3};
        const std::vector<double> gamma_result = stats::pdf(gamma, gamma_x);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.6083155580655996, gamma_result[0], 1e-10);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7819386772878384, gamma_result[1], 1e-10);
    }


    void expon_pdf(Expon& p)
    {
        const auto d = boost::math::exponential_distribution<>{p.lambda()};
        CPPUNIT_ASSERT_DOUBLES_EQUAL(p.expected(), boost::math::pdf(d, p.x() - p.loc()), 1e-10);
    }

    void expon_cdf(Expon& p)
    {
        const auto d = boost::math::exponential_distribution<>{p.lambda()};
        CPPUNIT_ASSERT_DOUBLES_EQUAL(p.expected(), boost::math::cdf(d, p.x() - p.loc()), 1e-10);
    }

    void expon_ppf(Expon& p)
    {
        const auto d = boost::math::exponential_distribution<>{p.lambda()};
        CPPUNIT_ASSERT_DOUBLES_EQUAL(p.expected(), boost::math::quantile(d, p.x()) + p.loc(), 1e-10);
    }

    void norm_pdf(Norm& p)
    {
        const auto d = boost::math::normal_distribution<>{p.mean(), p.sd()};
        CPPUNIT_ASSERT_DOUBLES_EQUAL(p.expected(), boost::math::pdf(d, p.x()), 1e-10);
    }

    void norm_cdf(Norm& p)
    {
        const auto d = boost::math::normal_distribution<>{p.mean(), p.sd()};
        CPPUNIT_ASSERT_DOUBLES_EQUAL(p.expected(), boost::math::cdf(d, p.x()), 1e-10);
    }

    void norm_ppf(Norm& p)
    {
        const auto d = boost::math::normal_distribution<>{p.mean(), p.sd()};
        CPPUNIT_ASSERT_DOUBLES_EQUAL(p.expected(), boost::math::quantile(d, p.x()), 1e-10);
    }

    void gamma_pdf(Gamma& p)
    {
        const auto d = boost::math::gamma_distribution<>{p.a(), p.scale()};
        CPPUNIT_ASSERT_DOUBLES_EQUAL(p.expected(), boost::math::pdf(d, p.x() - p.loc()), 1e-10);
    }

    void gamma_cdf(Gamma& p)
    {
        const auto d = boost::math::gamma_distribution<>{p.a(), p.scale()};
        CPPUNIT_ASSERT_DOUBLES_EQUAL(p.expected(), boost::math::cdf(d, p.x() - p.loc()), 1e-10);
    }

    void gamma_ppf(Gamma& p)
    {
        const auto d = boost::math::gamma_distribution<>{p.a(), p.scale()};
        CPPUNIT_ASSERT_DOUBLES_EQUAL(p.expected(), boost::math::quantile(d, p.x()) + p.loc(), 1e-10);
    }
};
