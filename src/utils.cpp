#include "utils.h"

#include <numbers>

using namespace std::literals;

namespace {
// Julians days for January 1st 2000 12:00 hours.
static constexpr double julianDaysForEpoch = 2451545.0;
static constexpr double julianCentury      = 36525.0;

double radiansToDegrees(double radians) noexcept {
    constexpr double toDegrees = 180 / std::numbers::pi;
    return radians * toDegrees;
}

double degreesToRadians(double degrees) noexcept {
    constexpr double toRadians = std::numbers::pi / 180;
    return degrees * toRadians;
}

double calculateJulianCenturiesSinceEpoch(
    const std::chrono::year_month_day& date, std::chrono::hours hour, std::chrono::minutes minutes
) {
    const double julianDays = Utils::calculateJulianEphemerisDay(date, hour, minutes);

    return (julianDays - julianDaysForEpoch) / julianCentury;
}

double calculatePolynomial(double x, double c0, double c1, double c2, double c3 = 0.0) {
    return c0 + x * (c1 + x * (c2 + c3 * x));
}
} // namespace

namespace Utils {
double calculateJulianEphemerisDay(
    const std::chrono::year_month_day& date, std::chrono::hours hour, std::chrono::minutes minutes
) {
    int year  = static_cast<int>(date.year());
    int month = static_cast<unsigned>(date.month());
    if (month <= 2) {
        year -= 1;
        month += 12;
    }

    constexpr double hourToMinutes = 60.0;
    constexpr double dayToMinutes  = 1440.0;

    const double day =
        static_cast<unsigned>(date.day()) + (hour.count() * hourToMinutes + minutes.count()) / dayToMinutes;

    constexpr double c0 = 365.25;
    constexpr double c1 = 4716;
    constexpr double c2 = 30.6001;
    constexpr double c3 = 1524.5;

    const int a = year / 100;

    constexpr std::chrono::year_month_day gregorianCalendarReferenceDate(1582y, std::chrono::October, 15d);
    const bool isGregorianDate = date >= gregorianCalendarReferenceDate;

    const int b = isGregorianDate ? 2 - a + a / 4 : 0;

    return static_cast<int>(c0 * (year + c1)) + static_cast<int>(c2 * (month + 1)) + day + b - c3;
}

namespace AstronomicalLongitudes {


double calculateMoonMeanLongitude(
    const std::chrono::year_month_day& date, std::chrono::hours hours, std::chrono::minutes minutes
) {
    const double julianCenturiesSinceEpoch = calculateJulianCenturiesSinceEpoch(date, hours, minutes);

    constexpr double c0 = 218.3164477;
    constexpr double c1 = 481'267.88123421;
    constexpr double c2 = -0.0015786;
    constexpr double c3 = 0.0000019;

    const double longitude = calculatePolynomial(julianCenturiesSinceEpoch, c0, c1, c2, c3);
    return longitude >= 0 ? fmod(longitude, 360.0) : fmod(longitude, 360.0) + 360;
}

double calculateSunMeanLongitude(
    const std::chrono::year_month_day& date, std::chrono::hours hours, std::chrono::minutes minutes
) {
    const double julianCenturiesSinceEpoch = calculateJulianCenturiesSinceEpoch(date, hours, minutes);

    constexpr double c0 = 280.46646;
    constexpr double c1 = 36'000.76983;
    constexpr double c2 = -0.0003032;

    const double longitude = calculatePolynomial(julianCenturiesSinceEpoch, c0, c1, c2);
    return longitude >= 0 ? fmod(longitude, 360.0) : fmod(longitude, 360.0) + 360;
}

double calculateMoonAscendingNodeLongitude(
    const std::chrono::year_month_day& date, std::chrono::hours hours, std::chrono::minutes minutes
) {
    const double julianCenturiesSinceEpoch = calculateJulianCenturiesSinceEpoch(date, hours, minutes);

    constexpr double c0 = 125.04452;
    constexpr double c1 = -1934.136261;
    constexpr double c2 = 0.0020708;
    constexpr double c3 = 1.0 / 450'000.0;

    const double longitude = calculatePolynomial(julianCenturiesSinceEpoch, c0, c1, c2, c3);
    return longitude >= 0 ? fmod(longitude, 360.0) : fmod(longitude, 360.0) + 360;
}

double calculateMoonMeanPerigee(
    const std::chrono::year_month_day& date, std::chrono::hours hours, std::chrono::minutes minutes
) {
    const double julianCenturiesSinceEpoch = calculateJulianCenturiesSinceEpoch(date, hours, minutes);

    constexpr double c0 = 83.3532465;
    constexpr double c1 = 4069.0137287;
    constexpr double c2 = -0.0103200;
    constexpr double c3 = -1.0 / 80'053.0;

    const double longitude = calculatePolynomial(julianCenturiesSinceEpoch, c0, c1, c2, c3);
    return longitude >= 0 ? fmod(longitude, 360.0) : fmod(longitude, 360.0) + 360;
}

double calculatePerihelionLongitude(
    const std::chrono::year_month_day& date, std::chrono::hours hours, std::chrono::minutes minutes
) {
    const double julianCenturiesSinceEpoch = calculateJulianCenturiesSinceEpoch(date, hours, minutes);

    constexpr double c0 = 102.937348;
    constexpr double c1 = 1.7195366;
    constexpr double c2 = 0.00045688;
    constexpr double c3 = -0.000000018;

    const double longitude = calculatePolynomial(julianCenturiesSinceEpoch, c0, c1, c2, c3);
    return longitude >= 0 ? fmod(longitude, 360.0) : fmod(longitude, 360.0) + 360;
}
} // namespace AstronomicalLongitudes

} // namespace Utils
