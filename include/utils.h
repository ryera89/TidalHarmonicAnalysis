#pragma once

#include "tidalharmonicanalysisglobal.h"

#include "harmonicconstituent.h"

#include <chrono>

namespace HarmonicAnalysis {
namespace Utils {

struct TidalHarmonicAnalysis_EXPORT DateTime {
    std::chrono::hours hours;
    std::chrono::minutes minutes;
    std::chrono::year_month_day date;
};

TidalHarmonicAnalysis_EXPORT constexpr double radiansToDegrees(double radians) noexcept;
TidalHarmonicAnalysis_EXPORT constexpr double degreesToRadians(double degrees) noexcept;

TidalHarmonicAnalysis_EXPORT double calculateJulianEphemerisDay(
    const std::chrono::year_month_day& date, std::chrono::hours hour, std::chrono::minutes minutes
);

namespace AstronomicalLongitudes {
TidalHarmonicAnalysis_EXPORT double calculateMoonMeanLongitude(
    const std::chrono::year_month_day& date, std::chrono::hours hours, std::chrono::minutes minutes
);
TidalHarmonicAnalysis_EXPORT double calculateSunMeanLongitude(
    const std::chrono::year_month_day& date, std::chrono::hours hours, std::chrono::minutes minutes
);
TidalHarmonicAnalysis_EXPORT double calculateLunarAscendingNodeLongitude(
    const std::chrono::year_month_day& date, std::chrono::hours hours, std::chrono::minutes minutes
);
TidalHarmonicAnalysis_EXPORT double
calculateLunarPerigee(const std::chrono::year_month_day& date, std::chrono::hours hours, std::chrono::minutes minutes);
TidalHarmonicAnalysis_EXPORT double calculatePerihelionLongitude(
    const std::chrono::year_month_day& date, std::chrono::hours hours, std::chrono::minutes minutes
);

} // namespace AstronomicalLongitudes
} // namespace Utils
} // namespace HarmonicAnalysis
