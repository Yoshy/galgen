#include "Mutator.h"
#include "Vector3Array.h"

using namespace GalGen;

Vector3Array Mutator::swirlXY(GalGen::Vector3Array& array, double rFactorPow, double rFactorLinear)
{
    std::vector<Vector3> points {};
    points.reserve(array.getPoints().size());
    for (auto& p : array.getPoints())
    {
        Vector3 pp{ 0.0, 0.0, p.z };
        double distFromCenter = sqrt(p.x * p.x + p.y * p.y);
        double degrees = pow(distFromCenter, rFactorPow) * rFactorLinear;
        double radians = 180.0 / PI * degrees;
        pp.x = p.x * cos(radians) - p.y * sin(radians);
        pp.y = p.x * sin(radians) + p.y * cos(radians);
        points.push_back(pp);
    }

    return Vector3Array(points);
}
