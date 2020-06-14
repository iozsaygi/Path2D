#include "assert.h"
#include "Agent.h"

namespace Path2D
{
	void Agent::CalculatePath(Node* startingNode, Node* endingNode)
	{
		// TO DO: Calculate the path between given nodes and return the path as an vector.
		startingNode->SetIsVisited(true);
		endingNode->SetIsVisited(true);
	}
}