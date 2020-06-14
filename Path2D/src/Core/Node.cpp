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
	}

	Vector2D& Node::GetPosition()
	{
		return m_Position;
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
}