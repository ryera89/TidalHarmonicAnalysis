#include "astronomicallongitudes.h"

#include <chrono>

using namespace std::literals;

namespace {
double meanMoonLongitude(double julianCenturies) {}
} // namespace

AstronomicalLongitudes::AstronomicalLongitudes() {}

AstronomicalLongitudes astronimicalLongitudes() {
  constexpr std::chrono::year_month_day epoch{2000y, std::chrono::January, 1d};
}
