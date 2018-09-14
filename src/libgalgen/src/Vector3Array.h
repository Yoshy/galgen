#pragma once

#include <vector>
#include "Vector3.h"

namespace GalGen
{
	class Vector3Array
	{
	public:
		Vector3Array();
		explicit Vector3Array(const std::vector<Vector3>& points);
		void addPoints(const std::vector<Vector3>& points);
		void addPoints(const Vector3Array& array);
		const std::vector<Vector3> & getPoints() const { return points_; };
	private:
		std::vector<Vector3> points_;
	};
}
