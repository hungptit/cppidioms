#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

namespace stats {
    constexpr auto NaN = std::numeric_limits<double>::quiet_NaN();

    // This is the recursive formula for calculating mean of an array
    // mean[k+1] = mean[k] + (x[k+1] - mean[k]) / (k+1)
    //
    // Note:
    // 1. We ignore NaN in our computation
    // 2. Mean of an empty array is NaN
    template <typename Iter> double mean(Iter begin, Iter end) {
        double   mean  = 0;
        uint32_t count = 0;
        for (auto it = begin; it != end; ++it) {
            if (std::isnan(*it)) continue;
            const double delta = *it - mean;
            ++count;
            mean += delta / count;
        }

        return count > 0 ? mean : NaN;
    }

    double mean(const std::vector<double> &data) { return mean(data.cbegin(), data.cend()); }

    // Below is the recursive formula for the variance
    // s[k+1] = s[k] + (x[k+1] * x[k+1] - s[k]) / (k+1)
    // var = s[N] - mean[N] * mean[N]
    template <typename Iter> double variance(Iter begin, Iter end) {
        double   mean     = 0;
        double   mean_sqr = 0;
        uint32_t count    = 0;
        for (auto it = begin; it != end; ++it) {
            if (std::isnan(*it)) continue;
            const double val            = *it;
            const double mean_delta     = val - mean;
            const double mean_sqr_delta = val * val - mean_sqr;
            ++count;
            mean += mean_delta / count;
            mean_sqr += mean_sqr_delta / count;
        }
        return count > 0 ? mean_sqr - mean * mean : NaN;
    }

    double variance(const std::vector<double> &data) { return variance(data.cbegin(), data.cend()); }

} // namespace stats

TEST_CASE("mean function") {
    SUBCASE("Empty array") {
        const std::vector<double> data{};
        CHECK(isnan(stats::mean(data.cbegin(), data.cend())));
        CHECK(isnan(stats::mean(data)));
    }

    SUBCASE("NaN array") {
        const std::vector<double> data{stats::NaN, stats::NaN};
        CHECK(isnan(stats::mean(data.cbegin(), data.cend())));
        CHECK(isnan(stats::mean(data)));
    }

    SUBCASE("One element vector") {
        const std::vector<double> data{3};
        CHECK(stats::mean(data.cbegin(), data.cend()) == 3.0);
        CHECK(stats::mean(data) == 3.0);
    }

    SUBCASE("A regular vector") {
        const std::vector<double> data{1, stats::NaN, 3};
        CHECK(stats::mean(data.cbegin(), data.cend()) == 2.0);
        CHECK(stats::mean(data) == 2.0);
    }
}

TEST_CASE("variance function") {
    SUBCASE("Empty array") {
        const std::vector<double> data{};
        CHECK(isnan(stats::variance(data.cbegin(), data.cend())));
        CHECK(isnan(stats::variance(data)));
    }

    SUBCASE("NaN array") {
        const std::vector<double> data{stats::NaN, stats::NaN};
        CHECK(isnan(stats::variance(data.cbegin(), data.cend())));
        CHECK(isnan(stats::variance(data)));
    }

    SUBCASE("One element vector") {
        const std::vector<double> data{3};
        CHECK(stats::variance(data.cbegin(), data.cend()) == 0.0);
        CHECK(stats::variance(data) == 0.0);
    }

    SUBCASE("A regular vector") {
        const std::vector<double> data{1, stats::NaN, 3};
        CHECK(stats::variance(data.cbegin(), data.cend()) == 1.0);
        CHECK(stats::variance(data) == 1.0);
    }
}
