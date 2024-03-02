#include "harmonicconstituent.h"

#include <array>

namespace HarmonicAnalysis {

struct HarmonicConstituent::HarmonicConstituentImpl {
  public:
    explicit HarmonicConstituentImpl(
        double frequency,
        const std::array<int, 7>& extended_doodson_numbers,
        std::function<NodalCorrections(double, double)> func
    )
    : m_frequency{frequency}
    , m_extended_doodson_numbers{extended_doodson_numbers}
    , m_nodal_corrections_func{func} {};
    explicit HarmonicConstituentImpl(
        double frequency,
        std::array<int, 7>&& extended_doodson_numbers,
        std::function<NodalCorrections(double, double)> func
    )
    : m_frequency{frequency}
    , m_extended_doodson_numbers{extended_doodson_numbers}
    , m_nodal_corrections_func{func} {};

    double m_frequency;
    std::array<int, 7> m_extended_doodson_numbers;
    std::function<NodalCorrections(double, double)> m_nodal_corrections_func;
};

HarmonicConstituent::HarmonicConstituent(
    double frequency,
    const std::array<int, 7>& extended_doodson_numbers,
    std::function<NodalCorrections(double, double)> func
)
: m_impl{std::make_unique<HarmonicConstituentImpl>(frequency, extended_doodson_numbers, func)} { }

HarmonicConstituent::HarmonicConstituent(
    double frequency,
    std::array<int, 7>&& extended_doodson_numbers,
    std::function<NodalCorrections(double, double)> func
)
: m_impl{std::make_unique<HarmonicConstituentImpl>(frequency, extended_doodson_numbers, func)} { }

double HarmonicConstituent::frequency() const { return m_impl->m_frequency; }

const std::array<int, 7>& HarmonicConstituent::extendedDoodsonNumbers() const {
    return m_impl->m_extended_doodson_numbers;
}

NodalCorrections HarmonicConstituent::nodalCorrections(double perigeeLongitude, double ascendingNodeLongitude) const {
    return m_impl->m_nodal_corrections_func(perigeeLongitude, ascendingNodeLongitude);
}

} // namespace HarmonicAnalysis
