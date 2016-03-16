#ifndef _CONTEXT_H
#define _CONTEXT_H

//Foward Declaration
class Window;

//Defines
#define WINDOW (context.pWnd)

struct Context
{
	float dTime;

	Window* pWnd;
};
#endif