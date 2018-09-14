#pragma once

#include <vector>
#include "Vector3.h"


namespace GalGen
{
	class GalaxyGenerator
	{
	public:
		GalaxyGenerator() = default;
		const std::vector<Vector3> generateRegularSpiralGalaxy();
		const std::vector<Vector3> generateToonSpiralGalaxy();
	};
}
