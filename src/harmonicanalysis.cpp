#include "harmonicanalysis.h"

#include <Eigen/Cholesky>

using namespace std::literals;

namespace HarmonicAnalysis {

namespace {

struct LeastSquaresMatrices {
    Eigen::MatrixXd bMatrix;
    Eigen::VectorXd rhs;
};

std::vector<float> elapsedTimeInHours(
    const std::vector<HarmonicAnalysis::Utils::DateTime>& dateTimesGMT, const std::chrono::year_month_day& referenceDate
) {
    std::vector<float> elapsedTimes;
    elapsedTimes.reserve(dateTimesGMT.size());
    for (auto& dateTime : dateTimesGMT) {
        std::chrono::hours elapsedDaysInHours = std::chrono::duration_cast<std::chrono::hours>(
            std::chrono::sys_days(dateTime.date) - std::chrono::sys_days(referenceDate)
        );
        std::chrono::duration<float, std::ratio<3600>> hours        = dateTime.hours + dateTime.minutes;
        std::chrono::duration<float, std::ratio<3600>> elapsedHours = elapsedDaysInHours + hours;
        elapsedTimes.push_back(elapsedHours.count());
    }

    return elapsedTimes;
}

std::pair<std::vector<double>, std::vector<HarmonicConstituent::NodalCorrections>>
computeConstituentsEquilibriumPhaseAngles(
    const std::vector<HarmonicConstituent>& constituents, const std::chrono::year_month_day& refDate
) {
    constexpr std::chrono::hours refHour{0h};
    constexpr std::chrono::minutes refMinutes{0min};
    double moonLongitude = Utils::AstronomicalLongitudes::calculateMoonMeanLongitude(refDate, refHour, refMinutes);
    double sunLongitude  = Utils::AstronomicalLongitudes::calculateSunMeanLongitude(refDate, refHour, refMinutes);
    double perigee       = Utils::AstronomicalLongitudes::calculateLunarPerigee(refDate, refHour, refMinutes);
    double ascendingNode =
        Utils::AstronomicalLongitudes::calculateLunarAscendingNodeLongitude(refDate, refHour, refMinutes);
    double perihelion = Utils::AstronomicalLongitudes::calculatePerihelionLongitude(refDate, refHour, refMinutes);

    std::vector<double> phaseAngles;
    phaseAngles.reserve(constituents.size());
    std::vector<HarmonicAnalysis::HarmonicConstituent::NodalCorrections> nodalCorrections;
    nodalCorrections.reserve(constituents.size());
    for (const auto& hConst : constituents) {
        const std::array<int, 7>& doodsonNumbers = hConst.extendedDoodsonNumbers();
        double equilibriumPhaseAngle             = doodsonNumbers[0] * (sunLongitude - moonLongitude);
        equilibriumPhaseAngle += doodsonNumbers[1] * moonLongitude;
        equilibriumPhaseAngle += doodsonNumbers[2] * sunLongitude;
        equilibriumPhaseAngle += doodsonNumbers[3] * perigee;
        equilibriumPhaseAngle += doodsonNumbers[4] * ascendingNode;
        equilibriumPhaseAngle += doodsonNumbers[5] * perihelion;
        equilibriumPhaseAngle += doodsonNumbers[6] * 90;

        phaseAngles.push_back(equilibriumPhaseAngle);
        nodalCorrections.push_back(hConst.nodalCorrections(perigee, ascendingNode));
    }

    return {phaseAngles, nodalCorrections};
}

LeastSquaresMatrices computeLeastSquaresMatrices(
    const std::vector<double>& seaLevel,
    const std::vector<Utils::DateTime>& dateTimesGMT,
    const std::vector<HarmonicConstituent>& constituents
) {
    // Reference time point is the first date in the series at 00:00
    const std::chrono::year_month_day refDate = dateTimesGMT.front().date;

    const std::vector<float> elapsedHours = elapsedTimeInHours(dateTimesGMT, refDate);
    auto [phaseAngles, nodalCorrection]   = computeConstituentsEquilibriumPhaseAngles(constituents, refDate);

    for (int i = 0; i < nodalCorrection.size(); ++i) {
        phaseAngles[i] -= nodalCorrection[i].angle;
    }

    const int rows = elapsedHours.size();
    const int cols = 2 * constituents.size() + 1;
    Eigen::MatrixXd xMatrix(rows, cols);

    for (int i = 0; i < rows; ++i) {
        xMatrix(i, 0) = 1.0;
    }

    for (int j = 1; j <= constituents.size(); ++j) {
        for (int i = 0; i < rows; ++i) {
            double x      = Utils::degreesToRadians(constituents[j].frequency() * elapsedHours[i] + phaseAngles[j]);
            xMatrix(i, j) = nodalCorrection[j].amplitude * std::cos(x);
            xMatrix(i, j + constituents.size()) = nodalCorrection[j].amplitude * std::sin(x);
        }
    }

    Eigen::VectorXd y(seaLevel.size());
    for (int i = 0; i < seaLevel.size(); ++i) {
        y(i) = seaLevel[i];
    }
    Eigen::MatrixXd xMatrixT = xMatrix.transpose();

    return LeastSquaresMatrices{.bMatrix = xMatrixT * xMatrix, .rhs = xMatrixT * y};
}

} // namespace

std::pair<double, std::vector<HarmonicConstituent>> computeHarmonicConstituentsConstants(
    const std::vector<double>& seaLevel,
    const std::vector<Utils::DateTime>& dateTimesGMT,
    const std::vector<HarmonicConstituent>& constituents
) {
    assert(dateTimesGMT.size() > 0);
    assert(seaLevel.size() == dateTimesGMT.size());
    // We have 2 unknowns per constituent plus the mean sea level C0
    assert(seaLevel.size() > 2 * constituents.size() + 1);

    LeastSquaresMatrices matrices     = computeLeastSquaresMatrices(seaLevel, dateTimesGMT, constituents);
    Eigen::MatrixXd harmonicConstants = matrices.bMatrix.llt().solve(matrices.rhs);

    double meanSeaLevel = harmonicConstants(0);
    std::vector<HarmonicConstituent> harmonicConstituents;
    const int n = constituents.size();
    harmonicConstituents.reserve(n);
    for (int i = 0; i < n; ++i) {
        const double cosComp = harmonicConstants(i + 1);
        const double sinComp = harmonicConstants(i + 1 + n);
        HarmonicConstituent::HarmonicConstants hConstants{
            .amplitude = std::sqrt(cosComp * cosComp + sinComp * sinComp),
            .phase     = Utils::radiansToDegrees(std::atan(sinComp / cosComp))
        };

        harmonicConstituents.emplace_back(
            constituents[i].frequency(),
            hConstants,
            constituents[i].extendedDoodsonNumbers(),
            constituents[i].nodalCorrectionFunc()
        );
    }

    return {meanSeaLevel, harmonicConstituents};
}

} // namespace HarmonicAnalysis
