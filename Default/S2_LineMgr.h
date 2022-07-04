#pragma once
#include "S2_Line.h"
#include "SC_Obj.h"
class CS2_LineMgr
{
private:
	CS2_LineMgr();
	//CLineMgr(const CLineMgr& rhs) = delete;
	~CS2_LineMgr();

public:
	void		Initialize(void);
	void		Render(HDC hDC);
	void		Release(void);
	void		DeleteAll(void);

	LINEID		Collision_Line(float* fX, float* fY, float* pY, float* pX);
	float		Collision_Down(CSC_Obj* _Player);
	float		Collision_Up(CSC_Obj* _Player);
	float		Collision_Left(CSC_Obj* _Player);
	float		Collision_Right(CSC_Obj* _Player);
	

	//void		Load_File(void);
	list<CS2_Line*>* Get_Line_List() { return m_LineList; }
public:
	static		CS2_LineMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CS2_LineMgr;

		return m_pInstance;
	}

	static		void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static		CS2_LineMgr*		m_pInstance;
	list<CS2_Line*>				m_LineList[LINE_END];
	float m_Set[4];
private:
	void	SetColisionPos(CSC_Obj* _Player);
public:
	HPEN m_hPen[LINE_LD];
};

