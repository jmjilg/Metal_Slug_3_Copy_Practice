#pragma once
#include "CState.h"
class CClawing :
	public CState
{
private:


public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	CClawing();
	~CClawing();
};