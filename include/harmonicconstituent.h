#pragma once

#include "tidalharmonicanalysisglobal.h"

#include <functional>
#include <memory>

namespace HarmonicAnalysis {

class TidalHarmonicAnalysis_EXPORT HarmonicConstituent {
  public:
    struct NodalCorrections {
        double amplitude;
        double angle;
    };

    struct HarmonicConstants {
        // Harmonic constants must be computed from sea level measurements
        double amplitude = 0.0;
        double phase     = 0.0;
    };

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

    explicit HarmonicConstituent(
        double frequency,
        HarmonicConstants harmonicConstants,
        const std::array<int, 7>& extended_doodson_numbers,
        std::function<NodalCorrections(double, double)> func = [](double, double) -> NodalCorrections {
        return NodalCorrections{.amplitude = 1.0, .angle = 0.0};
    }
    );

    explicit HarmonicConstituent(
        double frequency,
        HarmonicConstants harmonicConstants,
        std::array<int, 7>&& extended_doodson_numbers,
        std::function<NodalCorrections(double, double)> func = [](double, double) -> NodalCorrections {
        return NodalCorrections{.amplitude = 1.0, .angle = 0.0};
    }
    );

    ~HarmonicConstituent();

    double frequency() const;
    const std::array<int, 7>& extendedDoodsonNumbers() const;
    NodalCorrections nodalCorrections(double perigeeLongitude, double ascendingNodeLongitude) const;
    HarmonicConstants harmonicConstants();

  private:
    struct HarmonicConstituentImpl;
    std::unique_ptr<HarmonicConstituentImpl> m_impl;
};

} // namespace HarmonicAnalysis
