#include "EngineTimer.h"

//#include "MemeoryManager.h"
//#include "Logger.h"

#include "Timer.h"

#ifndef _DELETEMACROS_H
	#include "deletemacros.h"
#endif

EngineTimer::EngineTimer(const EngineTimerData& data) : System(data)
	, m_pWorldTimer(nullptr)
{
}

EngineTimer::~EngineTimer()
{
}

/*#pragma region New & Delete Operator
void* EngineTimer::operator new(szie_t size)
{
return MEMORYMANAGER->Alloc(size);
}
void EngineTimer::operator delete(void* pdelete)
{
return MEMORYMANAGER->Free(pdelete);
}
#pragma endregion*/

bool EngineTimer::Initialize()
{
	System::Initialize();

	m_pWorldTimer = new Timer(_T("WorldTimer"));
#if defined(DEBUG) | defined(_DEBUG)
	if (!m_pWorldTimer->Initialize())
		return false;
	m_pWorldTimer->SetInitialized();
	if (!m_pWorldTimer->PostInitialized())
		return false;
	m_pWorldTimer->SetPostInitialized();
#else
	m_pWorldTimer->Initialize();
	m_pWorldTimer->SetInitialized();
	m_pWorldTimer->PostInitialized();
	m_pWorldTimer->SetPostInitialized();
#endif

	//Logger::Log(_T("Engine Timer Initialized"), LOGTYPE_INFO, false);
	return true;
}

bool EngineTimer::Update(Context &context)
{
	System::Update(context);

	if (m_pWorldTimer)
	{
		m_pWorldTimer->Update(context);
		context.dTime = m_pWorldTimer->GetDeltaTime();
	}

	for (Timer* timer : m_vecTimers)
		timer->Update(context);

	return true;
}

bool EngineTimer::Shutdown()
{
	System::ShutDown();

	SafeDelete(m_pWorldTimer);

	for (Timer* timer : m_vecTimers)
		SafeDelete(timer);

	return true;
}
