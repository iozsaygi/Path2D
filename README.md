<p align="center">
  <a href="#"><img src="https://github.com/iozsaygi/Path2D/blob/master/media/preview.gif"/></a>
</p>

## About
Path2D is a simple pathfinding library that uses A* search algorithm to calculate shortest path between 2 locations (nodes).
Visualization tool is included with the library (which is written in SDL with C++) but it's not that convenient at the moment.

## Visualization tool instructions
* Blue node is the starting node
* Red nodes represents the blocked nodes
* Yellow node is the ending node
* White nodes represents the visited nodes
* Gray nodes represents the unvisited nodes
* Green nodes represents the nodes in optimal path
* Left click on node to mark it as blocked
* Right click on node to mark it as unblocked

## Dependencies
* [SDL2](https://www.libsdl.org/)

## Example code
```cpp
#include <vector>
#include "Path2D.h"

// Define the width and height of the world
#define  WORLD_WIDTH 10
#define WORLD_HEIGHT 10

int main(int argc, char* argv[])
{
	// Create the nodes list
	auto nodes = std::vector<Path2D::Node*>();

	// Add nodes to the list
	for (int y = 0; y < WORLD_HEIGHT; y++)
	{
		for (int x = 0; x < WORLD_WIDTH; x++)
		{
			Path2D::Vector2D position(x, y);
			nodes.push_back(new Path2D::Node(position));
		}
	}

	// Setup starting and ending nodes
	Path2D::Node* startingNode = nodes[11];
	Path2D::Node* endingNode = nodes[55];
	startingNode->SetIsStartingNode(true);
	endingNode->SetIsEndingNode(true);

	// Setup some obstacles (Optional)
	nodes[3]->SetIsBlocked(true);
	nodes[13]->SetIsBlocked(true);
	nodes[14]->SetIsBlocked(true);

	// Setup the neighbor nodes
	for (int i = 0; i < nodes.size(); i++)
	{
		if (i % WORLD_WIDTH != 0)
			nodes[i]->AddNeighborNode(nodes[i - 1]);

		if (i % (WORLD_WIDTH - 1) != 0 || i == 0)
			nodes[i]->AddNeighborNode(nodes[i + 1]);

		if (i - WORLD_WIDTH >= 0)
			nodes[i]->AddNeighborNode(nodes[i - WORLD_WIDTH]);

		if (i + WORLD_WIDTH < nodes.size())
			nodes[i]->AddNeighborNode(nodes[i + WORLD_WIDTH]);

		// Initialize the costs of each node
		nodes[i]->UpdateCosts(startingNode, endingNode);
	}

	// Create our agent to run algorithm (Optimal path will be stored in "path" vector)
	Path2D::Agent agent;
	std::vector<Path2D::Node*> path = agent.CalculatePath(startingNode, endingNode);

	return 0;
}
```

## Building
* Windows
  * Download and install [Visual Studio](https://visualstudio.microsoft.com/), make sure to check "Desktop development with C++" workload in Visual Studio Installer
  * Download [SDL2](https://www.libsdl.org/) and extract it in folder called "dependencies"
  * Make sure to rename extracted folder to "SDL2"
  * Clone the repository ```git clone https://github.com/iozsaygi/Path2D```
  * Put the dependencies folder near project's solution file
  * Open up the .sln file and make sure the platform is x86
  * Build the "Sandbox" project

## License
[MIT License](https://github.com/iozsaygi/Path2D/blob/master/LICENSE)
