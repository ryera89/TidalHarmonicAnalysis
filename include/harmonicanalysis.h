#pragma once

#include "tidalharmonicanalysisglobal.h"

#include "harmonicconstituent.h"

#include "utils.h"

namespace HarmonicAnalysis {

std::pair<double, std::vector<HarmonicConstituent>> TidalHarmonicAnalysis_EXPORT computeHarmonicConstituentsConstants(
    const std::vector<double>& seaLevel,
    const std::vector<Utils::DateTime>& dateTimesGMT,
    const std::vector<HarmonicConstituent>& constituents
);

std::vector<double> TidalHarmonicAnalysis_EXPORT predictSeaLevels(
    double meanSeaLevel,
    const std::vector<HarmonicConstituent>& constituents,
    const std::vector<Utils::DateTime>& dateTimesGMT
);

} // namespace HarmonicAnalysis
