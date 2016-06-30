#include "Timer.h"

#ifndef _WINDOWS
	#include <Windows.h>
#endif

//#include "MemeoryManager.h"
//#include "Logger.h"

#ifndef _CTIME_
	#include <ctime>
#endif

Timer::Timer(const std::tstring &name) : UObject(name)
	, m_SecondsPerCount(0.0)
	, m_DeltaTime(-1.0)

	, m_BaseTime(0)
	, m_PauseTime(0)
	, m_PrevTime(0)
	, m_CurrTime(0)
	, m_bStopped(false)
{
	__int64 countpersec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countpersec);
	m_SecondsPerCount = 1.0 / (double)countpersec;
}

Timer::~Timer()
{
}

/*#pragma region New & Delete Operator
void* Timer::operator new(szie_t size)
{
	return MEMORYMANAGER->Alloc(size);
}
void Timer::operator delete(void* pdelete)
{
	return MEMORYMANAGER->Free(pdelete);
}
#pragma endregion*/

bool Timer::Initialize()
{
	UObject::Initialize();

	Start();

	return true;
}

bool Timer::PostInitialize()
{
	return UObject::PostInitialize();
}

bool Timer::Update(Context &context)
{
	UObject::Update(context);

	if (m_bStopped)
	{
		m_DeltaTime = 0.0;
		return true;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_CurrTime = currTime;

	//Time difference betwen ths frame and the previous one
	m_DeltaTime = (m_CurrTime - m_PrevTime) * m_SecondsPerCount;

	//Prepare the next frame
	m_PrevTime = m_CurrTime;

	//Force nonnegative
	//The DXSKS's CDZUTTimer metions that if the processor goes into power save mode or we get shuffled to another processes
	//then DeltaTime can be negative
	if (m_DeltaTime < 0.0)
		m_DeltaTime = 0.0;

	return true;
}

bool Timer::ShutDown()
{
	UObject::ShutDown();

	Stop();

	return true;
}

float Timer::GetTotalTime()
{
	if (m_bStopped)
		return (float)((m_StopTime - m_BaseTime) * m_SecondsPerCount);

	else return (float)(((m_CurrTime - m_PauseTime) - m_BaseTime) * m_SecondsPerCount);
}

float Timer::GetDeltaTime()
{
	return (float)m_DeltaTime;
}

void Timer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_BaseTime = currTime;
	m_PrevTime = currTime;
	m_StopTime = 0;

	m_bStopped = false;
}

void Timer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);
	m_PrevTime = startTime;

	//If we are resuming the timer from a steooped state ...
	if (m_bStopped)
	{
		//then accumulate the paused tme
		m_PauseTime += (startTime - m_StopTime);

		//Since we are starting the timer back up,
		//the current previous time is not valid,
		//as it occured while paused,
		//So reset it to the current time
		m_PrevTime = startTime;

		//no longer stopped
		m_StopTime = 0;
		m_bStopped = false;
	}
}

void Timer::Stop()
{
	//If we are already stopped, then don't do anything
	
	if (m_bStopped)
		return;

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	//Save the time we stopped at
	//and set the boolean flag indication the timer stopped
	m_StopTime = currTime;
	m_bStopped = false;
}
