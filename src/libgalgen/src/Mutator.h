#pragma once

namespace GalGen
{
    class Vector3Array;

    namespace Mutator
    {
        Vector3Array swirlXY(GalGen::Vector3Array& array, double rFactorPow, double rFactorLinear);
    };
}
