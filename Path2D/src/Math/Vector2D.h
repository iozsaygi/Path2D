#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "Public/API.h"

namespace Path2D
{
	struct PATH2D_API Vector2D
	{
	public:
		Vector2D();
		Vector2D(float x, float y);
		Vector2D(const Vector2D& vector2D);

		static Vector2D Zero();
		static float ManhattanDistance(const Vector2D& source, const Vector2D& destination);

		float GetX();
		float GetY();

	private:
		float m_X;
		float m_Y;
	};
}

#endif // !VECTOR2D_H