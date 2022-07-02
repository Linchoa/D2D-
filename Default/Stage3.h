#pragma once
#include "Scene.h"
class CStage3 :
	public CScene
{
public:
	CStage3();
	virtual ~CStage3();

public:
	void	Initialize(void);
	void	Update(void);
	void	Late_Update(void);
	void	Render(HDC hDC);
	void	Release(void);
};

