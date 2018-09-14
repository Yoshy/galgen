#include "Vector3Array.h"


using namespace GalGen;

Vector3Array::Vector3Array()
{
	points_.clear();
}

Vector3Array::Vector3Array(const std::vector<Vector3>& points) : Vector3Array()
{
	addPoints(points);
}

void Vector3Array::addPoints(const std::vector<Vector3>& points)
{
	points_.reserve(points_.size() + points.size());
	points_.insert(points_.end(), points.begin(), points.end());
}

void Vector3Array::addPoints(const Vector3Array& array)
{
	addPoints(array.getPoints());
}
