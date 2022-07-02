#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj*		Create(void)
	{
		CObj*		pInstance = new T;
		pInstance->Initialize();

		return pInstance;
	}

public:
	CAbstractFactory() {}
	~CAbstractFactory() {}
};
