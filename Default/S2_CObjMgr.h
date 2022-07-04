#pragma once
#include "SC_Obj.h"

class CS2_CObjMgr
{
public:
	CS2_CObjMgr();
	~CS2_CObjMgr();
public:
	list<CSC_Obj*>* Get_List(CSC_Obj::OBJID eID) { return &m_ObjList[eID]; }

public:
	void		Add_Object(CSC_Obj::OBJID eID, CSC_Obj* pObj);
	void		Delete_ID(CSC_Obj::OBJID eID);

	int			Update(void);
	int			Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

private:
	list<CSC_Obj*>	m_ObjList[CSC_Obj::OBJ_END];

public:
	static		CS2_CObjMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CS2_CObjMgr;

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
	static		CS2_CObjMgr*		m_pInstance;
};

//#pragma once
//#include "Enum.h"
//#include "Obj.h"
//
//class CObj;
//class CObjMgr
//{
//private:
//	CObjMgr();
//	~CObjMgr();
//
//public:
//	list<CObj*>* Get_List(OBJID eID) { return &m_ObjList[eID]; }
//
//public:
//	void		Add_Object(OBJID eID, CObj* pObj);
//	void		Delete_ID(OBJID eID);
//
//	int			Update(void);
//	void		Late_Update(void);
//	void		Render(HDC hDC);
//	void		Release(void);
//
//private:
//	list<CObj*>	m_ObjList[OBJ_END];
//
//public:
//	static		CObjMgr*		Get_Instance(void)
//	{
//		if (nullptr == m_pInstance)
//			m_pInstance = new CObjMgr;
//
//		return m_pInstance;
//	}
//
//	static		void			Destroy_Instance(void)
//	{
//		if (nullptr != m_pInstance)
//		{
//			delete m_pInstance;
//			m_pInstance = nullptr;
//		}
//	}
//
//private:
//	static		CObjMgr*		m_pInstance;
//};
//
