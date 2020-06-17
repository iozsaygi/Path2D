#ifndef AGENT_H
#define AGENT_H

#include <vector>
#include "Public/API.h"
#include "Core/Node.h"

namespace Path2D
{
	class PATH2D_API Agent
	{
	public:
		std::vector<Node*> CalculatePath(Node* startingNode, Node* endingNode);

	private:
		Node* GetNodeWithLowestFCost(std::vector<Node*>& nodes);
		std::vector<Node*> RetracePath(Node* startingNode, Node* endingNode);
	};
}

#endif // !AGENT_H