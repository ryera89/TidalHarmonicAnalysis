#pragma once

#include "TidalHarmonicAnalysis_global.h"

#include <memory>

class NodalFactorsFactoryPrivate;

struct TidalHarmonicAnalysis_EXPORT NodalFactors {
    double amplitude;
    double angle;
};

class TidalHarmonicAnalysis_EXPORT NodalFactorsFactory {
  public:
    explicit NodalFactorsFactory(double lunarAscendingNodeLongitude);

    // TODO Implement...
    // NodalFactors operator()(/*class HarmonicComponent*/) const noexcept;

  private:
    std::unique_ptr<NodalFactorsFactoryPrivate> m_p;
};
