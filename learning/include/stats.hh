#ifndef STATS_HH
#define STATS_HH

#include <string>
#include <vector>
#include "boost/math/distributions.hpp"

namespace stats
{

    std::string coucou();

    template<class Distribution>
    inline std::vector<double> pdf(Distribution d, const std::vector<double>& x)
    {
        std::vector<double> result;
        for (int i = 0; i < x.size(); i++)
        {
            result.push_back(boost::math::pdf(d, x[i]));
        }
        return result;
    }
}

#endif // STATS_HH
