#pragma once

#include "Obj.h"

class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);
};

// 1. 마우스 포인터를 따라다니는 플레이어를 만들어라(단, 벡터 뺄셈이 아닌 내적을 이용해서 만들어라)

// 2. 증명 숙제 해오기








// 내적과 외적의 필수 조건 : 반드시 두 방향벡터여야 성립

// 만약, 벡터의 내적을 이용하여 스칼라를 구하고 그 스칼라로 각도를 만들어내려면 두 방향 벡터는 단위 벡터여야 한다.

//벡터의 내적 : U(x, y, z) V(X`, Y`, Z`)	-> x * X` + y * Y` + z * Z`