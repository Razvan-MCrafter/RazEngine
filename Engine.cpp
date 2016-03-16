#include "Engine.h"

//Additional include files
#include "System.h"
#include "Game.h"
#include "Window.h"

#ifndef _DELETEMACRO_H
	#include "deletemacros.h"
#endif
#ifndef _STRING_H
	#include "string.h"
#endif

EngineState Engine::m_EngineState = EngineState::Invalid;

Engine::Engine()
{
	m_EngineState = EngineState::Constructing;
}
Engine::~Engine()
{
	m_EngineState = EngineState::Destroying;
}

//Public Methods
int Engine::RunLoop()
{
	Context context;

	if (!this->Initialize())
		return 0;

	srand(GetTickCount());

	MSG msg = {};

	m_EngineState = EngineState::Running;

	while (msg.message != WM_QUIT && m_EngineState == EngineState::Running)
	{
		//CheckResize();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		this->Update(context);
		this->Draw(context);
	}

	//Logger::Log("Ending the program");
	//Logger::WriteLogFile();

	if (!this->ShutDown())
		return 0;

	return msg.wParam;
}

//Private Methods
int Engine::Initialize()
{
	m_EngineState = EngineState::Initializing;

	Game* game = CreateGame();

	if (!game)
		return false;

	//Add some systems
	if (!AddSystem(new Window(WindowData(640, 480))))
		return false;

	//Initialize
	if (!m_mapSystems[SystemType::Sys_Window]->Initialize())
		return false;
	
	return true;
}
int Engine::Draw(Context& context)
{
	return true;
}
int Engine::Update(Context& context)
{
	for (std::pair<SystemType, System*> pSys : m_mapSystems)
	{
		if (!pSys.second)
			continue;

		pSys.second->Update(context);
	}
	return true;
}
int Engine::ShutDown()
{
	m_EngineState = EngineState::ShuttingDown;

	for (std::pair<SystemType, System*> psys : m_mapSystems)
	{
		/*if (!psys.second->ShutDown())
		{
			//Logger::Log("Failed the shutdown system" + psys->GetSystemType());
			continue;
		}*/

		SafeDelete(psys.second);
	}

	return true;
}

int Engine::AddSystem(System* psys)
{
	auto element = m_mapSystems.insert(std::make_pair(psys->GetType(), psys));
	if (element.second)
		return true;

	return  false;
}

Game* Engine::CreateGame()
{
	if (!AddSystem(new Game(GameData())))
		return nullptr;

	Game* game = GetSystem<Game>(SystemType::Sys_Game);
	if (!game)
		return nullptr;

	//if (!game->Initialize())
		//return nullptr;

	return game;
}