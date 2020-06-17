#include <iostream>
#include "Common/Application.h"

int main(int argc, char* argv[])
{
	Application* application = new Application(800, 600, "Path2D", 30);
	application->InitializeNodes();
	application->InitializeAgent();
	application->Run();
	delete application;
	return 0;
}