#pragma once
#include "Scene.h"
#include "SC_Obj.h"
#include "S2_Line.h"
class CStage2 :
	public CScene
{
public:
	

public:
	CStage2();
	virtual ~CStage2();

public:
	void	Initialize(void);
	void	Update(void);
	void	Late_Update(void);
	void	Render(HDC hDC);
	void	Release(void);
	void	Key_Input(void);
private:
	int m_iClickNumber;
	LINEPOINT m_Line[2];
	list<CS2_Line*>*				m_pLineList;
	LINEID	 m_lineID;
private:
	int	m_iPage;
private:
	float m_ftime;
	int	  m_iScore;
};



template<typename T>
class CFac
{
public:
	static CSC_Obj*		Create(void)
	{
		CSC_Obj*		pInstance = new T;
		pInstance->Initialize();

		return pInstance;
	}
	
public:
	CFac() {}
	~CFac() {}

};