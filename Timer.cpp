#include "Timer.h"

//#include "MemeoryManager.h"
//#include "Logger.h"

Timer::Timer(const std::tstring &name) : UObject(name)
{
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
	return true;
}

bool Timer::PostInitialize()
{
	return true;
}

bool Timer::Update(Context &context)
{
	return true;
}

bool Timer::Shutdown()
{
	return true;
}

float Timer::GetTotalTime()
{
	return 0.0f;
}

float Timer::GetDeltaTime()
{
	return 0.0f;
}

void Timer::Reset()
{
}

void Timer::Start()
{
}

void Timer::Stop()
{
}
