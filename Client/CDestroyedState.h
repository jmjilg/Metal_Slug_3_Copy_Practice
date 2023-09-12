#pragma once
#include "CState.h"
class CDestroyedState :
	public CState
{
public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	CDestroyedState();
	~CDestroyedState();


};

