#pragma once

#include "tidalharmonicanalysisglobal.h"

#include <functional>
#include <memory>

namespace HarmonicAnalysis {

struct TidalHarmonicAnalysis_EXPORT NodalCorrections {
    double amplitude;
    double angle;
};

class TidalHarmonicAnalysis_EXPORT HarmonicConstituent {
  public:
    explicit HarmonicConstituent(
        double frequency,
        const std::array<int, 7>& extended_doodson_numbers,
        std::function<NodalCorrections(double, double)> func = [](double, double) -> NodalCorrections {
        return NodalCorrections{.amplitude = 1.0, .angle = 0.0};
    }
    );
    explicit HarmonicConstituent(
        double frequency,
        std::array<int, 7>&& extended_doodson_numbers,
        std::function<NodalCorrections(double, double)> func = [](double, double) -> NodalCorrections {
        return NodalCorrections{.amplitude = 1.0, .angle = 0.0};
    }
    );

    double frequency() const;
    const std::array<int, 7>& extendedDoodsonNumbers() const;
    NodalCorrections nodalCorrections(double perigeeLongitude, double ascendingNodeLongitude) const;

  private:
    struct HarmonicConstituentImpl;
    std::unique_ptr<HarmonicConstituentImpl> m_p;
};

} // namespace HarmonicAnalysis
