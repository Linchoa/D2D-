#pragma once
#include "Monster.h"
class CCrow :
	public CMonster
{
public:
	CCrow();
	virtual ~CCrow();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

