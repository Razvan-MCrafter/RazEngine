#pragma once

#include <Windows.h>
#include <map>
#include "context.h"

//Foward Declaration
class System;
class Game;

enum SystemType;

//Enumaration
enum EngineState
{
	Invalid,
	Constructing,
	Initializing,
	Running,
	ShuttingDown,
	Destroying
};

class Engine
{
public:
	Engine();
	~Engine();

	int RunLoop();

	//void* operator new(size_t size);
	//void operator delete(void* pdelete);

	static EngineState GetEngineState()
	{
		return m_EngineState;
	}

private:

	int Initialize();
	int Draw(Context& context);
	int Update(Context& context);
	int ShutDown();

	//Check if we need to resize the screen
	void CheckResize();
	//Add a core system to the engine
	int AddSystem(System* psys);
	//Retrieve a core system from the engine
	template<typename T>
	T* GetSystem(SystemType systype)
	{
		T* psys = static_cast<T*>(m_mapSystems[systype]);
		if (!psys)
		{
			//Logger::Log("System is not valid!");
			return nullptr;
		}

		return psys;
	}

	//Create the game instance
	Game* CreateGame();

	std::map<SystemType, System*> m_mapSystems;
	static EngineState m_EngineState;
};