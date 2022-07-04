#pragma once
#include "Scene.h"
class CStage1 :
	public CScene
{
public:
	CStage1();
	virtual ~CStage1();

public:
	void	Initialize(void);
	void	Update(void);
	void	Late_Update(void);
	void	Render(HDC hDC);
	void	Release(void);

private:
	DWORD		m_dwMonsterTime;
	int			m_iMonsterTimer;
};

