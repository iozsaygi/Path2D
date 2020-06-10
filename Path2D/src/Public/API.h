#ifndef API_H
#define API_H

#ifdef PATH2D_PLATFORM_WINDOWS
#ifdef PATH2D_BUILD_DLL
#define PATH2D_API __declspec(dllexport)
#else
#define PATH2D_API __declspec(dllimport)
#endif // PATH2D_BUILD_DLL
#endif // PATH2D_PLATFORM_WINDOWS

#endif // !API_H