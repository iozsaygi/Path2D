#include <assert.h>
#include "Node.h"

namespace Path2D
{
	Node::Node()
	{
		m_GCost = 0.0f;
		m_HCost = 0.0f;
		m_Position = Vector2D::Zero();
		m_IsVisited = false;
		m_IsBlocked = false;
		m_IsStartingNode = false;
		m_IsEndingNode = false;
		m_NeighborNodes = std::vector<Node*>();
	}

	Node::Node(const Vector2D& position)
	{
		m_GCost = 0.0f;
		m_HCost = 0.0f;
		m_Position = position;
		m_IsVisited = false;
		m_IsBlocked = false;
		m_IsStartingNode = false;
		m_IsEndingNode = false;
		m_NeighborNodes = std::vector<Node*>();
	}

	Vector2D& Node::GetPosition()
	{
		return m_Position;
	}

	float Node::GetGCost()
	{
		return m_GCost;
	}

	void Node::SetGCost(float gCost)
	{
		m_GCost = gCost;
	}

	void Node::SetHCost(float hCost)
	{
		m_HCost = hCost;
	}

	float Node::GetFCost()
	{
		return m_GCost + m_HCost;
	}

	bool Node::GetIsVisited()
	{
		return m_IsVisited;
	}

	bool Node::GetIsBlocked()
	{
		return m_IsBlocked;
	}

	bool Node::GetIsStartingNode()
	{
		return m_IsStartingNode;
	}

	bool Node::GetIsEndingNode()
	{
		return m_IsEndingNode;
	}

	void Node::SetIsVisited(bool isVisited)
	{
		if (m_IsVisited != isVisited)
			m_IsVisited = isVisited;
	}

	void Node::SetIsBlocked(bool isBlocked)
	{
		if (m_IsBlocked != isBlocked)
			m_IsBlocked = isBlocked;
	}

	void Node::SetIsStartingNode(bool isStartingNode)
	{
		if (m_IsStartingNode != isStartingNode)
			m_IsStartingNode = isStartingNode;
	}

	void Node::SetIsEndingNode(bool isEndingNode)
	{
		if (m_IsEndingNode != isEndingNode)
			m_IsEndingNode = isEndingNode;
	}

	void Node::AddNeighborNode(Node* node)
	{
		assert(node != nullptr);

		if (!std::count(m_NeighborNodes.begin(), m_NeighborNodes.end(), node))
			m_NeighborNodes.push_back(node);
	}

	std::vector<Node*>& Node::GetNeighborNodes()
	{
		return m_NeighborNodes;
	}

	void Node::UpdateCosts(Node* startingNode, Node* endingNode)
	{
		assert(startingNode != nullptr);
		assert(endingNode != nullptr);
		m_GCost = Vector2D::ManhattanDistance(GetPosition(), startingNode->GetPosition());
		m_HCost = Vector2D::ManhattanDistance(GetPosition(), endingNode->GetPosition());
	}

	Node* Node::GetParent()
	{
		return m_Parent;
	}

	void Node::SetParent(Node* node)
	{
		assert(node != nullptr);
		m_Parent = node;
	}
}