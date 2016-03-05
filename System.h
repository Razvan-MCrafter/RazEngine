#pragma once

#include "UObject.h"

//Enumaration
enum SystemType
{
	Sys_Windows,
	Sys_Game,
	Sys_Input,
	Sys_Graphics,
	Sys_GameTimer
};

//Structs
struct SystemData
{

};

class System : public UObject
{
public:
	System();
	virtual ~System();

	SystemType GetType() { return m_SystemType; }

protected:

	SystemType m_SystemType;
};

