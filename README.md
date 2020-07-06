<p align="center">
  <a href="#"><img src="https://github.com/iozsaygi/Path2D/blob/master/media/preview.gif"/></a>
</p>

## About
Path2D is a simple pathfinding library that uses A* search algorithm to calculate shortest path between 2 locations (nodes).
Visualization tool is included with the library (which is written in SDL with C++) but it's not that convenient at the moment.

## Visualization Tool Instructions
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

## Building
* Download and install [Visual Studio](https://visualstudio.microsoft.com/), make sure to check "Desktop development with C++" workload in Visual Studio Installer
* Download [SDL2](https://www.libsdl.org/) and extract it in folder called "dependencies"
* Clone the repository ```git clone https://github.com/iozsaygi/Path2D```
* Put the dependencies folder near project's solution file
* Open up the .sln file and make sure the platform is x86
* Build the "Sandbox" project

## License
[MIT License](https://github.com/iozsaygi/Path2D/blob/master/LICENSE)
