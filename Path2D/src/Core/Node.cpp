#include "Node.h"

namespace Path2D
{
	Node::Node()
	{
		m_GCost = 0.0f;
		m_HCost = 0.0f;
		m_Position = Vector2D::Zero();
		m_Scale = Vector2D::One();
	}

	Node::Node(const Vector2D position, const Vector2D scale)
	{
		m_GCost = 0.0f;
		m_HCost = 0.0f;
		m_Position = position;
		m_Scale = scale;
	}

	Vector2D& Node::GetPosition()
	{
		return m_Position;
	}

	Vector2D& Node::GetScale()
	{
		return m_Scale;
	}

	float Node::GetFCost()
	{
		return m_GCost + m_HCost;
	}
}