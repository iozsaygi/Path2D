#ifndef NODE_H
#define NODE_H

#include "Public/API.h"
#include "Math/Vector2D.h"

namespace Path2D
{
	// Represents the "tile" for agents to use
	class PATH2D_API Node
	{
	public:
		Node();
		Node(const Vector2D position);

		Vector2D& GetPosition();
		float GetFCost();

	private:
		float m_GCost;
		float m_HCost;

		Vector2D m_Position;
	};
}

#endif // !NODE_H