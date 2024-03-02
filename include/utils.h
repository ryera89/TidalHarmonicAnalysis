#pragma once

#include "tidalharmonicanalysisglobal.h"

#include <chrono>

namespace Utils {

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
TidalHarmonicAnalysis_EXPORT double calculateMoonAscendingNodeLongitude(
    const std::chrono::year_month_day& date, std::chrono::hours hours, std::chrono::minutes minutes
);
TidalHarmonicAnalysis_EXPORT double calculateMoonMeanPerigee(
    const std::chrono::year_month_day& date, std::chrono::hours hours, std::chrono::minutes minutes
);
TidalHarmonicAnalysis_EXPORT double calculatePerihelionLongitude(
    const std::chrono::year_month_day& date, std::chrono::hours hours, std::chrono::minutes minutes
);
} // namespace AstronomicalLongitudes
} // namespace Utils
