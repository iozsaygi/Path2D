#include <iostream>
#include "Application.h"
#include "Utilities/Physics.h"

#define WORLD_WIDTH 10
#define WORLD_HEIGHT 10

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
	{
		delete node;
	}

	m_Nodes.clear();
	m_IsRunning = false;

	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void Application::InitializeNodes()
{
	for (int y = 0; y < WORLD_HEIGHT; y++)
	{
		for (int x = 0; x < WORLD_WIDTH; x++)
		{
			Path2D::Vector2D position((x * (32 + 5)) + 210, (y * (32 + 5)) + 120);
			m_Nodes.push_back(new Path2D::Node(position));
		}
	}

	// Setup starting and ending nodes.
	m_StartingNode = m_Nodes[11];
	m_EndingNode = m_Nodes[5];

	m_StartingNode->SetIsStartingNode(true);
	m_EndingNode->SetIsEndingNode(true);

	// Setup some nodes as blocked.
	m_Nodes[3]->SetIsBlocked(true);
	m_Nodes[13]->SetIsBlocked(true);
	m_Nodes[14]->SetIsBlocked(true);
	m_Nodes[24]->SetIsBlocked(true);
	m_Nodes[25]->SetIsBlocked(true);
	m_Nodes[26]->SetIsBlocked(true);
	m_Nodes[27]->SetIsBlocked(true);
	m_Nodes[29]->SetIsBlocked(true);
	m_Nodes[35]->SetIsBlocked(true);
	m_Nodes[45]->SetIsBlocked(true);
	m_Nodes[55]->SetIsBlocked(true);
	m_Nodes[56]->SetIsBlocked(true);
	m_Nodes[57]->SetIsBlocked(true);
	m_Nodes[67]->SetIsBlocked(true);
	m_Nodes[71]->SetIsBlocked(true);
	m_Nodes[72]->SetIsBlocked(true);
	m_Nodes[81]->SetIsBlocked(true);

	// Setup the neighbor nodes.
	for (int i = 0; i < m_Nodes.size(); i++)
	{
		if (i % WORLD_WIDTH != 0)
		{
			m_Nodes[i]->AddNeighborNode(m_Nodes[i - 1]);
		}

		if (i % (WORLD_WIDTH - 1) != 0 || i == 0)
		{
			m_Nodes[i]->AddNeighborNode(m_Nodes[i + 1]);
		}

		if (i - WORLD_WIDTH >= 0)
		{
			m_Nodes[i]->AddNeighborNode(m_Nodes[i - WORLD_WIDTH]);
		}

		if (i + WORLD_WIDTH < m_Nodes.size())
		{
			m_Nodes[i]->AddNeighborNode(m_Nodes[i + WORLD_WIDTH]);
		}

		// Had to do this at somewhere.
		m_Nodes[i]->UpdateCosts(m_StartingNode, m_EndingNode);
	}
}

void Application::InitializeAgent()
{
	// Create the agent and also set the start and ending nodes.
	Path2D::Agent agent;
	m_Path = agent.CalculatePath(m_StartingNode, m_EndingNode);

	for (Path2D::Node* node : m_Path)
		node->SetIsOnPath(true);
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

		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			m_IsRunning = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				// Cycle through each node and find if user clicked inside any of it.
				for (int i = 0; i < m_Nodes.size(); i++)
				{
					Path2D::Vector2D nodePosition = m_Nodes[i]->GetPosition();
					SDL_Rect nodeRectangle;
					nodeRectangle.x = nodePosition.GetX();
					nodeRectangle.y = nodePosition.GetY();
					nodeRectangle.w = 32;
					nodeRectangle.h = 32;
					int mouseX, mouseY = 0;
					SDL_GetMouseState(&mouseX, &mouseY);
					if (IsPositionInsideRectangle(mouseX, mouseY, &nodeRectangle))
					{
						if (!m_Nodes[i]->GetIsStartingNode() && !m_Nodes[i]->GetIsEndingNode())
						{
							for (Path2D::Node* node : m_Path)
								node->SetIsOnPath(false);

							// Clear the path.
							m_Path.clear();

							m_Nodes[i]->SetIsBlocked(true);
							// Recalculate the path.
							Path2D::Agent agent;
							m_Path = agent.CalculatePath(m_StartingNode, m_EndingNode);

							for (Path2D::Node* node : m_Path)
								node->SetIsOnPath(true);
						}
					}
				}
			}
			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				// Cycle through each node and find if user clicked inside any of it.
				for (int i = 0; i < m_Nodes.size(); i++)
				{
					Path2D::Vector2D nodePosition = m_Nodes[i]->GetPosition();
					SDL_Rect nodeRectangle;
					nodeRectangle.x = nodePosition.GetX();
					nodeRectangle.y = nodePosition.GetY();
					nodeRectangle.w = 32;
					nodeRectangle.h = 32;
					int mouseX, mouseY = 0;
					SDL_GetMouseState(&mouseX, &mouseY);
					if (IsPositionInsideRectangle(mouseX, mouseY, &nodeRectangle))
					{
						for (Path2D::Node* node : m_Path)
							node->SetIsOnPath(false);

						// Clear the path.
						m_Path.clear();

						m_Nodes[i]->SetIsBlocked(false);
						// Recalculate the path.
						Path2D::Agent agent;
						m_Path = agent.CalculatePath(m_StartingNode, m_EndingNode);

						for (Path2D::Node* node : m_Path)
							node->SetIsOnPath(true);
					}
				}
			}
			break;
		}

		// Render process
		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
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
	for (Path2D::Node* node : m_Nodes)
	{
		SDL_Color renderColor = GetNodeRenderColor(node);
		SDL_SetRenderDrawColor(m_Renderer, renderColor.r, renderColor.g, renderColor.b, renderColor.a);

		SDL_Rect nodeBounds;
		nodeBounds.x = node->GetPosition().GetX();
		nodeBounds.y = node->GetPosition().GetY();
		nodeBounds.w = 32;
		nodeBounds.h = 32;

		SDL_RenderFillRect(m_Renderer, &nodeBounds);
	}
}

SDL_Color Application::GetNodeRenderColor(Path2D::Node* node)
{
	if (node != nullptr)
	{
		if (node->GetIsOnPath() && !node->GetIsEndingNode())
		{
			SDL_Color green;
			green.r = 0;
			green.g = 255;
			green.b = 0;
			green.a = 255;
			return green;
		}

		if (node->GetIsBlocked())
		{
			SDL_Color red;
			red.r = 255;
			red.g = 0;
			red.b = 0;
			red.a = 255;
			return red;
		}

		if (node->GetIsStartingNode())
		{
			SDL_Color blue;
			blue.r = 0;
			blue.g = 0;
			blue.b = 255;
			blue.a = 255;
			return blue;
		}

		if (node->GetIsEndingNode())
		{
			SDL_Color yellow;
			yellow.r = 255;
			yellow.g = 255;
			yellow.b = 0;
			yellow.a = 255;
			return yellow;
		}

		if (node->GetIsVisited())
		{
			SDL_Color white;
			white.r = 255;
			white.g = 255;
			white.b = 255;
			white.a = 255;
			return white;
		}
	}

	SDL_Color unVisited;
	unVisited.r = 150;
	unVisited.g = 150;
	unVisited.b = 150;
	unVisited.a = 255;
	return unVisited;
}