#pragma once

#include <memory>
#include <random>
#include "Vector3.h"

namespace GalGen
{
	enum class BoundingVolume{BV_SPHERE = 0, BV_CUBE = 1};

	const unsigned int DEFAULT_POINTS_NUMBER = 1000;

	class BaseGenerator
	{
	public:
		explicit BaseGenerator(unsigned int pointsNumber = DEFAULT_POINTS_NUMBER, double stddev = 1);
		void setPointsNum(unsigned int pointsNumber) { pointsNumber_ = pointsNumber; };
		void setDeviation(double stddev);
		void setScale(Vector3 scale);
		void setTranslation(Vector3 translation);
		std::vector<GalGen::Vector3> generate(BoundingVolume bv);
	private:
		unsigned int pointsNumber_;
		Vector3 scale_;
		Vector3 translation_;
		std::default_random_engine generator_;
		std::unique_ptr<std::normal_distribution<double>> distribution_;

		Vector3 getPointInsideSphere();
		Vector3 getPointInsideCube();
	};
}
