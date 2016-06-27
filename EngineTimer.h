#ifndef _ENGINETIMER_H
#define _ENGINETIMER_H

//Include Files
#include "System.h"

//Additional Inlucde Files
#ifndef _VECTOR_
	#include <vector>
#endif
#ifndef _STRING_H
	#include "string.h"
#endif

//Foward Declaration
class Timer;

//Structs
struct EngineTimerData : SystemData
{
	EngineTimerData() : SystemData(SystemType::Sys_EngineTimer)
	{}
};

class EngineTimer : public System
{
	friend class Engine;
public:
	//Destructor
	virtual ~EngineTimer();

	Timer* GetWorldTimer() { return m_pWorldTimer; }

	void AddTimer(const std::tstring &name);
	Timer* GetTimer(const std::tstring &name);

	//void* operator new(size_t size);
	//void operator delete(void* pdelete);

	//Methods
	bool Initialize();
	bool Update(Context &context);
	bool Shutdown();

protected:
	//Constructor
	EngineTimer(const EngineTimerData &data);

private:
	//Methods
	//Members
	Timer* m_pWorldTimer;
	std::vector<Timer*> m_vecTimers;
};

#endif
