#pragma once

#include "tidalharmonicanalysisglobal.h"

#include <array>
#include <functional>

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

    double frequency() const;
    const std::array<int, 7>& extendedDoodsonNumbers() const;
    NodalCorrections nodalCorrections(double perigeeLongitude, double ascendingNodeLongitude) const;
    HarmonicConstants harmonicConstants() const;
    std::function<NodalCorrections(double, double)> nodalCorrectionFunc() const;

  private:
    double m_frequency;
    HarmonicConstants m_harmonicConstants;
    std::array<int, 7> m_extendedDoodsonNumbers;
    std::function<NodalCorrections(double, double)> m_nodalCorrections;
};

} // namespace HarmonicAnalysis
