#pragma once
#include "Enum.h"
#include "Obj.h"

class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	list<CObj*>* Get_List(OBJID eID) { return &m_ObjList[eID]; }

public:
	void		Add_Object(OBJID eID, CObj* pObj);
	void		Delete_ID(OBJID eID);

	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

private:
	list<CObj*>	m_ObjList[OBJ_END];

public:
	static		CObjMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjMgr;

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
	static		CObjMgr*		m_pInstance;
};

