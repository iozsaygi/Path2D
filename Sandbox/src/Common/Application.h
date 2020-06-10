#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include <SDL.h>

class Application
{
public:
	Application(int windowWidth, int windowHeight, const std::string& windowTitle, int targetFrameRate);
	~Application();

	void Run();

private:
	static bool m_IsRunning;
	static int m_TargetFrameRate;
	static SDL_Renderer* m_Renderer;
	static SDL_Window* m_Window;
};

#endif // !APPLICATION_H