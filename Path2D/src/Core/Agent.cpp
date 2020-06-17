#include <iostream>
#include <algorithm>
#include <assert.h>
#include "Agent.h"

namespace Path2D
{
	std::vector<Node*> Agent::CalculatePath(Node* startingNode, Node* endingNode) 
	{
		assert(startingNode != nullptr);
		assert(endingNode != nullptr);

		// Initialize our lists.
		auto open = std::vector<Node*>();
		auto closed = std::vector<Node*>();

		// Add start node to open list.
		open.push_back(startingNode);

		// While open list is not empty.
		while (open.size() > 0)
		{
			// Get the node with lowest FCost in open list.
			Node* current = GetNodeWithLowestFCost(open);

			// Remove current from open list.
			open.erase(std::remove(open.begin(), open.end(), current), open.end());
			// Add current to the closed list.
			current->SetIsVisited(true);
			closed.push_back(current);

			// Check if current node is the target (ending) node.
			if (current == endingNode)
			{
				// Path found.
				break;
			}

			// Cycle through for each neighbor of the current node.
			for (Node* neighborNode : current->GetNeighborNodes())
			{
				// If neighbor is blocked or it is in the closed list: Ignore it and continue to looping.
				if (neighborNode->GetIsBlocked() || std::count(closed.begin(), closed.end(), neighborNode))
					continue;

				// If new path to the neighbor is shorter or neighbor is not in open list.
				float movementCostToNeighbor = current->GetGCost() + Vector2D::ManhattanDistance(current->GetPosition(), neighborNode->GetPosition());
				if (movementCostToNeighbor < neighborNode->GetGCost() || std::find(open.begin(), open.end(), neighborNode) == open.end())
				{
					neighborNode->SetGCost(movementCostToNeighbor);
					neighborNode->SetHCost(Vector2D::ManhattanDistance(neighborNode->GetPosition(), endingNode->GetPosition()));
					neighborNode->SetParent(current);

					if (std::find(open.begin(), open.end(), neighborNode) == open.end())
						open.push_back(neighborNode);
				}
			}
		}

		return RetracePath(startingNode, endingNode);
	}

	Node* Agent::GetNodeWithLowestFCost(std::vector<Node*>& nodes)
	{
		Node* nodeWithLowestFCost = nodes[0];
		for (auto node : nodes)
		{
			if (node->GetFCost() < nodeWithLowestFCost->GetFCost())
				nodeWithLowestFCost = node;
		}

		return nodeWithLowestFCost;
	}

	std::vector<Node*> Agent::RetracePath(Node* startingNode, Node* endingNode)
	{
		assert(startingNode != nullptr);
		assert(endingNode != nullptr);

		auto path = std::vector<Node*>();
		Node* currentNode = endingNode;

		while (currentNode != startingNode)
		{
			path.push_back(currentNode);
			currentNode = currentNode->GetParent();
		}

		std::reverse(path.begin(), path.end());
		return path;
	}
}