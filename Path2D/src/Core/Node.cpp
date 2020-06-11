#include "Node.h"

namespace Path2D
{
	Node::Node()
	{
		m_GCost = 0.0f;
		m_HCost = 0.0f;
		m_Position = Vector2D::Zero();
	}

	Node::Node(const Vector2D position)
	{
		m_GCost = 0.0f;
		m_HCost = 0.0f;
		m_Position = position;
	}

	Vector2D& Node::GetPosition()
	{
		return m_Position;
	}

	float Node::GetFCost()
	{
		return m_GCost + m_HCost;
	}
}