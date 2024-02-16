#include "nodalfactors.h"

#include "utils.h"

#include <cmath>

namespace {
inline NodalFactors equalFirstOrderComponentsFactors(double cosValue, double sinValue) noexcept {
    return NodalFactors{.amplitude = 1.009 + 0.187 * cosValue, .angle = 10.8 * sinValue};
}
inline NodalFactors equalSecondOrderComponentsFactors(double cosValue, double sinValue) noexcept {
    return NodalFactors{.amplitude = 1.0 - 0.037 * cosValue, .angle = -2.1 * sinValue};
}
} // namespace

class NodalFactorsFactoryPrivate {
  public:
    explicit NodalFactorsFactoryPrivate(double lunarAscendingNodeLongitude);

    void setAstronomicalParameters(double lunarAscendingNodeLongitude) noexcept;

    // TODO implement ...
    // NodalFactors operator()(/*class HarmonicComponent*/) const noexcept;

  private:
    double m_cosAscendingNode;
    double m_sinAscendingNode;

    // Mm
    inline NodalFactors montlyComponentMm() noexcept;

    // Mf
    inline NodalFactors semiMonthlyComponentMf() noexcept;

    // Q1
    inline NodalFactors largerEllipticalComponentQ1() noexcept;

    // O1
    inline NodalFactors principalComponentO1() noexcept;

    // O1
    inline NodalFactors principalComponentK1() noexcept;

    // 2N2
    inline NodalFactors secondOrderEllipticalComponent2N2() noexcept;

    // Mu2
    inline NodalFactors variationalComponentMu2() noexcept;

    // N2
    inline NodalFactors largerEllipticalComponentN2() noexcept;

    // Nu2
    inline NodalFactors largerEvectionalComponentNu2() noexcept;

    // M2
    inline NodalFactors principalComponentM2() noexcept;

    // K2
    inline NodalFactors declinationalComponentK2() noexcept;
};


NodalFactorsFactoryPrivate::NodalFactorsFactoryPrivate(double lunarAscendingNodeLongitude) {
    setAstronomicalParameters(lunarAscendingNodeLongitude);
}

void NodalFactorsFactoryPrivate::setAstronomicalParameters(double lunarAscendingNodeLongitude) noexcept {
    const double ascendingNodeRadians = Utils::degreesToRadians(lunarAscendingNodeLongitude);
    m_cosAscendingNode                = std::cos(ascendingNodeRadians);
    m_sinAscendingNode                = std::sin(ascendingNodeRadians);
}

inline NodalFactors NodalFactorsFactoryPrivate::montlyComponentMm() noexcept {
    return NodalFactors{.amplitude = 1.0 - 0.130 * m_cosAscendingNode, .angle = 0.0};
}

inline NodalFactors NodalFactorsFactoryPrivate::semiMonthlyComponentMf() noexcept {
    return NodalFactors{.amplitude = 1.043 + 0.414 * m_cosAscendingNode, .angle = -23.6 * m_sinAscendingNode};
}

inline NodalFactors NodalFactorsFactoryPrivate::largerEllipticalComponentQ1() noexcept {
    return equalFirstOrderComponentsFactors(m_cosAscendingNode, m_sinAscendingNode);
}

inline NodalFactors NodalFactorsFactoryPrivate::principalComponentO1() noexcept {
    return equalFirstOrderComponentsFactors(m_cosAscendingNode, m_sinAscendingNode);
}

inline NodalFactors NodalFactorsFactoryPrivate::principalComponentK1() noexcept {
    return NodalFactors{.amplitude = 1.006 + 0.115 * m_cosAscendingNode, .angle = -8.9 * m_sinAscendingNode};
}

inline NodalFactors NodalFactorsFactoryPrivate::secondOrderEllipticalComponent2N2() noexcept {
    return equalSecondOrderComponentsFactors(m_cosAscendingNode, m_sinAscendingNode);
}

inline NodalFactors NodalFactorsFactoryPrivate::variationalComponentMu2() noexcept {
    return equalSecondOrderComponentsFactors(m_cosAscendingNode, m_sinAscendingNode);
}

inline NodalFactors NodalFactorsFactoryPrivate::largerEllipticalComponentN2() noexcept {
    return equalSecondOrderComponentsFactors(m_cosAscendingNode, m_sinAscendingNode);
}

inline NodalFactors NodalFactorsFactoryPrivate::largerEvectionalComponentNu2() noexcept {
    return equalSecondOrderComponentsFactors(m_cosAscendingNode, m_sinAscendingNode);
}

inline NodalFactors NodalFactorsFactoryPrivate::principalComponentM2() noexcept {
    return equalSecondOrderComponentsFactors(m_cosAscendingNode, m_sinAscendingNode);
}

inline NodalFactors NodalFactorsFactoryPrivate::declinationalComponentK2() noexcept {
    return NodalFactors{.amplitude = 1.024 + 0.286 * m_cosAscendingNode, .angle = -17.7 * m_sinAscendingNode};
}

NodalFactorsFactory::NodalFactorsFactory(double lunarAscendingNodeLongitude)
: m_p{std::make_unique<NodalFactorsFactoryPrivate>(lunarAscendingNodeLongitude)} { }
