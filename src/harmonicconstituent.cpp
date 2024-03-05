#include "harmonicconstituent.h"

#include <array>

namespace HarmonicAnalysis {

HarmonicConstituent::HarmonicConstituent(
    double frequency,
    const std::array<int, 7>& extended_doodson_numbers,
    std::function<NodalCorrections(double, double)> func
)
: m_frequency{frequency}
, m_extendedDoodsonNumbers{extended_doodson_numbers}
, m_nodalCorrections{func} { }

HarmonicConstituent::HarmonicConstituent(
    double frequency,
    std::array<int, 7>&& extended_doodson_numbers,
    std::function<NodalCorrections(double, double)> func
)
: m_frequency{frequency}
, m_extendedDoodsonNumbers{extended_doodson_numbers}
, m_nodalCorrections{func} { }

HarmonicConstituent::HarmonicConstituent(
    double frequency,
    HarmonicConstants harmonicConstants,
    const std::array<int, 7>& extended_doodson_numbers,
    std::function<NodalCorrections(double, double)> func
)
: m_frequency{frequency}
, m_harmonicConstants{harmonicConstants}
, m_extendedDoodsonNumbers{extended_doodson_numbers}
, m_nodalCorrections{func} {};

HarmonicConstituent::HarmonicConstituent(
    double frequency,
    HarmonicConstants harmonicConstants,
    std::array<int, 7>&& extended_doodson_numbers,
    std::function<NodalCorrections(double, double)> func
)
: m_frequency{frequency}
, m_harmonicConstants{harmonicConstants}
, m_extendedDoodsonNumbers{extended_doodson_numbers}
, m_nodalCorrections{func} {};

double HarmonicConstituent::frequency() const { return m_frequency; }

const std::array<int, 7>& HarmonicConstituent::extendedDoodsonNumbers() const { return m_extendedDoodsonNumbers; }

HarmonicConstituent::NodalCorrections
HarmonicConstituent::nodalCorrections(double perigeeLongitude, double ascendingNodeLongitude) const {
    return m_nodalCorrections(perigeeLongitude, ascendingNodeLongitude);
}

HarmonicConstituent::HarmonicConstants HarmonicConstituent::harmonicConstants() const { return m_harmonicConstants; }

std::function<HarmonicConstituent::NodalCorrections(double, double)> HarmonicConstituent::nodalCorrectionFunc() const {
    return m_nodalCorrections;
}

} // namespace HarmonicAnalysis
