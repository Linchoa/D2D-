#pragma once
#include "Scene.h"
class CMenuScene :
	public CScene
{
public:
	CMenuScene();
	virtual ~CMenuScene();

public:
	void	Initialize(void);
	void	Update(void);
	void	Late_Update(void);
	void	Render(HDC hDC);
	void	Release(void);
};

