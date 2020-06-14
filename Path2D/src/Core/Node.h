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
		Node(const Vector2D& position);

		Vector2D& GetPosition();
		float GetFCost();
		bool GetIsVisited();
		bool GetIsBlocked();
		bool GetIsStartingNode();
		bool GetIsEndingNode();
		void SetIsVisited(bool isVisited);
		void SetIsBlocked(bool isBlocked);
		void SetIsStartingNode(bool isStartingNode);
		void SetIsEndingNode(bool isEndingNode);

	private:
		float m_GCost;
		float m_HCost;
		bool m_IsVisited;
		bool m_IsBlocked;
		bool m_IsStartingNode;
		bool m_IsEndingNode;

		Vector2D m_Position;
	};
}

#endif // !NODE_H