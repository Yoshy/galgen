#pragma once

namespace GalGen
{
    const double PI{ 3.1415926535897932 };

	struct Vector3
	{
		double x;
		double y;
		double z;

		void translate(const Vector3& t) { x += t.x; y += t.y; z += t.z; };
		void scale(const Vector3& s) { x *= s.x, y *= s.y, z *= s.z; };
	};
}
