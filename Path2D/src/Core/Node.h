#ifndef NODE_H
#define NODE_H

#include <vector>
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
		float GetGCost();
		void SetGCost(float gCost);
		void SetHCost(float hCost);
		float GetFCost();
		bool GetIsVisited();
		bool GetIsBlocked();
		bool GetIsStartingNode();
		bool GetIsEndingNode();
		void SetIsVisited(bool isVisited);
		void SetIsBlocked(bool isBlocked);
		void SetIsStartingNode(bool isStartingNode);
		void SetIsEndingNode(bool isEndingNode);
		void AddNeighborNode(Node* node);
		std::vector<Node*>& GetNeighborNodes();
		void UpdateCosts(Node* startingNode, Node* endingNode);
		Node* GetParent();
		void SetParent(Node* node);
		bool GetIsOnPath();
		void SetIsOnPath(bool isOnPath);

	private:
		float m_GCost;
		float m_HCost;
		bool m_IsVisited;
		bool m_IsBlocked;
		bool m_IsStartingNode;
		bool m_IsEndingNode;
		bool m_IsOnPath = false;
		Vector2D m_Position;
		std::vector<Node*> m_NeighborNodes;
		Node* m_Parent = nullptr;
	};
}

#endif // !NODE_H