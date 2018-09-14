#include "BaseGenerator.h"

using namespace GalGen;

BaseGenerator::BaseGenerator(unsigned int pointsNumber, double stddev) : pointsNumber_(pointsNumber)
{
	distribution_ = std::make_unique<std::normal_distribution<double>>(0, stddev);
	scale_ = Vector3{ 1.0, 1.0, 1.0 };
	translation_ = Vector3{ 0.0, 0.0, 0.0 };
}

void BaseGenerator::setDeviation(double stddev)
{
	distribution_.reset();
	distribution_ = std::make_unique<std::normal_distribution<double>>(0, stddev);
}

void BaseGenerator::setScale(Vector3 scale)
{
	scale_ = scale;
}

void BaseGenerator::setTranslation(Vector3 translation)
{
	translation_ = translation;
}

std::vector<Vector3> BaseGenerator::generate(BoundingVolume bv)
{
	std::vector<Vector3> data;
	Vector3 v{};
	for (unsigned int i = 0; i < pointsNumber_; ++i)
	{
		switch (bv)
		{
		case BoundingVolume::BV_CUBE:
			v = getPointInsideCube();
			break;
		case BoundingVolume::BV_SPHERE:
			v = getPointInsideSphere();
			break;
		}
		v.scale(scale_);
		v.translate(translation_);
		data.push_back(v);
	}
	return data;
}

Vector3 BaseGenerator::getPointInsideSphere()
{
	const double DISTRIBUTION_SCALE_FACTOR{ 0.5 };
	Vector3 v{};
	double len_square{ 10.0 };
	while (len_square > 1.0)
	{
		v.x = (*distribution_)(generator_) * DISTRIBUTION_SCALE_FACTOR;
		v.y = (*distribution_)(generator_) * DISTRIBUTION_SCALE_FACTOR;
		v.z = (*distribution_)(generator_) * DISTRIBUTION_SCALE_FACTOR;
		len_square = v.x * v.x + v.y * v.y + v.z * v.z;
	}
	return v;
}

Vector3 BaseGenerator::getPointInsideCube()
{
	Vector3 v{ 10.0, 10.0, 10.0 };
	while (abs(v.x) > 1.0 || abs(v.y) > 1.0 || abs(v.z) > 1.0)
	{
		v.x = (*distribution_)(generator_);
		v.y = (*distribution_)(generator_);
		v.z = (*distribution_)(generator_);
	}
	return v;
}