#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include <vector>
#include <SDL.h>
#include "Path2D.h"

class Application
{
public:
	Application(int windowWidth, int windowHeight, const std::string& windowTitle, int targetFrameRate);
	~Application();

	void InitializeNodes();
	void InitializeAgent();
	void Run();
	void Render();

private:
	static bool m_IsRunning;
	static int m_TargetFrameRate;
	static SDL_Renderer* m_Renderer;
	static SDL_Window* m_Window;

	std::vector<Path2D::Node*> m_Nodes;
	std::vector<Path2D::Node*> m_Path;
	Path2D::Node* m_StartingNode = nullptr;
	Path2D::Node* m_EndingNode = nullptr;

	SDL_Color GetNodeRenderColor(Path2D::Node* node);
};

#endif // !APPLICATION_H