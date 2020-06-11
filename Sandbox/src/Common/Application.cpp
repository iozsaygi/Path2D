#include "Application.h"

bool Application::m_IsRunning = false;
int Application::m_TargetFrameRate = 0;
SDL_Renderer* Application::m_Renderer = nullptr;
SDL_Window* Application::m_Window = nullptr;

Application::Application(int windowWidth, int windowHeight, const std::string& windowTitle, int targetFrameRate)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return;
	}

	if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, SDL_WINDOW_SHOWN, &m_Window, &m_Renderer))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
		SDL_Quit();
		return;
	}

	SDL_SetWindowPosition(m_Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_SetWindowTitle(m_Window, windowTitle.c_str());
	SDL_SetWindowResizable(m_Window, SDL_FALSE);

	m_TargetFrameRate = targetFrameRate;
	m_IsRunning = true;

	m_Nodes = std::vector<Path2D::Node*>();
}

Application::~Application()
{
	for (Path2D::Node* node : m_Nodes)
		delete node;

	m_Nodes.clear();
	m_IsRunning = false;

	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void Application::InitializeNodes(int worldWidth, int worldHeight)
{
	for (int y = 0; y < worldHeight; y++)
	{
		for (int x = 0; x < worldWidth; x++)
		{
			Path2D::Vector2D position(x * 32, y * 32);
			Path2D::Vector2D scale(32, 32);
			m_Nodes.push_back(new Path2D::Node(position, scale));
		}
	}
}

void Application::Run()
{
	const int frameDelay = 1000 / m_TargetFrameRate;
	Uint32 frameStart;
	int frameTime;

	SDL_Event event;

	while (m_IsRunning)
	{
		frameStart = SDL_GetTicks();

		// Handle events
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			m_IsRunning = false;

		// Render process
		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 1);
		SDL_RenderClear(m_Renderer);
		
		Render();

		SDL_RenderPresent(m_Renderer);

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}
}

void Application::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);

	for (Path2D::Node* node : m_Nodes)
	{
		SDL_Rect nodeBounds;
		nodeBounds.x = node->GetPosition().GetX();
		nodeBounds.y = node->GetPosition().GetY();
		nodeBounds.w = node->GetScale().GetX();
		nodeBounds.h = node->GetScale().GetY();

		SDL_RenderDrawRect(m_Renderer, &nodeBounds);
	}
}